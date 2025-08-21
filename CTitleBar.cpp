#include "CTitleBar.h"
#include <string>
#include "qss.h"
#include <QFileDialog>
#include <QSettings>
#include <QStandardPaths>

using namespace std;

CTitleBar::CTitleBar(QWidget* parent)
		:QWidget(parent)
{
		this->setAttribute(Qt::WA_DeleteOnClose);

		initUI();
}

CTitleBar::~CTitleBar()
{
}

void CTitleBar::initUI()
{
		setAttribute(Qt::WA_StyledBackground);

		setMouseTracking(true);

		this->setFixedHeight(32 + 3 * 2);
		this->setStyleSheet("background-color:rgb(54,54,54)");;
		this->setContentsMargins(0,0,0,0);

		m_LogoBtn = new QPushButton(this);
		m_LogoBtn->setFixedSize(138, 32);
		m_LogoBtn->setText(u8"Orange������");
		m_LogoBtn->setStyleSheet(QString::fromStdString(logo_button_qss));

		QMenu* pMenu = new QMenu(this);
		pMenu->setStyleSheet(QString::fromStdString(menu_qss));

		QAction* pAc1 = new QAction(u8"���ļ�",this);
		QAction* pAc2 = new QAction(u8"����˵��", this);
		QAction* pAc3 = new QAction(u8"�˳�", this);

		pMenu->addAction(pAc1);
		pMenu->addAction(pAc2);
		pMenu->addAction(pAc3);
		

		m_LogoBtn->setMenu(pMenu);



		// ������ť�����ö�����������CSSѡ������
		m_SmallBtn = new QPushButton(this);
		m_TopBtn = new QPushButton(this);
		m_MinBtn = new QPushButton(this);
		m_MaxBtn = new QPushButton(this);
		m_CloseBtn = new QPushButton(this);

		//���ð�ť��ʽ
		m_SmallBtn->setStyleSheet(QString::fromStdString(small_qss));
		m_TopBtn->setStyleSheet(QString::fromStdString(top_qss));
		m_MinBtn->setStyleSheet(QString::fromStdString(min_qss));
		m_MaxBtn->setStyleSheet(QString::fromStdString(max_qss));
		m_CloseBtn->setStyleSheet(QString::fromStdString(close_qss));

		// ���ù̶��ߴ�
		m_SmallBtn->setFixedSize(32, 32);
		m_TopBtn->setFixedSize(32, 32);
		m_MinBtn->setFixedSize(32, 32);
		m_MaxBtn->setFixedSize(32, 32);
		m_CloseBtn->setFixedSize(32, 32);

		QHBoxLayout* qHLayout = new QHBoxLayout(this);

		qHLayout->addWidget(m_LogoBtn);
		qHLayout->addStretch();

		qHLayout->addWidget(m_SmallBtn);
		QSpacerItem* pItem1 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
		qHLayout->addSpacerItem(pItem1);

		qHLayout->addWidget(m_TopBtn);
		QSpacerItem* pItem2 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
		qHLayout->addSpacerItem(pItem2);

		qHLayout->addWidget(m_MinBtn);
		QSpacerItem* pItem3 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
		qHLayout->addSpacerItem(pItem3);

		qHLayout->addWidget(m_MaxBtn);
		QSpacerItem* pItem4 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
		qHLayout->addSpacerItem(pItem4);

		qHLayout->addWidget(m_CloseBtn);


		connect(m_MinBtn, &QPushButton::clicked, this, &CTitleBar::onClick);
		connect(m_MaxBtn, &QPushButton::clicked, this, &CTitleBar::onClick);
		connect(m_CloseBtn, &QPushButton::clicked, this, &CTitleBar::onClick);

		connect(pAc1, &QAction::triggered,this, &CTitleBar::onOpenFile);
		connect(pAc3, &QAction::triggered, [=]() {emit sig_close(); });

}


void CTitleBar::onOpenFile()
{
		QString cfgPath = "HKEY_CURRENT_USER\\Software\\MediaPlayer";
		QSettings settings(cfgPath, QSettings::NativeFormat);
		QString lastPath = settings.value("openfile_path").toString(); // ��ע����ȡ·��

		if (lastPath.isEmpty()) {
				lastPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
		}

		// ����ͬʱ�򿪶���ļ�
		QStringList filelist = QFileDialog::getOpenFileNames(
				this,
				u8"ѡ��Ҫ���ŵ��ļ�",
				lastPath,
				u8"��Ƶ�ļ� (*.flv *.rmvb *.avi *.mp4);;�����ļ� (*.*);;");

		if (filelist.isEmpty())
		{
				return;
		}

		int end = filelist[0].lastIndexOf("/");
		QString tmppath = filelist[0].left(end + 1);
		settings.setValue("openfile_path", tmppath);

		emit sig_OpenFile(filelist);
}

void CTitleBar::mousePressEvent(QMouseEvent* event)
{
		if (ReleaseCapture())
		{
				QWidget* pwindow = this->window();
				if (pwindow->isTopLevel())
				{
						SendMessage(HWND(pwindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
				}
		}
}
void CTitleBar::mouseDoubleClickEvent(QMouseEvent* event)
{
		m_MaxBtn->click();
}



void CTitleBar::onClick()
{
		QPushButton* q_Btn = qobject_cast<QPushButton*>(sender());
		QWidget* qWindow = this->window();

		if (q_Btn == m_MinBtn)
		{
				qWindow->showMinimized();
		}
		else if (q_Btn == m_MaxBtn)
		{
				if (qWindow->isMaximized())
				{
						qWindow->showNormal();
						m_MaxBtn->setStyleSheet(QString::fromStdString(max_qss));
				}
				else {
						qWindow->showMaximized();
						m_MaxBtn->setStyleSheet(QString::fromStdString(normal_qss));
				}
		}
		else if (q_Btn == m_CloseBtn)
		{
				emit sig_close();
		}

}
