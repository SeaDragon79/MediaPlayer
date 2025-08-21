#pragma once
#include <QPushButton>
#include "CVolumeSliderDialog.h"
class CVolumeButton : public QPushButton
{
		Q_OBJECT
public:
		CVolumeButton(QWidget* parent = nullptr);
		~CVolumeButton();

		bool getMute() const
		{
				return m_isMute;
		}

		void setMute(bool mute) { m_isMute = mute; }

		void setVolumeValue(int value);

signals:
		void sig_VolumeValue(int value);
		void sig_VolumeMoved(int value);

protected:
		void paintEvent(QPaintEvent* event)override;
		void enterEvent(QEvent* event)override;
		void mousePressEvent(QMouseEvent* event)override;
		void timerEvent(QTimerEvent* event)override;

private:
		bool m_isMute = false;
		CVolumeSliderDialog* m_pVolumeSliderDialog = nullptr;
};

