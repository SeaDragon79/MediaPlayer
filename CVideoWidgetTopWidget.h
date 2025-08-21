#pragma once

#include "COpenFileButton.h" 
#include "CTimeSlider.h"
#include <QWidget>
#include <QPushButton>


class CVideoWidgetTopWidget : public QWidget
{
		Q_OBJECT
				
public:
		CVideoWidgetTopWidget(QWidget* parent = nullptr);
		~CVideoWidgetTopWidget();

		void setTimeSliderRange(qint64 value);
		void setSliderValue(int value);
		void showRightBtn(bool flag);
		void showOpenBtn(bool flag);
		void showSlider(bool flag);

		void playListBtnChanged();
		void updateButtonPosition();

		void setPlayerStatus(bool play) { m_isPlay = play; }

private slots:
		void onSliderPressed();
		void onSliderMoved(int position);
		void onSliderRelease();
		void onSliderClicked(int value);
		void onOpenPlayList();


protected:
		void resizeEvent(QResizeEvent* event)override;


signals:
		void sig_OpenFile(const QStringList& filelist);
		void sig_OpenFloder(QString path);
		void sig_OpenPlayList();
		void sig_SliderValue(int value);
		void sig_SliderMoved(int value);
		void sig_SliderClicked(int value);

private:
		QPushButton* m_pOpenRightListButton = nullptr;
		COpenFileButton* m_pOpenFileButton = nullptr;
		CTimeSlider* m_pTimeSlider = nullptr;

		bool m_isOpenList = false;
		bool m_isPlay = false;
		bool m_bSliderPressed = false;
};

