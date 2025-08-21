#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QHBoxLayout>
#include <qt_windows.h>
#include <QMenu>

class CTitleBar : public QWidget
{
		Q_OBJECT

public:
		CTitleBar(QWidget* parent);
		~CTitleBar();

private:
		void initUI();
		void mousePressEvent(QMouseEvent* event) override;

private slots:
		void onClick();
		void mouseDoubleClickEvent(QMouseEvent* event)override;
		void onOpenFile();

signals:
		void sig_close();
	  void sig_OpenFile(const QStringList& fileList);

private:
		QPushButton* m_LogoBtn;
		QPushButton* m_SmallBtn;
		QPushButton* m_TopBtn;
		QPushButton* m_MinBtn;
		QPushButton* m_MaxBtn;
		QPushButton* m_CloseBtn;

};

