#pragma once

#include <QWidget>
#include <QStringListModel>
#include <QListView>
#include <QLabel>

class CRightPlayListWidget : public QWidget
{
		Q_OBJECT

public:
		CRightPlayListWidget(QWidget* parent = nullptr);
		~CRightPlayListWidget();

		void init();

		void setListView(const QStringList& fileList);
		void setFilePathList(const QStringList& fileList);
		QString getFilePathAt(int index) const;

		QModelIndex getModelIndex(int row) const;
		void setCurrentIndex(const QModelIndex& index);
		void setCurrentIndex(int index);

private slots:
		void onListViewClicked(const QModelIndex& index);

signals:
		void sig_ItemClicked(int index); // 发送点击的项索引

private:
		QStringList m_filePathList;
		QStringListModel* m_pStringListModel;
		QListView* m_pListView;
		QLabel* m_pLabel;
};

