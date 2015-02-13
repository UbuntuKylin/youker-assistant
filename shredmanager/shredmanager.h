#include <QObject>
#include <QString>
#include "../component/plugininterface.h"
#include "shreddialog.h"

//插件入口
class ShredManager : public QObject , PluginInterface
{
  Q_OBJECT
  Q_INTERFACES(PluginInterface)

public:
    ShredManager(QObject* parent = 0);
    virtual ~ShredManager();

public slots:

public:
    virtual QString getGuid();
    virtual QString getName();
    virtual QString getDescribe();
    virtual QString getPicture();
    virtual void doAction();

private:
    ShredDialog shred_dialog;
};
