#include "CBottomCtrlBar.h"
#include <QHBoxLayout>


CBottomCtrlBar::CBottomCtrlBar(QWidget* parent)
		:QWidget(parent)
{
		setAttribute(Qt::WA_StyledBackground);

		setMouseTracking(true);

		this->setFixedHeight(80);

		setStyleSheet("background-color:rgb(67,67,67)");

		QString label_qss = "QLabel{font-family:Microsoft Yallei;font-size:18px;color:rgb(255,255,255)}";

		m_pCurPlayTimeLabel = new QLabel(this);
		m_pCurPlayTimeLabel->setText("");
		//m_pCurPlayTimeLabel->setAlignment(Qt::AlignRight);
		m_pCurPlayTimeLabel->setFixedSize(160, 32);
		m_pCurPlayTimeLabel->setStyleSheet(label_qss);

		/*m_pTotalTimeLabel = new QLabel(this);
		m_pTotalTimeLabel->setText("");
		m_pTotalTimeLabel->setAlignment(Qt::AlignLeft);
		m_pTotalTimeLabel->setFixedSize(160, 32);
		m_pTotalTimeLabel->setStyleSheet(label_qss);*/

		m_pPlayButtonGroupWidget = new CPlayButtonGroupWidget(this);

		m_pToolBoxButton = new QPushButton(this);
		m_pToolBoxButton->setText("");
		m_pToolBoxButton->setFixedSize(32, 32);
		m_pToolBoxButton->setStyleSheet("QPushButton{image:url(:/MainWidget/resources/bottomBar/screen.svg);border:none;}");

		m_pEffectButton = new QPushButton(this);
		m_pEffectButton->setText("");
		m_pEffectButton->setFixedSize(32, 32);
		m_pEffectButton->setStyleSheet("QPushButton{image:url(:/MainWidget/resources/bottomBar/set.svg);border:none;}");

		m_pFullButton = new QPushButton(this);
		m_pFullButton->setText("");
		m_pFullButton->setFixedSize(32, 32);
		m_pFullButton->setStyleSheet("QPushButton{image:url(:/MainWidget/resources/bottomBar/full.svg);border:none;}");

		QHBoxLayout* pHLay = new QHBoxLayout(this);
		pHLay->addSpacing(3);
		pHLay->addWidget(m_pCurPlayTimeLabel);
		//pHLay->addSpacing(1);
		//pHLay->addWidget(m_pTotalTimeLabel);
		pHLay->addStretch();
		pHLay->addWidget(m_pPlayButtonGroupWidget);
		pHLay->addStretch();
		pHLay->addWidget(m_pToolBoxButton);
		pHLay->addSpacing(18);
		pHLay->addWidget(m_pEffectButton);
		pHLay->addSpacing(18);
		pHLay->addWidget(m_pFullButton);
		
		showTimeLabel(true);
		
		connect(m_pPlayButtonGroupWidget, &CPlayButtonGroupWidget::sig_play, this, &CBottomCtrlBar::sig_play);
		connect(m_pPlayButtonGroupWidget, &CPlayButtonGroupWidget::sig_stop, this, &CBottomCtrlBar::sig_stop);

		connect(m_pPlayButtonGroupWidget, &CPlayButtonGroupWidget::sig_prev, this, &CBottomCtrlBar::sig_prev);
		connect(m_pPlayButtonGroupWidget, &CPlayButtonGroupWidget::sig_next, this, &CBottomCtrlBar::sig_next);

		connect(m_pPlayButtonGroupWidget, &CPlayButtonGroupWidget::sig_VolumeMoved, this, &CBottomCtrlBar::onVolumeMoved);

		connect(m_pFullButton, &QPushButton::clicked, this, &CBottomCtrlBar::onFullButtonClicked);

}

CBottomCtrlBar::~CBottomCtrlBar()
{

}


void CBottomCtrlBar::onFullButtonClicked()
{
		emit sig_Full();
}


void CBottomCtrlBar::onVolumeMoved(int value)
{
		emit sig_VolumeMoved(value);
}

void CBottomCtrlBar::showTimeLabel(bool isShow)
{
		if (isShow)
		{
				m_pCurPlayTimeLabel->show();
				//m_pTotalTimeLabel->show();
		}
		else
		{
				m_pCurPlayTimeLabel->hide();
				//m_pTotalTimeLabel->hide();
		}
}

QString CBottomCtrlBar::formatTimeMs(const qint64& timeMs)
{
		qint64 seconds = timeMs / 1000;
		int hours = seconds / 3600;
		int mins = (seconds - hours * 3600) / 60;
		int secs = seconds - hours * 3600 - mins * 60;

		char buf[1024] = { 0 };
		if (hours < 100)
		{
				sprintf_s(buf, "%02d:%02d:%02d", hours, mins, secs);
		}
		else
		{
				sprintf_s(buf, "%d:%02d:%02d", hours, mins, secs);
		}

		return QString::fromUtf8(buf);
}

void CBottomCtrlBar::setCurPlayTime(const qint64& curMs)
{
		m_pCurPlayTimeLabel->setText(formatTimeMs(curMs));
}


void CBottomCtrlBar::setCurPlayTime(const QString& time)
{
		m_pCurPlayTimeLabel->setText(time);
}

void CBottomCtrlBar::setVolumeValue(int value)
{
		m_pPlayButtonGroupWidget->setVolumeValue(value);
}


//void CBottomCtrlBar::setTotalTime(const qint64& totalMs)
//{
//		m_pTotalTimeLabel->setText("/" + formatTimeMs(totalMs));
//}


//窗口改变大小，播放按钮总是居中
void CBottomCtrlBar::resizeEvent(QResizeEvent* event)
{
		if (m_pPlayButtonGroupWidget)
		{
				int x = this->width() / 2 - m_pPlayButtonGroupWidget->width() / 2;
				int y = this->height() / 2 - m_pPlayButtonGroupWidget->height() / 2;
				m_pPlayButtonGroupWidget->move(x, y);
		}
}
