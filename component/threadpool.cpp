/*
 * Copyright (C) 2013 ~ 2017 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    xiangli@ubuntukylin.com/kobe24_lixiang@126.com
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

#include "threadpool.h"
#include <QDebug>

ThreadPool::ThreadPool(QObject *parent) : QObject(parent)
{

}

ThreadPool::~ThreadPool()
{
    exitAllThreads();
}

ThreadPool *ThreadPool::Instance()
{
    static ThreadPool threadPool;
    return &threadPool;
}

QThread *ThreadPool::createNewThread()
{
    QThread *thread = new QThread;
    m_threadPool.push_back(thread);
    return thread;
}

void ThreadPool::moveObjectToThread(QObject *obj)
{
    QThread *work = createNewThread();
    obj->moveToThread(work);
    work->start();
}

void ThreadPool::exitAllThreads()
{
    foreach (QThread *thread, m_threadPool) {
        thread->quit();
        thread->wait(2000);
    }
}
