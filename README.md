# MediaPlayer – 基于 Qt 和 libvlc 的跨平台视频播放器

一个使用 **C++/Qt** 和 **libvlc** 开发的轻量级、跨平台视频播放器，支持常见视频格式，提供友好的用户界面和基本播放控制功能。

![Qt](https://img.shields.io/badge/Qt-5.x-green?logo=qt)
![VLC](https://img.shields.io/badge/libvlc-3.x-orange?logo=vlc-media-player)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-blue)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)

## 功能特性

- ✅ 支持常见视频格式（mp4, avi, mkv, flv 等）
- ✅ 自定义标题栏与无边框窗口设计
- ✅ 播放控制：播放/暂停、前进/后退、音量调节
- ✅ 时间轴拖拽、全屏切换
- ✅ 播放列表管理
- ✅ 样式表支持（QSS）自定义界面风格

## 预览

*(此处可添加项目截图或演示GIF)*
<img width="800" height="568" alt="image" src="https://github.com/user-attachments/assets/cf795b44-fbf1-4424-bd86-eab75f1b2952" />



## 项目结构
```plaintext
MediaPlayer/
├── Header Files/
│   ├── CButtonCtrlBar.h          # 控制栏按钮组
│   ├── CFrameLessWidgetBase.h    # 无边框窗口基类
│   ├── COpenFileButton.h         # 打开文件按钮
│   ├── CPlayButtonGroupWidget.h  # 播放控制按钮组
│   ├── CRightPlayListWidget.h    # 右侧播放列表
│   ├── CTimeSlider.h             # 时间进度条
│   ├── CTitleBar.h               # 自定义标题栏
│   ├── CVideoWidgetTopWidget.h   # 视频上方控制栏
│   ├── CVlcKits.h                # VLC 封装接口
│   ├── CVolumeButton.h           # 音量按钮
│   ├── CVolumeSliderDialog.h     # 音量弹窗
│   ├── MainWidget.h              # 主窗口
│   ├── qss.h                     # 样式表资源
│   └── VideoWidget.h             # 视频渲染组件
├── Source Files/
│   ├── CButtonCtrlBar.cpp
│   ├── CFrameLessWidgetBase.cpp
│   ├── COpenFileButton.cpp
│   ├── CPlayButtonGroupWidget.cpp
│   ├── CRightPlayListWidget.cpp
│   ├── CTimeSlider.cpp
│   ├── CTitleBar.cpp
│   ├── CVideoWidgetTopWidget.cpp
│   ├── CVlcKits.cpp
│   ├── CVolumeButton.cpp
│   ├── CVolumeSliderDialog.cpp
│   ├── main.cpp
│   ├── MainWidget.cpp
│   └── VideoWidget.cpp
├── Resource Files/               # 资源文件（如图标、样式表）
└── Translation Files/            # 国际化文件（可选）
```

## 构建说明

### 依赖项

-  Qt 5.12
- libvlc 开发库

#### Ubuntu/Debian:
```bash
sudo apt install libvlc-dev vlc
```

## Windows:
下载 VLC SDK 并配置包含路径和库路径。
```bash
git clone https://github.com/videolan/vlc.git
cd vlc
```
## macOS:
```bash
brew install vlc
```
## 编译步骤
1、克隆本项目：
```bash
git clone https://github.com/SeaDragon79/MediaPlayer.git
cd MediaPlayer
```
2、使用 Qt Creator 打开 MediaPlayer.pro，配置 kit 和 libvlc 路径，然后构建并运行。
或使用命令行（需配置好 Qt 环境变量）：
```bash
mkdir build && cd build
qmake ../MediaPlayer.pro
make -j4
```

### 使用说明
- 点击"打开文件"按钮选择视频文件
- 使用底部控制栏进行播放/暂停、音量调节等操作
- 右键视频画面可弹出菜单，支持全屏切换
- 拖拽时间轴可跳转播放进度
## 贡献
欢迎提交 Issue 和 Pull Request！如果你有任何改进建议或功能需求，请随时联系我们。
## 许可证
本项目基于 MIT License 开源，详情请见 LICENSE 文件。
## 致谢

- [VLC Media Player](https://www.videolan.org/vlc/) - 提供强大的媒体播放能力
- [Qt Framework](https://www.qt.io/) - 提供跨平台 GUI 开发框架
- [GitHub](https://github.com/) - 提供代码托管和协作平台
## 如果这个项目对你有帮助，请点一个 ⭐️ 支持一下！
