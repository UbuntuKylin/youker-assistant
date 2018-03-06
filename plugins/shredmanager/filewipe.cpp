/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <dirent.h>

#include "filewipe.h"

#ifdef STAT_MACROS_BROKEN
/* just in case, so we don't unlink a directory,
   we don't currently handle broken stat macros */
# define unlink(x) remove(x)
#endif

#ifndef HAVE_UNLINK
# define unlink(x) remove(x)
#endif

/* these should be safe for darwin */
#ifndef PATH_MAX
# define PATH_MAX 1023
#endif
#ifndef NAME_MAX
# define NAME_MAX 255
#endif

#ifndef O_NOFOLLOW
# define O_NOFOLLOW 0
#endif

#ifndef O_DSYNC
# define O_DSYNC O_SYNC
#endif

#if defined HAVE_FSYNC || defined HAVE_FDATASYNC
# define SYNC 0
#else
# ifdef O_DSYNC
#  define SYNC O_DSYNC
# else
#  define SYNC O_SYNC
# endif
#endif

#include <sys/stat.h>

/* exit codes */
#define SUCCESS 0
#define FAILED -1
#define NOT_SUPPORT_TYPE -2
#define PATH_NAME_TOO_LONG -3
#define STAT_FAILED -4
#define WIPE_WRITE_FAILED -5

static int verbose = 0;

#ifndef __DEBUG
#define fprintf(e, fmt...) 
#endif

struct file_info
{
    char path_name[PATH_MAX+1];

    int fd;
    struct stat st;

    char *buf;
    size_t buf_size;
};

int do_close(const char name[], const int fd)
{
    if (close(fd))
    {
        fprintf(stderr, "\r close failed for '%s': %s\n", name, strerror(errno));
        return FAILED;
    }
    return SUCCESS;
}

int do_write(const char name[], const int fd, char *buf, size_t count)
{
    int ret;
    ssize_t c;
    size_t written;

    if (count == 0)
        abort();

    ret = 0;
    written = 0;

    while (written < count)
    {
        c = write(fd, buf, count - written);

        if (c == 0) 
            abort();

        if (c > 0)
        {
            written += c;
            buf += c;
        }
        else
        {
            if (errno == ENOSPC)
            {
                --count; 
                ret = ENOSPC;
            }
            else if (errno == EAGAIN || errno == EINTR)
                continue;
            else
	    {
                fprintf(stderr, "\r write failed to '%s': %s\n", name, strerror(errno));
                return FAILED;
            }
        }
    }

    return ret;
}

int sync_data(const char name[], const int fd)
{
    if (fd == -1)
        //abort();
        return FAILED;

#if !defined (HAVE_FSYNC) || !defined (HAVE_FDATASYNC)
    /*
    the file will still get written out
    file.h will make the file be opened with a sync flag
    */
    return SUCCESS;
#endif

#ifdef HAVE_FDATASYNC
    if (fdatasync(fd))
#endif
#ifdef HAVE_FSYNC
    if (fsync(fd))
#endif
    {
        fprintf(stderr, "\r cannot synchronize '%s': %s\n", name, strerror(errno));
#ifdef HAVE_FCNTL
        if (fcntl(fd, F_SETFL, O_SYNC) == -1)
        {
            fprintf(stderr, "\r cannot set synchronis writes '%s': %s\n", name, strerror(errno));
            return FAILED;
        }
#endif
    }

    return SUCCESS;
}

int write_pass(struct file_info *info)
{
    off_t i;

#ifdef HAVE_BZERO
    bzero(info->buf, info->buf_size);
#endif
    memset(info->buf, 0, info->buf_size);

    for (i = 0; i < info->st.st_size; i += info->buf_size)
    {
        if (do_write(info->path_name, info->fd, info->buf, info->buf_size)) 
            return WIPE_WRITE_FAILED;
    }

    return sync_data(info->path_name, info->fd);
}

int zero_data(struct file_info *info)
{
    info->buf_size = 1024*1024;//512
    if ((info->buf = (char *)malloc(info->buf_size)) == NULL)
    {
        fprintf(stderr, "\r cannot allocate %ld bytes for '%s': %s\n", 
            (long int)info->buf_size, info->path_name, strerror(errno));
        return FAILED;
    }

    if (write_pass(info)) {
        free(info->buf);
        return FAILED;
    }

    free(info->buf);
    return SUCCESS;
}

int wipe_data(struct file_info *info)
{
    if (info->st.st_size == 0)
    {
        if (verbose)
        {
            fprintf(stderr, "\r zero length, skipping '%s'\n", info->path_name);
        }
        /* no need to write anything */
        return SUCCESS; 
    }

    return zero_data(info);
}

char rand_safe_char(void)
{
    int i;
    
    struct timeval tpstart;
    gettimeofday(&tpstart,NULL);
    srand(tpstart.tv_usec);
    
    const char nameset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_+=%@#.";
    i = (int) ((float) (sizeof(nameset) - 1.0) * rand() / (RAND_MAX+1.0));
    return nameset[i];
}


void rename_str(char str[], const size_t len)
{
    int i;

    i=0;
    while (i <= ((int)len-2))
        str[i++] = rand_safe_char();

    str[len-1] = 0;
}

int dir_sync(char dir_name[])
{
    int dfd;
    DIR *dir;

    if ((dir = opendir(dir_name)) == NULL)
    {
        fprintf(stderr, "\r cannot open directory '%s': %s\n", dir_name, strerror(errno));
        return FAILED;
    }

    if ((dfd = dirfd(dir)) < 0)
    {
         fprintf(stderr, "\r dirfd() failed for '%s': %s\n", dir_name, strerror(errno));
        return FAILED;
    }

    sync_data(dir_name, dfd);

    if (closedir(dir))
    {
        fprintf(stderr, "\r closedir failed for '%s': %s\n", dir_name, strerror(errno));
        return FAILED;
    }

    return SUCCESS;
}

int rename_file(struct file_info *info)
{
    int i;
    size_t len, file_len, path_len;
    char base_name[PATH_MAX+1];
    char *base, dest_name[PATH_MAX+1];

    memset(dest_name, 0, sizeof(dest_name));
    strcpy(dest_name, info->path_name);

    base = strrchr(dest_name, '/');

    if (base == NULL || base >= (dest_name + sizeof(dest_name)))
        base = dest_name;
    else
        ++base;
    
    *base = 0x00;
    memset(base_name, 0, sizeof(base_name));
    strcpy(base_name, dest_name);
    
    path_len = strnlen(dest_name, sizeof(dest_name));
    file_len = PATH_MAX - path_len;
    
    i = 0;
    len = 2;
    while (!i && len <= file_len)
    {
        rename_str(base, len++);
        i = access(dest_name, F_OK);
    }
    
    if (rename(info->path_name, dest_name) == 0)
    {
        memset(info->path_name, 0, sizeof(info->path_name));
        strncpy(info->path_name, dest_name, strnlen(dest_name, sizeof(dest_name)));
    }
    else
    {
        fprintf(stderr, "\r cannot rename '%s': %s\n", info->path_name, strerror(errno));
        return FAILED;
    }

    if (dir_sync(base_name))
        return FAILED;

    return SUCCESS;
}

int destroy_file(struct file_info *info)
{
    if ((info->fd = open(info->path_name, O_WRONLY | O_NOFOLLOW | SYNC)) < 0)
    {
        fprintf(stderr, "\r cannot open '%s': %s\n", info->path_name, strerror(errno));
        return FAILED;
    }

    if (wipe_data(info) == FAILED)
    {
        do_close(info->path_name, info->fd);
        fprintf(stderr, "\r failed to wipe '%s'\n", info->path_name);
        return FAILED;
    }
    
    if (ftruncate(info->fd, 0))
    {
        do_close(info->path_name, info->fd);
        fprintf(stderr, "\r cannot truncate '%s': %s\n", info->path_name, strerror(errno));
        return FAILED;
    }

    do_close(info->path_name, info->fd);

    //Do not care about the return value;
    rename_file(info);
    
    if (unlink(info->path_name))
    {
        fprintf(stderr, "\r cannot unlink '%s': %s\n", info->path_name, strerror(errno));
        return FAILED;
    }

    return SUCCESS;
}

int do_file(const char *name)
{
    struct file_info info;

    if (strlen(name) > PATH_MAX)
        return PATH_NAME_TOO_LONG;

    memset(info.path_name, 0, sizeof(info.path_name));
    strcpy(info.path_name, name);

    if (lstat(name, &info.st))
    {
        fprintf(stderr, "\r cannot stat '%s': %s\n", name, strerror(errno));
        return FAILED;
    }

    switch (info.st.st_mode & S_IFMT)
    {
    /* regular file */
    case S_IFREG: 
        return destroy_file(&info); 
        break;
    /* block device */    
    case S_IFBLK: 
        //destroy_blkdev(f);
        return NOT_SUPPORT_TYPE;
        break;
    /* char dev */    
    case S_IFCHR: 
        //destroy_file(f);
        return NOT_SUPPORT_TYPE;
    break;
    /* directory */
    case S_IFDIR: 
        //drill_down(name);
        return NOT_SUPPORT_TYPE;
    break;

    /* fifo */
    case S_IFIFO: 
    /* socket */
    case S_IFSOCK: 
    /* sym link */
    case S_IFLNK: 
        if (unlink(name))
        {
            if (verbose)
	    {
                fprintf(stderr, "\r cannot remove '%s': %s\n", name, strerror(errno));
            }
        }
        break;

    default:
        //abort();
        return NOT_SUPPORT_TYPE;
    }

    return NOT_SUPPORT_TYPE;
}

//#ifdef __DEBUG
//int main(int argc, char **argv)
//{
    /*
//    char pwd_path[PATH_MAX+1];
//    memset(pwd_path, 0, sizeof(pwd_path)):
//    int count = readlink("/proc/self/exe", pwd_path, PATH_MAX);
//    if ( count < 0 || count >= PATH_MAX)
//    {
//        return -1;
//    }
//    */

//    return do_file(argv[1]);
//}
//#endif
