#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include<Python.h>
#include <sys/mman.h>
unsigned char * my_c_function(int base,int len)
{
	unsigned char *buf = (unsigned char *) malloc(len);
	unsigned char bufcpy[len];
	int i=0;
	void *mmp = NULL;
	int mmoffset = 0;
	int fd = open("/dev/mem",O_RDONLY);
	if(len == 0)
		return;
	if(buf == NULL)
		return;
	mmoffset = base % getpagesize();
	mmp = mmap(0, mmoffset + len, PROT_READ, MAP_SHARED, fd, base - mmoffset);
	if(mmp == MAP_FAILED)
    	{
       		free(buf);
        	return;
    	}
	memcpy(bufcpy, (unsigned char *) mmp + mmoffset, len);
    	munmap(mmp, mmoffset + len);
	for(i=0;i < len - 1;i++)
		if(bufcpy[i] == '\0')
			bufcpy[i] = '$';
	bufcpy[len-1]='\0';
	for(i=0;i<len;i++)
		buf[i] = bufcpy[i];
	close(fd);
	return buf;
}
static PyObject * wrap_my_c_fun(PyObject *self, PyObject *args)
{
	int k ;
	int m;
	char *n;
	if (!PyArg_ParseTuple(args, "ii", &k,&m))//这句是把python的变量args转换成c的变量command
	    	return NULL;
	n = my_c_function(k,m);//调用c的函数
	return Py_BuildValue("s", n);//把c的返回值n转换成python的对象
} 
static PyMethodDef MyCppMethods[] = {
//MyCppFun1是python中注册的函数名，wrap_my_c_fun是函数指针
   {"MyCppFun1", wrap_my_c_fun, METH_VARARGS, "Execute a shell command."},
   {NULL, NULL, 0, NULL}
}; 
PyMODINIT_FUNC initMyCppModule(void)
{
//初始模块，把MyCppMethods初始到MyCppModule中
   PyObject *m = Py_InitModule("MyCppModule", MyCppMethods);
  if (m == NULL) return;
} 
