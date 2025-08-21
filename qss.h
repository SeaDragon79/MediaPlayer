#pragma once
#include <string>
using namespace std;

string logo_button_qss = R"(
    QPushButton {
        background-color:rgb(54, 54, 54);
        border:none;
        font-family:Microsoft Yallei;
        font-size:18px;
        color:rgb(255, 255, 255);
    }

    QPushButton::menu-indicator:open{
        image:url(:/MainWidget/resources/titleBar/down.svg);
        subcontrol-position:right center;
        subcontrol-origin:padding;border:none;
    }

    QPushButton::menu-indicator:closed{
        image:url(:/MainWidget/resources/titleBar/up.svg);
        subcontrol-position:right center;
        subcontrol-origin:padding;border:none;
    })";

string menu_qss = R"(
    QMenu{background-color:rgb(253,253,253);}
    QMenu::item {
        font: 16px;
        background-color: rgb(253, 253, 253);
        padding: 8px 32px;
        margin: 0px 8px;
        border-bottom: 1px solid #DBDBDB;
    }

    QMenu::item:selected {
        background-color: #FFF8DC;
    }
)";

string small_qss = R"(
    QPushButton {
        image: url(:/MainWidget/resources/titleBar/small.svg);
        background-color: rgb(54,54,54);
        background-repeat: no-repeat;
        background-position: center;
        border: none;
        padding: 5px;
      }

    QPushButton:hover{
        image: url(:/MainWidget/resources/titleBar/small_hover.svg);
        background-color: rgb(54,54,54);
        background-repeat: no-repeat;
        background-position: center;
        border: none;
        padding: 5px;

  }
)";


string top_qss = R"(
    QPushButton {
        image: url(:/MainWidget/resources/titleBar/top.svg);
        background-color: rgb(54,54,54);
        background-repeat: no-repeat;
        background-position: center;
        border: none;
        padding: 5px;
      }

    QPushButton:hover{
        image: url(:/MainWidget/resources/titleBar/top_hover.svg);
        background-color: rgb(54,54,54);
        background-repeat: no-repeat;
        background-position: center;
        border: none;
        padding: 5px;

  }
)";


string min_qss = R"(
    QPushButton {
        image: url(:/MainWidget/resources/titleBar/min.svg);
        background-color: rgb(54,54,54);
        background-repeat: no-repeat;
        background-position: center;
        border: none;
        padding: 5px;
      }

    QPushButton:hover{
        image: url(:/MainWidget/resources/titleBar/min_hover.svg);
        background-color: rgb(54,54,54);
        background-repeat: no-repeat;
        background-position: center;
        border: none;
        padding: 5px;

  }
)";

string max_qss = R"(
    QPushButton {
        image: url(:/MainWidget/resources/titleBar/max.svg);
        background-color: rgb(54,54,54);
        background-repeat: no-repeat;
        background-position: center;
        border: none;
        padding: 5px;
      }

    QPushButton:hover{
        image: url(:/MainWidget/resources/titleBar/max_hover.svg);
        background-color: rgb(54,54,54);
        background-repeat: no-repeat;
        background-position: center;
        border: none;
        padding: 5px;

  }
)";

string close_qss = R"(
    QPushButton {
        image: url(:/MainWidget/resources/titleBar/close.svg);
        background-color: rgb(54,54,54);
        background-repeat: no-repeat;
        background-position: center;
        border: none;
        padding: 5px;
      }

    QPushButton:hover{
        image: url(:/MainWidget/resources/titleBar/close_hover.svg);
        background-color: rgb(54,54,54);
        background-repeat: no-repeat;
        background-position: center;
        border: none;
        padding: 5px;
  }
)";

string normal_qss = R"(
    QPushButton {
        image: url(:/MainWidget/resources/titleBar/normal.svg);
        background-color: rgb(54,54,54);
        background-repeat: no-repeat;
        background-position: center;
        border: none;
        padding: 5px;
      }
)";


string slider_qss = R"(
/* ===== 水平滑动条 ===== */
QSlider:horizontal {
    height: 16px;
    margin: 0 5px;
}

QSlider::groove:horizontal {
    background: #3A3A4A; /* 轨道背景色 */
    height: 6px;
    border-radius: 3px;
}

QSlider::sub-page:horizontal {
    background: qlineargradient(
        x1:0, y1:0, 
        x2:1, y2:0,
        stop:0 #6A5ACD, /* 紫罗兰色 */
        stop:0.5 #4169E1, /* 皇家蓝 */
        stop:1 #00BFFF  /* 深天蓝 */
    );
    height: 6px;
    border-radius: 3px;
}

QSlider::handle:horizontal {
    background: qradialgradient(
        cx:0.5, cy:0.5,
        radius:0.8,
        fx:0.3, fy:0.3,
        stop:0 white,
        stop:0.7 #E0FFFF,
        stop:1 #00CED1
    );
    width: 18px;
    height: 18px;
    margin: -6px 0;
    border-radius: 9px;
    border: 1px solid #008B8B;
    box-shadow: 0 1px 3px rgba(0, 0, 0, 0.5);
}

QSlider::handle:horizontal:hover {
    background: qradialgradient(
        cx:0.5, cy:0.5,
        radius:0.8,
        fx:0.4, fy:0.4,
        stop:0 white,
        stop:0.7 #AFEEEE,
        stop:1 #20B2AA
    );
    border: 1px solid #20B2AA;
}

QSlider::handle:horizontal:pressed {
    background: qradialgradient(
        cx:0.5, cy:0.5,
        radius:0.8,
        fx:0.5, fy:0.5,
        stop:0 white,
        stop:0.7 #7FFFD4,
        stop:1 #00CED1
    );
    box-shadow: 0 0 5px rgba(0, 206, 209, 0.8);
}

/* ===== 垂直滑动条 ===== */
QSlider:vertical {
    width: 16px;
    margin: 5px 0;
}

QSlider::groove:vertical {
    background: #3A3A4A;
    width: 6px;
    border-radius: 3px;
}

QSlider::sub-page:vertical {
    background: qlineargradient(
        x1:0, y1:1, 
        x2:0, y2:0,
        stop:0 #6A5ACD,
        stop:0.5 #4169E1,
        stop:1 #00BFFF
    );
    width: 6px;
    border-radius: 3px;
}

QSlider::handle:vertical {
    background: qradialgradient(
        cx:0.5, cy:0.5,
        radius:0.8,
        fx:0.3, fy:0.3,
        stop:0 white,
        stop:0.7 #E0FFFF,
        stop:1 #00CED1
    );
    width: 18px;
    height: 18px;
    margin: 0 -6px;
    border-radius: 9px;
    border: 1px solid #008B8B;
    box-shadow: 0 1px 3px rgba(0, 0, 0, 0.5);
}

/* ===== 添加刻度标记 ===== */
QSlider::add-page:horizontal {
    background: #4A4A5A;
    border-radius: 3px;
}

QSlider::add-page:vertical {
    background: #4A4A5A;
    border-radius: 3px;
})";