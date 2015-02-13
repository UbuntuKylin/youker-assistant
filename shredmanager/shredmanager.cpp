#include "shredmanager.h"

ShredManager::ShredManager(QObject *parent)
:QObject(parent), shred_dialog(this)
{

}

ShredManager::~ShredManager()
{

}

QString ShredManager::getGuid()
{
    return tr("7F1F6AF1-82C3-4224-8A37-676A7FC98YUA");
}

//插件名称
 QString ShredManager::getName()
{
    return tr("Shred Manager");
}

//插件描述
QString ShredManager::getDescribe()
{
    return tr("可以彻底粉碎无法删除的文件");
}

//插件图片名称
QString ShredManager::getPicture()
{
    return "shredder.png";
}

void  ShredManager::doAction()
{
    int windowWidth = QApplication::desktop()->width();
    int windowHeight = QApplication::desktop()->height();
    shred_dialog.move((windowWidth - 500) / 2,(windowHeight - 471) / 2);
    shred_dialog.show();
    shred_dialog.raise();
}

Q_EXPORT_PLUGIN2(ShredManager, ShredManager)
