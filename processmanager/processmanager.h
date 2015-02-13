#include <QObject>
#include <QString>
#include "../component/plugininterface.h"
#include "processdialog.h"

//插件入口
class ProcessManager : public QObject , PluginInterface
{
  Q_OBJECT
  Q_INTERFACES(PluginInterface)

public:
    ProcessManager(QObject* parent = 0);
    virtual ~ProcessManager();

public slots:

public:
    virtual QString getGuid();
    virtual QString getName();
    virtual QString getDescribe();
    virtual QString getPicture();
    virtual void doAction();

private:
    ProcessDialog process_dialog;
};
