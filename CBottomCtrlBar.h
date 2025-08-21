#pragma once
#include "CPlayButtonGroupWidget.h"
#include <QWidget>
#include <QLabel>

class CBottomCtrlBar : public QWidget
{
		Q_OBJECT

public:
		CBottomCtrlBar(QWidget* parent = nullptr);
		~CBottomCtrlBar();

		void showTimeLabel(bool isShow);
	  void setCurPlayTime(const qint64& curMs);
		void setTotalTime(const qint64& totalMs);

		void setCurPlayTime(const QString& time);

		void setVolumeValue(int value);

private:
		QString formatTimeMs(const qint64& timeMs);

private:
		void resizeEvent(QResizeEvent* event)override;

private slots:
		void onVolumeMoved(int value);

		void onFullButtonClicked();

signals:
		void sig_play();
		void sig_stop();
		void sig_prev();
		void sig_next();
		void sig_fullScreen();
		void sig_VolumeMoved(int value);
		void sig_Full();

private:
		QLabel* m_pCurPlayTimeLabel = nullptr;
		//QLabel* m_pTotalTimeLabel = nullptr;

		CPlayButtonGroupWidget* m_pPlayButtonGroupWidget = nullptr;

		QPushButton* m_pToolBoxButton = nullptr;
		QPushButton* m_pEffectButton = nullptr;
		QPushButton* m_pFullButton = nullptr;
};

