#include "boxwidget.h"
#include <QDebug>
#include "../component/plugininterface.h"
#include "pluginmanager.h"
#include <QGridLayout>



BoxWidget::BoxWidget(QWidget *parent, QString path) :
    QWidget(parent), plugin_path(path)
{
    this->setFixedSize(900, 403);
    //set white background color
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    this->setPalette(palette);

    list_view = new QListView(this);
    list_view->setFocusPolicy(Qt::NoFocus);
    list_view->setAutoFillBackground(true);
    list_view->setIconSize(QSize(48, 48));
    list_view->setResizeMode(QListView::Adjust);
    list_view->setModel(&m_feture_Model);
    list_view->setViewMode(QListView::IconMode);
    list_view->setMovement(QListView::Static);
    list_view->setSpacing(26);
    list_view->setLineWidth(110);

    this->loadPlugins();
    this->initPluginWidget();
    connect(list_view,SIGNAL(clicked(const QModelIndex&)),this,SLOT(OnClickListView(const QModelIndex &)));


//    stacked_widget = new QStackedWidget(this);//stacked_widget will delete when InfoWidget delete
//    stacked_widget->setFocusPolicy(Qt::NoFocus);
//    stacked_widget->setAutoFillBackground(true);
//    stacked_widget->addWidget(list_view);
//    stacked_widget->addWidget(test_widget);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(list_view,0,0);
    setLayout(layout);
}

BoxWidget::~BoxWidget()
{

}

void BoxWidget::displayBoxHomePage() {
//    stacked_widget->setCurrentIndex(0);
}

void BoxWidget::displayBoxSubPage(QString plugin_id) {
//    QObject *object = QObject::sender();
//    QPushButton *btn = qobject_cast<QPushButton *>(object);
//    QString object_name = btn->statusTip();
//    if (object_name == "theme") {
//        stacked_widget->setCurrentIndex(1);
//    }
}

void BoxWidget::loadPlugins()
{
    PluginManager::Instance()->loadPlugin(plugin_path);
}

void BoxWidget::initPluginWidget()
{
    QStringList title;
    title << tr("");
    m_feture_Model.Setitle(title);
    //插入一个空行，用于布局
    m_feture_Model.insertRows(0,1,QModelIndex());
    QModelIndex qindex = m_feture_Model.index(0,0,QModelIndex());
    m_feture_Model.setData(qindex,tr("      "));
    int count =  PluginManager::Instance()->count();
    qDebug() << "Plugin count: " << count;
    //添加插件到主界面
    for (int i = 0;i < count;++i)
    {
//      PluginInterface* ICommon = PluginManager::Instance()->getInterfaceByindex<PluginInterface>(i);
        PluginInterface* ICommon = PluginManager::Instance()->getInterfaceByindex<PluginInterface>(i);
        QString picture = ICommon->getPicture();
//        qDebug() << picture;
        QString  pacture_path = QString(":/model/res/plugin/%1").arg(picture);
//        qDebug() << pacture_path;
        m_feture_Model.SetGuid(ICommon->getGuid());
        //      qDebug() << picture;
        //      qDebug() << pacture_path;
        //      qDebug() << ICommon->getGuid();
        m_feture_Model.insertRows(i + 1,1,QModelIndex());
        qindex = m_feture_Model.index(i + 1,0,QModelIndex());
//        m_feture_Model.setData(qindex,ICommon->getName() + "(" + ICommon->getDescribe() + ")");
        m_feture_Model.setData(qindex,ICommon->getName());
        m_feture_Model.setData(qindex,QIcon(QPixmap(pacture_path)),Qt::DecorationRole);
    }
}

void BoxWidget::OnClickListView(const QModelIndex & index)
{
//  if (index.row() == 0)
//  {
//    return;
//  }
  QString guid = m_feture_Model.getGuid(index.row() - 1);
////  PluginInterface* ICommon = PluginManager::Instance()->getInterfaceByGuid<PluginInterface>(guid);
  PluginInterface* ICommon = PluginManager::Instance()->getInterfaceByGuid<PluginInterface>(guid);
  ICommon->doAction();
//  displayBoxSubPage(guid);
}
