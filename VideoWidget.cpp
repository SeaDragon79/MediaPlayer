#include "VideoWidget.h"
#include <QPainter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenu>
#include <QDebug>
#include <QApplication>
#include <QMessageBox>
#include <qt_windows.h>


VideoWidget::VideoWidget(QWidget* parent)
		:QWidget(parent)
{
		setAttribute(Qt::WA_StyledBackground);

		this->setAttribute(Qt::WA_OpaquePaintEvent);

		qApp->installNativeEventFilter(this);

		setMouseTracking(true);

		setStyleSheet("background-color:balck");


		QString openfile_button_qss = "QPushButton::menu-indicator:open("
				"image:url(:/MainWidget/resources/vedioWidget/down.svg);"
				"subcontrol-position:right center;"
				"subcontrol-origin:padding;border:none;}"
				"QPushButton::menu-indicator:closed("
				"image:url(:/MainWidget/resources/vedioWidget/up.svg);"
				"subcontrol-position:right center;"
				"subcontrol-origin:padding;border:none;}";

		setMinimumSize(800, 450);

		m_pTopWidget = new CVideoWidgetTopWidget(this);

		connect(m_pTopWidget, &CVideoWidgetTopWidget::sig_OpenFile, this, &VideoWidget::sig_OpenFile);
		connect(m_pTopWidget, &CVideoWidgetTopWidget::sig_OpenPlayList, this, &VideoWidget::sig_OpenPlayList);
		connect(m_pTopWidget, &CVideoWidgetTopWidget::sig_SliderMoved, this, &VideoWidget::onSliderMoved);
		connect(m_pTopWidget, &CVideoWidgetTopWidget::sig_SliderClicked, this, &VideoWidget::onSliderClicked);

}

VideoWidget::~VideoWidget()
{

}

void VideoWidget::setSliderValue(int value)
{
		m_pTopWidget->setSliderValue(value);
}

void VideoWidget::onSliderMoved(int value)
{
		emit sig_SliderMoved(value);
}

void VideoWidget::onSliderClicked(int value)
{
		emit sig_SliderClicked(value);
}


void VideoWidget::showTopWidget(bool show)
{
		if (show)
		{
				m_pTopWidget->show();
				m_pTopWidget->showOpenBtn(false);
				m_pTopWidget->showSlider(true);
				m_pTopWidget->showRightBtn(true);
		}
		else
		{
				m_pTopWidget->hide();
		}
}

void VideoWidget::setPlayStatus(bool play)
{
		m_isPlay = play;
}

void VideoWidget::resizeEvent(QResizeEvent* event)
{
		m_dPos = this->pos();

		QPoint pos = this->mapToGlobal(QPoint(0, 0));

		m_pTopWidget->resize(this->width(), this->height());
		m_pTopWidget->move(pos);
		m_pTopWidget->show();
}

bool VideoWidget::nativeEventFilter(const QByteArray& eventType, void* message, long* result)
{
		if (eventType == "windows_generic_MSG" || eventType == "windows_dispatcher_MSG") {
				MSG* pMsg = reinterpret_cast<MSG*>(message);
				if (pMsg->message == 1025) {
						QPoint pos = this->window()->mapToGlobal(QPoint(0, 0));

						// ÒÆ¶¯¶¥²ã¿ØÖÆ´°¿Ú
						m_pTopWidget->move(pos + m_dPos);
				}
		}
		return false;
}


