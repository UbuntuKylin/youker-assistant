#include <QMap>
#include <QPluginLoader>
#include <QObject>

class PluginManager
{
private:
    PluginManager();
    ~PluginManager();

public:
    static PluginManager *Instance();
    bool loadPlugin(QString plugin_path);
    bool unloadPlugin(QString plugin_guid);

    template<class T>
    T* getPlugin(QString plugin_guid)
    {
        QMap<QString, QPluginLoader*>::iterator iter = plugin_map.find(plugin_guid);
        if (iter == plugin_map.end())
        {
            return NULL;
        }
        return iter.value();
    }

    int count() {return plugin_map.count();}

    template<class T>
    T* getPluginByindex(int index)
    {
        QMap<QString, QPluginLoader*>::iterator iter = plugin_map.begin();
        for (int i = 0;i < index; ++i)
        {
            ++iter;
        }
        return iter.value();
    }

    template<class T>
    T* getInterfaceByindex(int index)
    {
        QPluginLoader* plugin_loader = getPluginByindex<QPluginLoader>(index);
        QObject *plugin = plugin_loader->instance();
        return qobject_cast<T*>(plugin);
    }

    template<class T>
    T* getInterfaceByGuid(QString guid)
    {
        QMap<QString, QPluginLoader*>::iterator iter = plugin_map.find(guid);
        if (iter == plugin_map.end())
        {
            return NULL;
        }
        QPluginLoader* plugin_loader = iter.value();
        QObject *plugin = plugin_loader->instance();
        return qobject_cast<T*>(plugin);
    }

private:
    QMap<QString, QPluginLoader*> plugin_map;
};


/*class PluginManager : public QObject
{
    Q_OBJECT

public:
    explicit PluginManager(QObject *parent = 0);
    ~PluginManager();

    static PluginManager* Instance();

signals:
    void pluginAdded(QWidget *const w);

public slots:
    void loadPlugin(QString plugin_path);
};*/
