#include "CVlcKits.h"
#include <iostream>
#include <QDir>
#include <QDebug>


// 辅助函数：更新当前媒体信息
void updateCurrentMedia(CVlcKits* pThis) {
    int _index = pThis->getCurrentIndex();
    int vSize = pThis->getvecDurations().size();

    // 循环索引处理
    if (_index > vSize) {
        _index = (_index % vSize == 0) ? vSize : (_index % vSize);
    }
    else if (_index < 1) {
        _index = vSize;  // 处理索引小于1的情况
    }

    // 更新当前媒体时长
    if (_index > 0 && _index <= vSize) {
        libvlc_time_t duration = pThis->getvecDurations()[_index - 1];
        pThis->setCurrentDuration(duration);
        qDebug() << "Switched to media index:" << _index << "Duration:" << duration;
    }
    else {
        qWarning() << "Invalid media index:" << _index;
    }

    emit pThis->sig_CurrentIndex(_index);
}


void vlc_callback(const struct libvlc_event_t* p_event, void* p_data)
{
    CVlcKits* pThis = static_cast<CVlcKits*>(p_data);
    if (pThis)
    {
        switch (p_event->type)
        {
        case libvlc_MediaPlayerPositionChanged:
        {
            float pos = libvlc_media_player_get_position(pThis->media_player());
            pThis->setTimeSliderPos(pos * 100);

            qint64 curSecs = libvlc_media_player_get_time(pThis->media_player()) / 1000;

            int curHour = curSecs / 3600;
            int curMinute = (curSecs - curHour * 3600) / 60;
            int curSec = curSecs - curHour * 3600 - curMinute * 60;

            char buf1[256]{ 0 };
            sprintf_s(buf1, "%02d:%02d:%02d", curHour, curMinute, curSec);
            QString str1(buf1);


            qint64 totalsecs = pThis->getDuration();
            int _Hour = totalsecs / 3600;
            int _Minute = (totalsecs - _Hour * 3600) / 60;
            int _sec = totalsecs - _Hour * 3600 - _Minute * 60;

            char buf2[256]{ 0 };
            sprintf_s(buf2, "%02d:%02d:%02d", _Hour, _Minute, _sec);
            QString str2(buf2);

            QString text = str1 + "/" + str2;
            pThis->setTimeText(text);

        }
        break;

        case libvlc_MediaPlayerAudioVolume:
        {
            int volume = libvlc_audio_get_volume(pThis->media_player());
            pThis->setVolumeSliderPos(volume);
            emit pThis->sig_VolumeSliderPos(volume);
        }
        break;

        case libvlc_MediaPlayerMediaChanged: {
            // 媒体改变时自动进入下一项
            pThis->addCurrentIndex();
            updateCurrentMedia(pThis);
            break;
        }

        case libvlc_MediaPlayerBackward: {  // 上一个
            qDebug() << "Previous requested. CurrentIndex =" << pThis->getCurrentIndex();
            pThis->prevCurrentIndex();
            updateCurrentMedia(pThis);
            break;
        }

        case libvlc_MediaPlayerForward: {   // 下一个
            qDebug() << "Next requested. CurrentIndex =" << pThis->getCurrentIndex();
            pThis->addCurrentIndex();
            updateCurrentMedia(pThis);
            break;
        }

        }
    }
}



CVlcKits::CVlcKits()
{
}

CVlcKits::~CVlcKits()
{
    if (m_pMediaPlayer)
    {
        libvlc_media_player_release(m_pMediaPlayer);
        m_pMediaPlayer = nullptr;
    }

    if (m_pInstance)
    {
        libvlc_release(m_pInstance);
        m_pInstance = nullptr;
    }
}





///<summary>
/// 初始化libvlc
///</summary>
/// <returns>
/// 0 success
/// -1, libvlc_new failed
/// -2, libvlc_media_player_new failed
/// </returns>

int CVlcKits::initVlc()
{
    //vlc初始化
    m_pInstance = libvlc_new(0, nullptr);
    if (m_pInstance)
    {
        m_pMediaPlayer = libvlc_media_player_new(m_pInstance);
        if (m_pMediaPlayer)
        {
            m_pEvent_manager = libvlc_media_player_event_manager(m_pMediaPlayer);

            libvlc_event_attach(m_pEvent_manager, libvlc_MediaPlayerPositionChanged, vlc_callback, this);

            libvlc_event_attach(m_pEvent_manager, libvlc_MediaPlayerAudioVolume, vlc_callback, this);

            libvlc_event_attach(m_pEvent_manager, libvlc_MediaPlayerMediaChanged, vlc_callback, this);
        }
        else
        {
            libvlc_release(m_pInstance);
            return -2;
        }
    }
    else
    {
        return -1; 
    }

		return 0;
}

libvlc_media_player_t* CVlcKits::media_player()
{
		return m_pMediaPlayer;
}

void CVlcKits::setTimeSliderPos(const int& value)
{
    emit sig_TimeSliderPos(value);
}

void CVlcKits::setVolumeSliderPos(const int& value)
{
    emit sig_VolumeSliderPos(value);
}

void CVlcKits::setTimeText(const QString& str)
{
    emit sig_UpdateTimeText(str);
}

libvlc_time_t CVlcKits::getDuration()
{
    return m_CurrentDuration;
}

void CVlcKits::setCurrentDuration(libvlc_time_t value)
{
    m_CurrentDuration = value;
}



int CVlcKits::play(QStringList fileList, void* hwnd)
{
     m_pMediaPlayerList = libvlc_media_list_player_new(m_pInstance);
     m_pMediaList = libvlc_media_list_new(m_pInstance);

     int size = fileList.size();
     for (int i = 0; i < size; i++)
     {
         QString fileName = fileList[i];
         fileName = QDir::toNativeSeparators(fileName);  //路径转义

         //设置路径
         libvlc_media_t* _pMedia = libvlc_media_new_path(m_pInstance, fileName.toStdString().c_str());
         if (!_pMedia)
         {
             return -1;
         }

         libvlc_media_list_add_media(m_pMediaList, _pMedia);
         
         libvlc_media_parse(_pMedia);
         libvlc_time_t _duration = libvlc_media_get_duration(_pMedia);
         if (_duration == -1)
         {
             return -2;
         }

         m_vecDurations.push_back(_duration / 1000);

         libvlc_media_release(_pMedia);
     }

     //设置播放循环模式
     libvlc_media_list_player_set_playback_mode(m_pMediaPlayerList, libvlc_playback_mode_loop);

     libvlc_media_list_player_set_media_list(m_pMediaPlayerList, m_pMediaList);
     libvlc_media_list_player_set_media_player(m_pMediaPlayerList, m_pMediaPlayer);
     libvlc_media_player_set_hwnd(m_pMediaPlayer, hwnd);
     libvlc_media_list_player_play(m_pMediaPlayerList);


     return 0;
}


void CVlcKits::play()
{
    if (libvlc_media_player_get_state(m_pMediaPlayer) == libvlc_state_t::libvlc_Paused 
        || libvlc_media_player_get_state(m_pMediaPlayer) == libvlc_state_t::libvlc_Stopped)
    {
        //libvlc_media_player_play(m_pMediaPlayer);
        libvlc_media_list_player_play(m_pMediaPlayerList);
    }
    else if (libvlc_media_player_get_state(m_pMediaPlayer) == libvlc_state_t::libvlc_Playing)
    {
        //libvlc_media_player_pause(m_pMediaPlayer);
        libvlc_media_list_player_pause(m_pMediaPlayerList);
    }
}

void CVlcKits::pause()
{
    if (libvlc_media_player_get_state(m_pMediaPlayer) == libvlc_state_t::libvlc_Playing)
    {
        libvlc_media_player_pause(m_pMediaPlayer);
    }
}

void CVlcKits::stop()
{
    if (libvlc_media_player_get_state(m_pMediaPlayer) == libvlc_state_t::libvlc_Playing
        || libvlc_media_player_get_state(m_pMediaPlayer) == libvlc_state_t::libvlc_Paused)
    {
        libvlc_media_list_player_stop(m_pMediaPlayerList);
    }
}


void CVlcKits::prev()
{
    libvlc_media_list_player_previous(m_pMediaPlayerList);
}


void CVlcKits::next()
{
    libvlc_media_list_player_next(m_pMediaPlayerList);
}


vector<libvlc_time_t> CVlcKits::getvecDurations()
{
    return m_vecDurations;
}

int CVlcKits::getCurrentIndex()
{
    return m_CurrentIndex;
}

void CVlcKits::addCurrentIndex()
{
    m_CurrentIndex++;
}

void CVlcKits::prevCurrentIndex()
{
    m_CurrentIndex--;
}

void CVlcKits::setVideoPosition(int value)
{
    libvlc_media_player_set_position(m_pMediaPlayer, value / 100.0);
}


void CVlcKits::setVolumeSliderValue(int value)
{
    //设置播放声音
    libvlc_audio_set_volume(m_pMediaPlayer, value);
}


// 播放指定索引的媒体
void CVlcKits::playItem(int index) 
{
    libvlc_media_list_player_play_item_at_index(m_pMediaPlayerList, index);
}