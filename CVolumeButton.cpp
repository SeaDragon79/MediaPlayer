#include "CVolumeButton.h"
#include <QMouseEvent>
#include <QStylePainter>
#include <QStyleOptionButton>
#include <iostream>
#include <QThread>

CVolumeButton::CVolumeButton(QWidget* parent)
		:QPushButton(parent)
{
		this->setFixedSize(32, 32);

		setStyleSheet("QPushButton{background-image:url(:/MainWidget/resources/bottomBar/volume.svg);border:none;}");

		connect(m_pVolumeSliderDialog, &CVolumeSliderDialog::sig_VolumeMoved, [=](int value) {
				emit sig_VolumeMoved(value);
				});

		connect(m_pVolumeSliderDialog, &CVolumeSliderDialog::sig_SliderValueChanged, [=](int value) {
				emit sig_VolumeValue(value);
				});
}

CVolumeButton::~CVolumeButton()
{
}


void CVolumeButton::setVolumeValue(int value)
{
		if (m_pVolumeSliderDialog) {
				m_pVolumeSliderDialog->setSliderValue(value);
		}
}

void CVolumeButton::paintEvent(QPaintEvent* event)
{
		QStylePainter p(this);
		QStyleOptionButton option;
		initStyleOption(&option);
		p.drawControl(QStyle::CE_PushButton, option);
}

void CVolumeButton::enterEvent(QEvent* event)
{
		if (!m_pVolumeSliderDialog)
				m_pVolumeSliderDialog = new CVolumeSliderDialog(this);

		QPoint p1 = this->mapToGlobal(QPoint(0, 0));
		QRect rect1 = this->rect();
		QRect rect2 = m_pVolumeSliderDialog->rect();

		int x = p1.x() + (rect1.width() - rect2.width()) / 2;
		int y = p1.y() - rect2.height() - 5;
		m_pVolumeSliderDialog->move(x, y);

		m_pVolumeSliderDialog->show();
		startTimer(250);

		connect(m_pVolumeSliderDialog, &CVolumeSliderDialog::sig_SliderValueChanged, [=](int value){
				emit sig_VolumeValue(value);
				});

		connect(m_pVolumeSliderDialog, &CVolumeSliderDialog::sig_VolumeMoved, [=](int value) {
				emit sig_VolumeMoved(value);
				});
}

void CVolumeButton::mousePressEvent(QMouseEvent* event)
{
		if (event->button() == Qt::LeftButton)
		{
				m_isMute = !m_isMute;
				if (m_isMute)
				{
						if (m_pVolumeSliderDialog)
								m_pVolumeSliderDialog->setSliderValue(0);
				}
				else
				{
						if (m_pVolumeSliderDialog)
								m_pVolumeSliderDialog->setSliderValue(50);
				}
		}
}

void CVolumeButton::timerEvent(QTimerEvent* event)
{
		if ((m_pVolumeSliderDialog != nullptr) && (m_pVolumeSliderDialog->isVisible()))
		{
				QPoint p1 = QCursor::pos();
				if (m_pVolumeSliderDialog)
				{
						QRect rect1 = this->rect();
						QRect rect2 = m_pVolumeSliderDialog->rect();
						QRect rect3 = m_pVolumeSliderDialog->geometry();

						QPoint p2 = this->mapToGlobal(QPoint(0, 0));

						QRect area(rect3.left(), rect3.top(), rect2.width(), p2.y() + rect1.height() - rect3.top());

						if (!area.contains(p1))
						{
								m_pVolumeSliderDialog->hide();
						}
				}
		}
		else
		{
				killTimer(event->timerId());
		}
}
