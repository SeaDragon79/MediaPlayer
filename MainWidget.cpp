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


//ö��VLC�Ӵ��ڵĻص�����
//hwnd����ǰ����Ĵ��ھ��
//lParam�����Ӳ���

BOOL CALLBACK EnumVLC(HWND hwnd, LPARAM lParam)
{
    TCHAR szTitle[1024];

    int nLen = GetWindowText(hwnd, szTitle, 1024);  //��ȡ���ڱ���

    if (nLen > 0)
    {
        EnableWindow(hwnd, FALSE);//���ô���
        KillTimer(NULL, 1); //ͣ�ö�ʱ��

    }

    return TRUE;
}

//��ʱ���ص����������ڼ��VLC����
//��׼��ʱ���ص�����

void CALLBACK TimeProc(HWND hwnd, UINT msg, UINT_PTR id, DWORD time)
{
    HWND vlcHwnd = FindWindowEx(NULL, NULL, NULL, L"vlcmain"); //������Ϊ"vlcmain"�Ķ��㴰�ڣ�VLC�����ڣ�

    if (vlcHwnd)
    {
        EnumChildWindows(vlcHwnd, EnumVLC, NULL);  //ö���������Ӵ��ڲ���ÿ���Ӵ��ڵ���EnumVLC����
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
    msgBox.setWindowTitle(u8"��ʾ");
    msgBox.setText(u8"ȷ��Ҫ�˳���");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);

    // Ϊ��Ϣ�����ö�����ʽ
    msgBox.setStyleSheet("QMessageBox { background-color: white; }");
    if (msgBox.exec() == QMessageBox::Yes)
    {
        close();
    }
}


// �������б�����
void MainWidget::onPlayListItemClicked(int index)
{
    // ֹͣ��ǰ����
    if (m_pVlc) {
        m_pVlc->stop();
    }

    if (index < 0 || index >= m_fileList.size()) {
        return;
    }

    //qDebug() << "index = " << index;

    m_pVlc->playItem(index);

    // ���²���״̬
    m_pVideoWidget->setPlayStatus(true);
    is_Play = true;

    // ���õ�ǰ��������
    m_currentPlayIndex = index;

    // ������ǰ������
    QModelIndex modelIndex = m_pRightPlayListWidget->getModelIndex(index);
    if (modelIndex.isValid()) {
        m_pRightPlayListWidget->setCurrentIndex(modelIndex);
    }

}


void MainWidget::onOpenPlayList()
{
    if (is_ShowList)
    {
        // ���ز����б����һ�����
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
        // ��ʾ�����б������룩
        m_pRightPlayListWidget->show();
        m_pRightPlayListWidget->raise(); // ȷ�������ϲ�

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
        QMessageBox::information(this, "title", u8"����ʧ��!");
        return;
    }

    // ���õ�ǰ��������
    m_currentPlayIndex = 0;

    // ������ǰ������
    QModelIndex modelIndex = m_pRightPlayListWidget->getModelIndex(0);
    if (modelIndex.isValid()) {
        m_pRightPlayListWidget->setCurrentIndex(modelIndex);
    }

    SetTimer(NULL, 1, 300, TimeProc);

    m_pVideoWidget->setPlayStatus(true);
    is_Play = true;
   
}

//���˫��
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
    // ���ֲ����б�����ȷλ��
    if (is_ShowList) {
        m_pRightPlayListWidget->move(width() - 200, m_pTitleBar->height());
    }
    else {
        m_pRightPlayListWidget->move(width(), m_pTitleBar->height());
    }

    QWidget::resizeEvent(event);
}