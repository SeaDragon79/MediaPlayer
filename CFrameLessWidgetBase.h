#pragma once
#include <QWidget>
#include <qt_windows.h>
#include <windows.h>        
#include <windowsx.h>


class CFrameLessWidgetBase :
    public QWidget
{
public:
    CFrameLessWidgetBase(QWidget* parent = nullptr);
    ~CFrameLessWidgetBase();

protected:
    bool nativeEvent(const QByteArray& eventType, void* message, long* result)override;


private:
    int boundaryWidth = 5;
};

