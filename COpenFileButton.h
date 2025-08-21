#pragma once

#include <QWidget>
#include <QPushButton>

class COpenFileButton : public QWidget
{
		Q_OBJECT

public:
		COpenFileButton(QWidget* parent = nullptr);
		~COpenFileButton();

private slots:
		void on_openfile();
		void on_openFloder();

protected:
		void paintEvent(QPaintEvent* event)override;
		bool eventFilter(QObject* watched, QEvent* event)override;

signals:
		void sig_openfile(const QStringList& filelist);
		void sig_openFloder(QString path);

private:
		int m_totalWidth = 0;

		QPushButton* m_pOpenFileButton = nullptr;
		QPushButton* m_pArrowButton = nullptr;
};

