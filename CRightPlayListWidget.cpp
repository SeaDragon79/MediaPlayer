#include "CRightPlayListWidget.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDebug>

CRightPlayListWidget::CRightPlayListWidget(QWidget* parent)
		:QWidget(parent)
{
		setAttribute(Qt::WA_StyledBackground);

		this->setFixedWidth(200);
		setStyleSheet("background-color:rgb(34,34,34);");

		init();

		connect(m_pListView, &QListView::clicked, this, &CRightPlayListWidget::onListViewClicked);

}

CRightPlayListWidget::~CRightPlayListWidget()
{

}

void CRightPlayListWidget::init()
{
		setAttribute(Qt::WA_StyledBackground);

		// 创建数据模型
		m_pStringListModel = new QStringListModel(this);
		//创建视图
		m_pListView = new QListView(this);
		// 为ListView设置数据模型
		m_pListView->setModel(m_pStringListModel);
		m_pListView->setEditTriggers(QAbstractItemView::NoEditTriggers); // 禁用所有编辑触发

		m_pLabel = new QLabel(this);

		QVBoxLayout* pVLay = new QVBoxLayout(this);
		pVLay->addWidget(m_pLabel);
		pVLay->addWidget(m_pListView);
		pVLay->setContentsMargins(0, 0, 0, 0);
		pVLay->setSpacing(5);

		// 设置ListView样式
		m_pListView->setStyleSheet(
				"QListView {"
				"   background-color: rgb(45,45,45);"  // 比背景稍亮的颜色
				"   color: rgb(220,220,220);"          // 文字颜色
				"   border: 1px solid rgb(60,60,60);"  // 边框
				"   border-radius: 3px;"               // 圆角
				"   outline: 0px;"                     // 移除焦点边框
				"}"
				"QListView::item {"
				"   padding: 5px;"                     // 项内边距
				"   border-bottom: 1px solid rgb(60,60,60);" // 项之间的分隔线
				"}"
				"QListView::item:selected {"
				"   background-color: rgb(0, 120, 215);" // 选中项背景色
				"   color: white;"                      // 选中项文字颜色
				"}"
				"QListView::item:hover {"
				"   background-color: rgb(60,60,60);"   // 鼠标悬停背景色
				"}"
		);

		m_pLabel->setFixedSize(64, 32);
		m_pLabel->setText(u8"播放列表");
		m_pLabel->setStyleSheet(
				"QLabel {"
				"   color: rgb(220,220,220);"          // 文字颜色
				"   font-weight: bold;"                // 字体加粗
				"		font-family:YaHei;"                // 字体样式
				"   background-color: transparent;"    // 透明背景
				"   padding: 2px;"                     // 内边距
				"		margin-top: 5px;"
				"}"
		);
}

void CRightPlayListWidget::setListView(const QStringList& fileList)
{
		// 保存完整路径
		m_filePathList = fileList;

		// 提取文件名用于显示
		QStringList fileNames;
		for (const QString& filePath : fileList) {
				QFileInfo fileInfo(filePath);
				fileNames.append(fileInfo.fileName());
		}

		// 为模型设置文件名列表
		m_pStringListModel->setStringList(fileNames);
}

void CRightPlayListWidget::onListViewClicked(const QModelIndex& index)
{
		if (index.isValid()) {
				emit sig_ItemClicked(index.row()); // 发射点击的项索引
		}
}

void CRightPlayListWidget::setFilePathList(const QStringList& fileList)
{
		m_filePathList = fileList; // 保存完整路径列表
}

// 获取文件路径
QString CRightPlayListWidget::getFilePathAt(int index) const
{
		if (index >= 0 && index < m_filePathList.size()) {
				return m_filePathList.at(index);
		}
		return QString();
}

QModelIndex CRightPlayListWidget::getModelIndex(int row) const
{
		if (row >= 0 && row < m_pStringListModel->rowCount()) {
				return m_pStringListModel->index(row);
		}
		return QModelIndex();
}

void CRightPlayListWidget::setCurrentIndex(const QModelIndex& index)
{
		if (index.isValid()) {
				m_pListView->setCurrentIndex(index);
				m_pListView->update();
		}

		// 确保当前项可见
		m_pListView->scrollTo(index, QAbstractItemView::EnsureVisible);
}

void CRightPlayListWidget::setCurrentIndex(int index) {
		int m_pIndex = index - 1;
		if (m_pIndex >= 0 && m_pIndex < m_pStringListModel->rowCount()) {
				QModelIndex modelIndex = m_pStringListModel->index(m_pIndex, 0);
				setCurrentIndex(modelIndex);
		}
}
