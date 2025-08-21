/*  libvlc¹¦ÄÜ·â×°   */

#pragma once

#ifdef _WIN32
#include <basetsd.h>
typedef SSIZE_T ssize_t;
#endif

#include "vlc/vlc.h"
#include <QObject>
#include <vector>

using namespace std;

//#pragma comment(lib, "libvlc.lib")
//#pragma comment(lib, "libvlccore.lib")

class CVlcKits : public QObject
{
    Q_OBJECT

public:
		CVlcKits();
		~CVlcKits();

    int initVlc();

    libvlc_media_player_t* media_player();

    void setTimeSliderPos(const int& value);
    void setVolumeSliderPos(const int& value);
    void setTimeText(const QString& str);
    libvlc_time_t getDuration();
    void setCurrentDuration(libvlc_time_t value);

    int play(QStringList fileList, void* hwnd);
    void play();
    void pause();
    void stop();
    void prev();
    void next();

    void setVolumeSliderValue(int value);

    void updateCurrentMedia(CVlcKits* pThis);

    vector<libvlc_time_t> getvecDurations();
    int getCurrentIndex();
    void addCurrentIndex();
    void prevCurrentIndex();

    void setVideoPosition(int value);

    void playItem(int index);


signals:
        void sig_TimeSliderPos(int value);
        void sig_VolumeSliderPos(int value);
        void sig_UpdateTimeText(const QString& str);
        void sig_CurrentIndex(int index);

private:
    libvlc_instance_t* m_pInstance = nullptr;
    libvlc_media_player_t* m_pMediaPlayer = nullptr;
    libvlc_media_t* m_pMedia = nullptr;
    libvlc_event_manager_t* m_pEvent_manager = nullptr;

    libvlc_media_list_player_t* m_pMediaPlayerList = nullptr;
    libvlc_media_list_t* m_pMediaList = nullptr;

    libvlc_time_t m_CurrentDuration = 0;

    vector<libvlc_time_t> m_vecDurations;
    
    int m_CurrentIndex = 0;
    
};

