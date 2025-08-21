#pragma once
#include <QWidget>
#include <QPushButton>
#include "CVolumeButton.h"

class CPlayButtonGroupWidget : public QWidget
{
		Q_OBJECT
public:
		CPlayButtonGroupWidget(QWidget* parent = nullptr);
		~CPlayButtonGroupWidget();

		void setVolumeValue(int value);

private slots:
		void onVolumeMoved(int value);

signals:
		void sig_play();
		void sig_stop();
		void sig_next();
		void sig_prev();
		void sig_VolumeMoved(int value);

private:
		QPushButton* m_pStopButton = nullptr;
		QPushButton* m_pPrevButton = nullptr;
		QPushButton* m_pPlayButton = nullptr;
		QPushButton* m_pNextButton = nullptr;
		CVolumeButton* m_pVolumeButton = nullptr;

};

