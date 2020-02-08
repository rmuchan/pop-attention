#include <algorithm>
#include "pop_attention_plugin.h"

PopAttentionPlugin::PopAttentionPlugin(QObject *parent) : QObject(parent), widget(new QLabel("DP")) {
    widget->setFixedSize(26, 26);
    widget->setAlignment(Qt::AlignCenter);
}

PopAttentionPlugin::~PopAttentionPlugin() {
    widget->deleteLater();
}

const QString PopAttentionPlugin::pluginName() const {
    return "pop-attention";
}

const QString PopAttentionPlugin::pluginDisplayName() const {
    return "Demands POP!";
}

void PopAttentionPlugin::init(PluginProxyInterface *proxyInter) {
    m_proxyInter = proxyInter;
    if (!pluginIsDisable()) {
        m_proxyInter->itemAdded(this, "widget");
    }

    auto dock = new DockDaemonInter("com.deepin.dde.daemon.Dock", "/com/deepin/dde/daemon/Dock", QDBusConnection::sessionBus(), this);
    connect(dock, &DockDaemonInter::EntryAdded, this, &PopAttentionPlugin::onEntryAdded);
    connect(dock, &DockDaemonInter::EntryRemoved, this, &PopAttentionPlugin::onEntryRemoved);
    for (const auto &path : dock->entries()) {
        onEntryAdded(path);
    }
}

QWidget *PopAttentionPlugin::itemWidget(const QString &itemKey) {
    return widget;
}

bool PopAttentionPlugin::itemAllowContainer(const QString &itemKey) {
    return true;
}

bool PopAttentionPlugin::itemIsInContainer(const QString &itemKey) {
    return m_proxyInter->getValue(this, "container", true).toBool();
}

void PopAttentionPlugin::setItemIsInContainer(const QString &itemKey, bool container) {
    m_proxyInter->saveValue(this, "container", container);
}

bool PopAttentionPlugin::pluginIsAllowDisable() {
    return true;
}

bool PopAttentionPlugin::pluginIsDisable() {
    return m_proxyInter->getValue(this, "disabled", false).toBool();
}

void PopAttentionPlugin::pluginStateSwitched() {
    bool disabled = !pluginIsDisable();
    m_proxyInter->saveValue(this, "disabled", disabled);
    if (disabled) {
        m_proxyInter->itemRemoved(this, "widget");
    } else {
        m_proxyInter->itemAdded(this, "widget");
    }
}

void PopAttentionPlugin::onEntryAdded(const QDBusObjectPath &path, int unused) {
    auto entry = new DockEntryInter("com.deepin.dde.daemon.Dock", path.path(), QDBusConnection::sessionBus(), this);
    entries.push_back(entry);
    updateWindowInfo(entry, entry->windowInfos());
    connect(entry, &DockEntryInter::WindowInfosChanged, this, &PopAttentionPlugin::onWindowInfoChanged);
}

void PopAttentionPlugin::onEntryRemoved(const QString &id) {
    for (int i = entries.size() - 1; i >= 0; i--) {
        auto entry = entries[i];
        if (entry->id() == id) {
            entries.remove(i);
            updateWindowInfo(entry, WindowInfoMap());
            entry->deleteLater();
            break;
        }
    }
}

void PopAttentionPlugin::onWindowInfoChanged(const WindowInfoMap &infoMap) {
    auto entry = qobject_cast<DockEntryInter *>(sender());
    updateWindowInfo(entry, infoMap);
}

void PopAttentionPlugin::updateWindowInfo(DockEntryInter *entry, const WindowInfoMap &infoMap) {
    bool modified;
    if (std::any_of(infoMap.begin(), infoMap.end(), [](const WindowInfo &it) { return it.attention; })) {
        modified = !hasAttention.contains(entry);
        hasAttention.insert(entry);
    } else {
        modified = hasAttention.remove(entry);
    }
    if (modified && !pluginIsDisable()) {
        m_proxyInter->requestWindowAutoHide(this, "widget", hasAttention.empty());
    }
}
