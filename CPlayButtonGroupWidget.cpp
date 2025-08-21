#include "CPlayButtonGroupWidget.h"
#include <QHBoxLayout>

CPlayButtonGroupWidget::CPlayButtonGroupWidget(QWidget* parent)
		:QWidget(parent)
{
		this->setFixedHeight(80);
		this->setFixedWidth(32 * 4 + 64 + 10 * 4 + 10);

		m_pStopButton = new QPushButton(this);
		m_pStopButton->setText("");
		m_pStopButton->setFixedSize(32, 32);
		m_pStopButton->setStyleSheet("QPushButton{image:url(:/MainWidget/resources/bottomBar/stop.svg);border:none;}");

		m_pPrevButton = new QPushButton(this);
		m_pPrevButton->setText("");
		m_pPrevButton->setFixedSize(32, 32);
		m_pPrevButton->setStyleSheet("QPushButton{image:url(:/MainWidget/resources/bottomBar/prev.svg);border:none;}");

		m_pPlayButton = new QPushButton(this);
		m_pPlayButton->setText("");
		m_pPlayButton->setFixedSize(64, 64);
		m_pPlayButton->setStyleSheet("QPushButton{image:url(:/MainWidget/resources/bottomBar/play.svg);border:none;}");
		
		m_pNextButton = new QPushButton(this);
		m_pNextButton->setText("");
		m_pNextButton->setFixedSize(32, 32);
		m_pNextButton->setStyleSheet("QPushButton{image:url(:/MainWidget/resources/bottomBar/next.svg);border:none;}");

		m_pVolumeButton = new CVolumeButton(this);
		m_pVolumeButton->setText("");
		m_pVolumeButton->setFixedSize(32, 32);
		m_pVolumeButton->setStyleSheet("QPushButton{image:url(:/MainWidget/resources/bottomBar/volume.svg);border:none;}");

		QHBoxLayout* pHLay = new QHBoxLayout(this);
		pHLay->addWidget(m_pStopButton);
		pHLay->setSpacing(8);
		pHLay->addWidget(m_pPrevButton);
		pHLay->setSpacing(8);
		pHLay->addWidget(m_pPlayButton);
		pHLay->setSpacing(8);
		pHLay->addWidget(m_pNextButton);
		pHLay->setSpacing(8);
		pHLay->addWidget(m_pVolumeButton);

		this->setLayout(pHLay);

		connect(m_pPlayButton, &QPushButton::clicked, this, &CPlayButtonGroupWidget::sig_play);
		connect(m_pStopButton, &QPushButton::clicked, this, &CPlayButtonGroupWidget::sig_stop);
		connect(m_pPrevButton, &QPushButton::clicked, this, &CPlayButtonGroupWidget::sig_prev);
		connect(m_pNextButton, &QPushButton::clicked, this, &CPlayButtonGroupWidget::sig_next);
		connect(m_pVolumeButton, &CVolumeButton::sig_VolumeMoved, this, &CPlayButtonGroupWidget::onVolumeMoved);


}

CPlayButtonGroupWidget::~CPlayButtonGroupWidget()
{
}

void CPlayButtonGroupWidget::onVolumeMoved(int value)
{
		emit sig_VolumeMoved(value);
}

void CPlayButtonGroupWidget::setVolumeValue(int value)
{
		m_pVolumeButton->setVolumeValue(value);
}