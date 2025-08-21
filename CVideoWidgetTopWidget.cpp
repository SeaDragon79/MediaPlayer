#include "CVideoWidgetTopWidget.h"
#include <QPropertyAnimation>

#define TIME_SLIDER_HEIGHT 20

CVideoWidgetTopWidget::CVideoWidgetTopWidget(QWidget* parent)
		:QWidget(parent)
{
		// 设置窗口属性
		setAttribute(Qt::WA_StyledBackground);
		setAttribute(Qt::WA_Hover);
		this->setAttribute(Qt::WA_TranslucentBackground); // 设置透明背景
		setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::SubWindow); // 无边框窗口
		setAutoFillBackground(true);
		setMinimumSize(800, 450); // 设置最小窗口尺寸
		setMouseTracking(true); // 启用鼠标跟踪

		// 初始化按钮
		m_pOpenFileButton = new COpenFileButton(this);
		m_pOpenRightListButton = new QPushButton(this);
		m_pOpenRightListButton->setText(u8""); // 设置空文本（使用UTF-8编码）
		m_pOpenRightListButton->setFixedSize(36, 80); // 固定按钮尺寸

		QString qssRightBtn_close = "QPushButton{"
				"image: url(:/MainWidget/resources/vedioWidget/left.svg);"
				"background-color:rgb(54,54,54);"
				"background-repeat: no-repeat;"
				"border: none;"
				"}";

		m_pOpenRightListButton->setStyleSheet(qssRightBtn_close);

		m_pTimeSlider = new CTimeSlider(this);

		QString slider_qss =
				"QSlider {"
				"    background: transparent;"
				"    border-style: outset;"
				"    border-radius: 10px;"
				"}"
				"QSlider::groove:horizontal {"
				"    height: 12px;"
				"    background-color: #E0E0E0;"
				"    margin: 2px 0;"
				"}"
				"QSlider::handle:horizontal {"
				"    background: white;"
				"    width: 16px;"
				"    height: 16px;"
				"    margin: -5px 6px -5px 6px;"
				"    border-radius: 11px;"
				"    border: 3px solid #ffffff;"
				"}"
				"QSlider::add-page:horizontal {"
				"    background-color: #E0E0E0;"
				"    border-radius: 2px;"
				"}"
				"QSlider::sub-page:horizontal {"
				"    background-color: #4A90E2;"
				"		 height: 4px;"
				"		 border-radius: 2px; "
				"}";

		m_pTimeSlider->setStyleSheet(slider_qss);

		connect(m_pOpenFileButton, &COpenFileButton::sig_openfile, this, &CVideoWidgetTopWidget::sig_OpenFile);
		connect(m_pOpenFileButton, &COpenFileButton::sig_openFloder, this, &CVideoWidgetTopWidget::sig_OpenFloder);
		connect(m_pOpenRightListButton, &QPushButton::clicked, this, &CVideoWidgetTopWidget::onOpenPlayList);

		connect(m_pTimeSlider, &QSlider::sliderPressed, this, &CVideoWidgetTopWidget::onSliderPressed);
		connect(m_pTimeSlider, &QSlider::sliderMoved, this, &CVideoWidgetTopWidget::onSliderMoved);
		connect(m_pTimeSlider, &QSlider::sliderReleased, this, &CVideoWidgetTopWidget::onSliderRelease);
		connect(m_pTimeSlider, &CTimeSlider::sig_SliderClicked, this, &CVideoWidgetTopWidget::onSliderClicked);
}

CVideoWidgetTopWidget::~CVideoWidgetTopWidget()
{
}



void CVideoWidgetTopWidget::setTimeSliderRange(qint64 value)
{
		m_pTimeSlider->setRange(0, value);
}

void CVideoWidgetTopWidget::setSliderValue(int value)
{
		m_pTimeSlider->setValue(value);
}

void CVideoWidgetTopWidget::showRightBtn(bool flag)
{
		flag ? m_pOpenRightListButton->show() : m_pOpenRightListButton->hide();
}

void CVideoWidgetTopWidget::showOpenBtn(bool flag)
{
		flag ? m_pOpenFileButton->show() : m_pOpenFileButton->hide();
}

void CVideoWidgetTopWidget::showSlider(bool flag)
{
		flag ? m_pTimeSlider->show() : m_pTimeSlider->hide();
}


void CVideoWidgetTopWidget::onSliderPressed()
{
		m_bSliderPressed = true;
		
}


void CVideoWidgetTopWidget::onSliderMoved(int position)
{
		emit sig_SliderMoved(position);
}

void CVideoWidgetTopWidget::onSliderRelease()
{
		qint64 value = m_pTimeSlider->value();
		emit sig_SliderValue(value);
		m_bSliderPressed = false;
}

void CVideoWidgetTopWidget::onSliderClicked(int value)
{
		emit sig_SliderClicked(value);
}


// 更新按钮位置
void CVideoWidgetTopWidget::updateButtonPosition()
{
		int x2 = width() - m_pOpenRightListButton->width(); 
		int y2 = height() / 2 - m_pOpenRightListButton->height() / 2;

		if (m_isOpenList) {
				m_pOpenRightListButton->move(x2 - 200, y2); // 向左偏移200px
		}
		else {
				m_pOpenRightListButton->move(x2, y2); // 正常右侧位置
		}
}

void CVideoWidgetTopWidget::playListBtnChanged()
{
		m_isOpenList = !m_isOpenList; // 切换状态
		if (m_isOpenList) //playList is opened
		{
				QString qssRightBtn_close = "QPushButton{"
						"image: url(:/MainWidget/resources/vedioWidget/right.svg);"
						"background-color:rgb(54,54,54);"
						"background-repeat: no-repeat;"
						"border: none;"
						"}";

				m_pOpenRightListButton->setStyleSheet(qssRightBtn_close);
				
		}
		else
		{
				QString qssRightBtn_open = "QPushButton{"
						"image: url(:/MainWidget/resources/vedioWidget/left.svg);"
						"background-color:rgb(54,54,54);"
						"background-repeat: no-repeat;"
						"border: none;"
						"}";

				m_pOpenRightListButton->setStyleSheet(qssRightBtn_open);
				
		}
}


void CVideoWidgetTopWidget::onOpenPlayList()
{
		playListBtnChanged();
		emit sig_OpenPlayList();
}

void CVideoWidgetTopWidget::resizeEvent(QResizeEvent* event)
{
		if (m_pOpenFileButton && m_pOpenRightListButton && m_pTimeSlider)
		{
				// 将"打开文件"按钮居中显示
				int x1 = this->width() / 2 - m_pOpenFileButton->width() / 2;
				int y1 = this->height() / 2 - m_pOpenFileButton->height() / 2;
				m_pOpenFileButton->move(x1, y1);

				// 将右侧列表按钮放在窗口右侧居中
				int x2 = this->width() - m_pOpenRightListButton->width();
				int y2 = this->height() / 2 - m_pOpenRightListButton->height() / 2;
				m_pOpenRightListButton->move(x2, y2);

				// 将时间滑块放在窗口底部
				int x3 = 0;
				int y3 = this->height() - TIME_SLIDER_HEIGHT;
				m_pTimeSlider->move(x3, y3);  
				m_pTimeSlider->resize(this->width(), TIME_SLIDER_HEIGHT);
		}
}
