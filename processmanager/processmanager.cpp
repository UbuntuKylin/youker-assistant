#include "processmanager.h"

ProcessManager::ProcessManager(QObject *parent)
:QObject(parent), process_dialog(this)
{

}

ProcessManager::~ProcessManager()
{

}

QString ProcessManager::getGuid()
{
    return tr("7F1F6AF1-82C3-4224-8A37-496A7FC98RTA");
}

//插件名称
 QString ProcessManager::getName()
{
    return tr("Process Manager");
}

//插件描述
QString ProcessManager::getDescribe()
{
    return tr("方便用户杀掉进程");
}

//插件图片名称
QString ProcessManager::getPicture()
{
    return "processmanager.png";
}

void  ProcessManager::doAction()
{
    int windowWidth = QApplication::desktop()->width();
    int windowHeight = QApplication::desktop()->height();
    process_dialog.move((windowWidth - 850) / 2,(windowHeight - 476) / 2);
    process_dialog.show();
    process_dialog.raise();
}

Q_EXPORT_PLUGIN2(ProcessManager, ProcessManager)
