#include "MainWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QKeyEvent>
#include <Windows.h>
#include <QDebug>
#include <QPropertyAnimation>
#include <QApplication>


//枚举VLC子窗口的回调函数
//hwnd：当前处理的窗口句柄
//lParam：附加参数

BOOL CALLBACK EnumVLC(HWND hwnd, LPARAM lParam)
{
    TCHAR szTitle[1024];

    int nLen = GetWindowText(hwnd, szTitle, 1024);  //获取窗口标题

    if (nLen > 0)
    {
        EnableWindow(hwnd, FALSE);//禁用窗口
        KillTimer(NULL, 1); //停用定时器

    }

    return TRUE;
}

//定时器回调函数，定期检查VLC窗口
//标准定时器回调参数

void CALLBACK TimeProc(HWND hwnd, UINT msg, UINT_PTR id, DWORD time)
{
    HWND vlcHwnd = FindWindowEx(NULL, NULL, NULL, L"vlcmain"); //查找名为"vlcmain"的顶层窗口（VLC主窗口）

    if (vlcHwnd)
    {
        EnumChildWindows(vlcHwnd, EnumVLC, NULL);  //枚举其所有子窗口并对每个子窗口调用EnumVLC函数
    }
}


MainWidget::MainWidget(QWidget *parent)
    : CFrameLessWidgetBase(parent)
{
    this->setWindowTitle("vlcmain");

    m_pVlc.reset(new CVlcKits());

    int nRet = m_pVlc->initVlc();

    switch (nRet)
    {
    case -1:
        //libvlc_new failed
        QMessageBox::information(this, "title", u8"libvlc_new failed");
        exit(EXIT_FAILURE);

    case -2:
        //libvlc_media_player_new failed
        QMessageBox::information(this, "title", u8"libvlc_media_player_new failed");
        exit(EXIT_FAILURE);
    }

    setMouseTracking(true);

    initUI();

    
}

MainWidget::~MainWidget()
{}



void MainWidget::initUI()
{
    setStyleSheet("background-color:black");

     m_pTitleBar = new CTitleBar(this);
     m_pVideoWidget = new VideoWidget(this);
     m_pRightPlayListWidget = new CRightPlayListWidget(this);
     m_pRightPlayListWidget->hide();

     m_pBottomCtrlBar = new CBottomCtrlBar(this);
    
     QVBoxLayout* pMainVLay = new QVBoxLayout(this);
     pMainVLay->addWidget(m_pTitleBar);

     pMainVLay->setSpacing(0);

     QHBoxLayout* pHLay = new QHBoxLayout;
     pHLay->addWidget(m_pVideoWidget);
     pHLay->addWidget(m_pRightPlayListWidget);

     pMainVLay->addLayout(pHLay);
     pMainVLay->addWidget(m_pBottomCtrlBar);

     pMainVLay->setContentsMargins(0, 0, 0, 0);

     connect(m_pTitleBar, &CTitleBar::sig_close, this, &MainWidget::on_close);
     connect(m_pTitleBar, &CTitleBar::sig_OpenFile, this, &MainWidget::onOpenFile);

     connect(m_pVideoWidget, &VideoWidget::sig_OpenFile, this, &MainWidget::onOpenFile);
     connect(m_pVideoWidget, &VideoWidget::sig_SliderMoved, this, &MainWidget::onTimeSliderMoved);
     connect(m_pVideoWidget, &VideoWidget::sig_SliderClicked, this, &MainWidget::onTimeSliderMoved);
     connect(m_pVideoWidget, &VideoWidget::sig_OpenPlayList, this, &MainWidget::onOpenPlayList);

     connect(m_pRightPlayListWidget, &CRightPlayListWidget::sig_ItemClicked, this, &MainWidget::onPlayListItemClicked);

     connect(m_pBottomCtrlBar, &CBottomCtrlBar::sig_play, this, &MainWidget::onPlay);
     connect(m_pBottomCtrlBar, &CBottomCtrlBar::sig_stop, this, &MainWidget::onStop);
     connect(m_pBottomCtrlBar, &CBottomCtrlBar::sig_prev, this, &MainWidget::onPrev);
     connect(m_pBottomCtrlBar, &CBottomCtrlBar::sig_next, this, &MainWidget::onNext);
     connect(m_pBottomCtrlBar, &CBottomCtrlBar::sig_Full, this, &MainWidget::onFull);
     connect(m_pBottomCtrlBar, &CBottomCtrlBar::sig_VolumeMoved, this, &MainWidget::onVolumeSliderMoved);

     
     connect(m_pVlc.get(), &CVlcKits::sig_UpdateTimeText, [=](const QString& time) {
         m_pBottomCtrlBar->setCurPlayTime(time);
         });

     connect(m_pVlc.get(), &CVlcKits::sig_TimeSliderPos, [=](const int& value) {
         m_pVideoWidget->setSliderValue(value);
         });

     connect(m_pVlc.get(), &CVlcKits::sig_VolumeSliderPos, [=](const int& value) {
         m_pBottomCtrlBar->setVolumeValue(value);
         });

     connect(m_pVlc.get(), &CVlcKits::sig_CurrentIndex, [=](const int& index) {
         m_pRightPlayListWidget->setCurrentIndex(index);
         });

}


void MainWidget::on_close()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(u8"提示");
    msgBox.setText(u8"确定要退出吗？");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);

    // 为消息框设置独立样式
    msgBox.setStyleSheet("QMessageBox { background-color: white; }");
    if (msgBox.exec() == QMessageBox::Yes)
    {
        close();
    }
}


// 处理播放列表项点击
void MainWidget::onPlayListItemClicked(int index)
{
    // 停止当前播放
    if (m_pVlc) {
        m_pVlc->stop();
    }

    if (index < 0 || index >= m_fileList.size()) {
        return;
    }

    //qDebug() << "index = " << index;

    m_pVlc->playItem(index);

    // 更新播放状态
    m_pVideoWidget->setPlayStatus(true);
    is_Play = true;

    // 设置当前播放索引
    m_currentPlayIndex = index;

    // 高亮当前播放项
    QModelIndex modelIndex = m_pRightPlayListWidget->getModelIndex(index);
    if (modelIndex.isValid()) {
        m_pRightPlayListWidget->setCurrentIndex(modelIndex);
    }

}


void MainWidget::onOpenPlayList()
{
    if (is_ShowList)
    {
        // 隐藏播放列表（向右滑出）
        QPropertyAnimation* animation = new QPropertyAnimation(m_pRightPlayListWidget, "pos");
        animation->setDuration(300);
        animation->setStartValue(m_pRightPlayListWidget->pos());
        animation->setEndValue(QPoint(width(), m_pTitleBar->height()));
        animation->start(QAbstractAnimation::DeleteWhenStopped);

        connect(animation, &QPropertyAnimation::finished, [=]() {
            m_pRightPlayListWidget->hide();
            });

        is_ShowList = false;
    }
    else
    {
        // 显示播放列表（向左滑入）
        m_pRightPlayListWidget->show();
        m_pRightPlayListWidget->raise(); // 确保在最上层

        QPropertyAnimation* animation = new QPropertyAnimation(m_pRightPlayListWidget, "pos");
        animation->setDuration(300);
        animation->setStartValue(QPoint(width(), m_pTitleBar->height()));
        animation->setEndValue(QPoint(width() - 200, m_pTitleBar->height()));
        animation->start(QAbstractAnimation::DeleteWhenStopped);

        is_ShowList = true;
    }
   
}


void MainWidget::onTimeSliderMoved(int value)
{
    m_pVlc->setVideoPosition(value);
}

void MainWidget::onVolumeSliderMoved(int value)
{
    m_pVlc->setVolumeSliderValue(value);
}

void MainWidget::onPlay()
{
    m_pVlc->play();
}

void MainWidget::onStop()
{
    m_pVlc->stop();
}

void MainWidget::onPrev()
{
    m_pVlc->prev();
}

void MainWidget::onNext()
{
    m_pVlc->next();
}

void MainWidget::onFull()
{
    if (this->isFullScreen())
    {
        this->showNormal();
    }
    else
    {
        this->showFullScreen();
    }
}

void MainWidget::onOpenFile(const QStringList& fileList)
{
    if (fileList.isEmpty())
        return;

    m_pRightPlayListWidget->setListView(fileList);

    m_fileList = fileList;

    if (0 != m_pVlc->play(fileList, (void*)(m_pVideoWidget->winId())))
    {
        QMessageBox::information(this, "title", u8"播放失败!");
        return;
    }

    // 设置当前播放索引
    m_currentPlayIndex = 0;

    // 高亮当前播放项
    QModelIndex modelIndex = m_pRightPlayListWidget->getModelIndex(0);
    if (modelIndex.isValid()) {
        m_pRightPlayListWidget->setCurrentIndex(modelIndex);
    }

    SetTimer(NULL, 1, 300, TimeProc);

    m_pVideoWidget->setPlayStatus(true);
    is_Play = true;
   
}

//鼠标双击
void MainWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (this->isFullScreen())
    {
        this->showNormal();
    }
    else
    {
        this->showFullScreen();
    }
}

void MainWidget::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape)
    {
        if (this->isFullScreen())
        {
            this->showNormal();
        }
    }
}

void MainWidget::mouseMoveEvent(QMouseEvent* event)
{
    QPoint p1 = m_pVideoWidget->mapToGlobal(QPoint(0, 0));

    QRect rect1 = m_pVideoWidget->rect();

    QRect rect2(p1.x(), p1.y(), rect1.width(), rect1.height());

    QPoint p2 = QCursor::pos();

    if (is_Play) 
    {
        if (rect2.contains(p2))
        {
            m_pVideoWidget->showTopWidget(true);
        }
        else
        {
            m_pVideoWidget->showTopWidget(false);
        }
    }
   
}


void MainWidget::resizeEvent(QResizeEvent* event)
{
    // 保持播放列表在正确位置
    if (is_ShowList) {
        m_pRightPlayListWidget->move(width() - 200, m_pTitleBar->height());
    }
    else {
        m_pRightPlayListWidget->move(width(), m_pTitleBar->height());
    }

    QWidget::resizeEvent(event);
}