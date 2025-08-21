#pragma once

#include <QtWidgets/QWidget>
#include "CFrameLessWidgetBase.h"
#include "CTitleBar.h"
#include "VideoWidget.h"
#include "CBottomCtrlBar.h"
#include "CRightPlayListWidget.h"
#include "CVlcKits.h"
#include <memory>


using namespace std;


class MainWidget : public CFrameLessWidgetBase
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    void initUI();

private:
    void mouseDoubleClickEvent(QMouseEvent* event)override;
    void keyPressEvent(QKeyEvent* event)override;

    void mouseMoveEvent(QMouseEvent* event)override;
    void resizeEvent(QResizeEvent* event)override;

private slots:
    void onPlayListItemClicked(int index);
    void onOpenPlayList();
    void onOpenFile(const QStringList& fileList);
    void onTimeSliderMoved(int value);
    void onVolumeSliderMoved(int value);
    void onPlay();
    void onStop();
    void onPrev();
    void onNext();
    void onFull();
    void on_close();



private:
    CTitleBar *m_pTitleBar;
    VideoWidget *m_pVideoWidget;
    CRightPlayListWidget* m_pRightPlayListWidget;
    CBottomCtrlBar *m_pBottomCtrlBar;

    std::unique_ptr<CVlcKits> m_pVlc;
    bool is_Play = false;
    bool is_ShowList = false;

    QStringList m_fileList; 
    int m_currentPlayIndex; 
};

