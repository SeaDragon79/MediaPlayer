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

		// ��������ģ��
		m_pStringListModel = new QStringListModel(this);
		//������ͼ
		m_pListView = new QListView(this);
		// ΪListView��������ģ��
		m_pListView->setModel(m_pStringListModel);
		m_pListView->setEditTriggers(QAbstractItemView::NoEditTriggers); // �������б༭����

		m_pLabel = new QLabel(this);

		QVBoxLayout* pVLay = new QVBoxLayout(this);
		pVLay->addWidget(m_pLabel);
		pVLay->addWidget(m_pListView);
		pVLay->setContentsMargins(0, 0, 0, 0);
		pVLay->setSpacing(5);

		// ����ListView��ʽ
		m_pListView->setStyleSheet(
				"QListView {"
				"   background-color: rgb(45,45,45);"  // �ȱ�����������ɫ
				"   color: rgb(220,220,220);"          // ������ɫ
				"   border: 1px solid rgb(60,60,60);"  // �߿�
				"   border-radius: 3px;"               // Բ��
				"   outline: 0px;"                     // �Ƴ�����߿�
				"}"
				"QListView::item {"
				"   padding: 5px;"                     // ���ڱ߾�
				"   border-bottom: 1px solid rgb(60,60,60);" // ��֮��ķָ���
				"}"
				"QListView::item:selected {"
				"   background-color: rgb(0, 120, 215);" // ѡ�����ɫ
				"   color: white;"                      // ѡ����������ɫ
				"}"
				"QListView::item:hover {"
				"   background-color: rgb(60,60,60);"   // �����ͣ����ɫ
				"}"
		);

		m_pLabel->setFixedSize(64, 32);
		m_pLabel->setText(u8"�����б�");
		m_pLabel->setStyleSheet(
				"QLabel {"
				"   color: rgb(220,220,220);"          // ������ɫ
				"   font-weight: bold;"                // ����Ӵ�
				"		font-family:YaHei;"                // ������ʽ
				"   background-color: transparent;"    // ͸������
				"   padding: 2px;"                     // �ڱ߾�
				"		margin-top: 5px;"
				"}"
		);
}

void CRightPlayListWidget::setListView(const QStringList& fileList)
{
		// ��������·��
		m_filePathList = fileList;

		// ��ȡ�ļ���������ʾ
		QStringList fileNames;
		for (const QString& filePath : fileList) {
				QFileInfo fileInfo(filePath);
				fileNames.append(fileInfo.fileName());
		}

		// Ϊģ�������ļ����б�
		m_pStringListModel->setStringList(fileNames);
}

void CRightPlayListWidget::onListViewClicked(const QModelIndex& index)
{
		if (index.isValid()) {
				emit sig_ItemClicked(index.row()); // ��������������
		}
}

void CRightPlayListWidget::setFilePathList(const QStringList& fileList)
{
		m_filePathList = fileList; // ��������·���б�
}

// ��ȡ�ļ�·��
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

		// ȷ����ǰ��ɼ�
		m_pListView->scrollTo(index, QAbstractItemView::EnsureVisible);
}

void CRightPlayListWidget::setCurrentIndex(int index) {
		int m_pIndex = index - 1;
		if (m_pIndex >= 0 && m_pIndex < m_pStringListModel->rowCount()) {
				QModelIndex modelIndex = m_pStringListModel->index(m_pIndex, 0);
				setCurrentIndex(modelIndex);
		}
}
