#ifndef POP_ATTENTION_POP_ATTENTION_PLUGIN_H
#define POP_ATTENTION_POP_ATTENTION_PLUGIN_H

#include <QVector>
#include <QLabel>
#include <pluginsiteminterface.h>
#include <com_deepin_dde_daemon_dock.h>
#include <com_deepin_dde_daemon_dock_entry.h>

using DockDaemonInter = com::deepin::dde::daemon::Dock;
using DockEntryInter = com::deepin::dde::daemon::dock::Entry;

class PopAttentionPlugin : public QObject, public PluginsItemInterface {
    Q_OBJECT
    Q_INTERFACES(PluginsItemInterface)
    Q_PLUGIN_METADATA(IID "com.deepin.dock.PluginsItemInterface" FILE "pop-attention.json")

public:
    explicit PopAttentionPlugin(QObject *parent = nullptr);
    ~PopAttentionPlugin() override;
    const QString pluginName() const override;
    const QString pluginDisplayName() const override;
    void init(PluginProxyInterface *proxyInter) override;
    QWidget *itemWidget(const QString &itemKey) override;
    bool itemAllowContainer(const QString &itemKey) override;
    bool itemIsInContainer(const QString &itemKey) override;
    void setItemIsInContainer(const QString &itemKey, bool container) override;
    bool pluginIsAllowDisable() override;
    bool pluginIsDisable() override;
    void pluginStateSwitched() override;

private slots:
    void onEntryAdded(const QDBusObjectPath &path, int unused = 0);
    void onEntryRemoved(const QString &id);
    void onWindowInfoChanged(const WindowInfoMap &infoMap);

private:
    QLabel *widget;
    QVector<DockEntryInter *> entries;
};

#endif //POP_ATTENTION_POP_ATTENTION_PLUGIN_H
