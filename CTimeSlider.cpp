#include "CTimeSlider.h"
#include <QEvent>
#include <QMouseEvent>

CTimeSlider::CTimeSlider(QWidget* parent)
		:QSlider(parent)
{
		setAttribute(Qt::WA_StyledBackground);

		this->setOrientation(Qt::Horizontal);
		this->setFixedHeight(m_SliderHeight);

		installEventFilter(this);

		m_pSlider = new QSlider(this);

		QString slider_qss =
				"QSlider {"
				"    background: transparent;"
				"    border-style: outset;"
				"    border-radius: 10px;"
				"}"
				"QSlider::groove:horizontal {"
				"    height: 12px;"
				"    background: #E0E0E0;"
				"    margin: 2px 0;"
				"}"
				"QSlider::handle:horizontal {"
				"    background: white;"
				"    width: 12px;"
				"    height: 12px;"
				"    margin: -5px 6px -5px 6px;"
				"    border-radius: 11px;"
				"    border: 3px solid #FFFFFF;"
				"}"
				"QSlider::add-page:horizontal {"
				"    background-color: #FF7826;"
				"    border-radius: 2px;"
				"}"
				"QSlider::sub-page:horizontal {"
				"    background-color: #4A90E2;"
				"		 height: 4px;"
				"		 border-radius: 2px; "
				"}";




		m_pSlider->setStyleSheet(slider_qss);

		connect(m_pSlider, &QSlider::sliderPressed, this, &CTimeSlider::onSliderPressed);
		connect(m_pSlider, &QSlider::sliderMoved, this, &CTimeSlider::onSliderMoved);
		connect(m_pSlider, &QSlider::sliderReleased, this, &CTimeSlider::onSliderRelease);

}

CTimeSlider::~CTimeSlider()
{
}

bool CTimeSlider::eventFilter(QObject* watched, QEvent* event)
{
		if (event->type() == QEvent::MouseButtonPress && watched == this)
		{
				slider_mouseLButtonPress(watched, event);
		}

		return QWidget::eventFilter(watched, event);
}

void CTimeSlider::slider_mouseLButtonPress(QObject* slider, QEvent* event)
{
		do
		{
				//只处理鼠标左键的按下事件

				QSlider* sliderCtrl = static_cast<QSlider*>(slider);
				QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
				if (Qt::LeftButton != mouseEvent->button())
				{
						break;
				}

				int cxctl = 0;
				int cxwnd = 0;
				int mxpos = 0;

				if (Qt::Horizontal == sliderCtrl->orientation())
				{
						cxctl = sliderCtrl->minimumSizeHint().width();
						cxwnd = sliderCtrl->width();
						if (sliderCtrl->invertedAppearance())
								mxpos = cxwnd - mouseEvent->x();
						else
								mxpos = mouseEvent->x();
				}
				else
				{
						cxctl = sliderCtrl->minimumSizeHint().height();
						cxwnd = sliderCtrl->height();
						if (sliderCtrl->invertedAppearance())
								mxpos = mouseEvent->y();
						else
								mxpos = cxwnd - mouseEvent->y();
				}

				if (cxwnd <= cxctl)
				{
						break;
				}

				int scpos = sliderCtrl->minimum() + (int)((sliderCtrl->maximum() - sliderCtrl->minimum()) *
						((mxpos - cxctl / 2.0) / (cxwnd - cxctl)));

				if (sliderCtrl->sliderPosition() == scpos)
				{
						break;
				}

				sliderCtrl->setSliderPosition(scpos);
				
				sliderCtrl->setValue(scpos);
				emit sig_SliderClicked(scpos);
				
		} while(0);
}

void CTimeSlider::onSliderPressed()
{
		m_bSliderPressed = true;
}

void CTimeSlider::setTimeSliderRange(qint64 value)
{
		m_pSlider->setRange(0, value);
}

void CTimeSlider::setSliderValue(int value)
{
		m_pSlider->setValue(value);
}

void CTimeSlider::onSliderMoved(int position)
{
		emit sig_SliderMoved(position);
}

void CTimeSlider::onSliderRelease()
{
		m_bSliderPressed = false;
}