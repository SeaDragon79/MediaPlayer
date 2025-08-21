#include "CFrameLessWidgetBase.h"

CFrameLessWidgetBase::CFrameLessWidgetBase(QWidget* parent)
{
		this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
		setAttribute(Qt::WA_Hover);
}

CFrameLessWidgetBase::~CFrameLessWidgetBase()
{
}

bool CFrameLessWidgetBase::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
    MSG* msg = (MSG*)message;
    switch (msg->message)
    {
    case WM_NCHITTEST:
        int xPos = GET_X_LPARAM(msg->lParam) - this->frameGeometry().x();
        int yPos = GET_Y_LPARAM(msg->lParam) - this->frameGeometry().y();
        if (xPos < boundaryWidth && yPos < boundaryWidth)                    //���Ͻ�
            *result = HTTOPLEFT;
        else if (xPos >= width() - boundaryWidth && yPos < boundaryWidth)          //���Ͻ�
            *result = HTTOPRIGHT;
        else if (xPos < boundaryWidth && yPos >= height() - boundaryWidth)         //���½�
            *result = HTBOTTOMLEFT;
        else if (xPos >= width() - boundaryWidth && yPos >= height() - boundaryWidth)//���½�
            *result = HTBOTTOMRIGHT;
        else if (xPos < boundaryWidth)                                     //���
            *result = HTLEFT;
        else if (xPos >= width() - boundaryWidth)                              //�ұ�
            *result = HTRIGHT;
        else if (yPos < boundaryWidth)                                       //�ϱ�
            *result = HTTOP;
        else if (yPos >= height() - boundaryWidth)                             //�±�
            *result = HTBOTTOM;
        else              //�������ֲ�����������false�����������¼�����������
            return false;
        return true;
    }
    return false;         //�˴�����false�����������¼�����������

}
