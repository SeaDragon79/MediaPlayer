#pragma once
#include <QSlider>

class CTimeSlider : public QSlider
{
		Q_OBJECT

public:
		CTimeSlider(QWidget* parent = nullptr);
		~CTimeSlider();
		
private:
    // 事件过滤器函数
    bool eventFilter(QObject* watched, QEvent* event) override;


    void slider_mouseLButtonPress(QObject* slider, QEvent* event);  
    void setTimeSliderRange(qint64 value);  
    void setSliderValue(int value);    

private slots:
    void onSliderPressed();          
    void onSliderMoved(int position); 
    void onSliderRelease();           

signals:
    void sig_SliderMoved(int value);
    void sig_SliderClicked(int value);
    

private:
    bool m_bSliderPressed = false;
    int m_SliderHeight = 15;

    QSlider* m_pSlider = nullptr;
};

