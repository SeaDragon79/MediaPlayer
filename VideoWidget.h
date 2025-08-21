
/*ÊÓÆµ²¥·Å´°¿Ú*/

#pragma once
#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QAbstractNativeEventFilter>

#include "CVideoWidgetTopWidget.h"

class VideoWidget : public QWidget, public QAbstractNativeEventFilter
{
		Q_OBJECT

public:
		VideoWidget(QWidget* parent = nullptr);
		~VideoWidget();

		void showTopWidget(bool show);
		void setPlayStatus(bool play);

		void setSliderValue(int value);

protected:
		void resizeEvent(QResizeEvent* event)override;
		bool nativeEventFilter(const QByteArray& eventType, void* message, long* result)override;

		/*void enterEvent(QEvent* event)override;
		void leaveEvent(QEvent* event)override;*/

private slots:
		void onSliderMoved(int value);
		void onSliderClicked(int value);

signals:
		void sig_OpenFile(const QStringList& fileList);
		void sig_OpenFloder(QString path);
		void sig_OpenPlayList();
		void sig_TotalMs(const qint64& duration);
		void sig_VideoPositionChanged(const qint64& pos);
		void sig_SliderMoved(int value);
		void sig_SliderClicked(int value);

private:
		QPoint m_dPos;
		CVideoWidgetTopWidget* m_pTopWidget = nullptr;

		bool m_isPlay = false;
};

