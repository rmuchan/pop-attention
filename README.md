# Pop Attention

在Windows下，当一个窗口的任务栏图标闪动时，处于隐藏状态的任务栏会自动弹出，避免用户错过提示。Deepin任务栏没有提供这一功能，本插件予以补充。

本插件在插件列表中显示为“Demands POP!”，在Deepin任务栏内部管理所用名为`pop-attention`。命名来源是X协议中对应任务栏图标闪动的窗口状态`_NET_WM_STATE_DEMANDS_ATTENTION`。~~完全不会起名~~

本插件会在任务栏中添加一个图标（显示文字“DP”），但没有任何功能，默认处于收纳状态。其存在的唯一原因是受`dde-dock`接口限制，插件必须有控件才能调用弹出任务栏。插件可以禁用，禁用时移除图标，且不会自动弹出任务栏。

## 编译安装

本插件使用CMake构建，依赖关系详见CMakeList。CMakeList第4行指定的QT安装路径是我的机器上的，如果编译安装的话需要修改为实际安装位置。

关于QT的版本，我使用的是与系统自带的几个插件一致的5.7.1，使用新版本可能会导致加载失败。

我也会在[GitHub上](https://github.com/ScNM/pop-attention/releases)提供一份编译好的，放在`/usr/lib/dde-dock/plugins/`下即可。

## 已知Bug

- [x] ~~通过快捷键切换至有提示的窗口不会使任务栏回到自动隐藏状态~~

欢迎Issue和PR。

## 610NB！

610NB！