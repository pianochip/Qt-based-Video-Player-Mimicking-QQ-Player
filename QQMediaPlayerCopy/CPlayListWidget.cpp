#include "CPlayListWidget.h"
#include <QVBoxLayout>

CPlayListWidget::CPlayListWidget(QWidget* parent)
	: QWidget(parent)
{
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setFixedWidth(400);

	//侧边栏外框
	m_pListView = new QListView(this);
	m_pListView->setFixedWidth(400);
	m_pListView->setEditTriggers(QListView::EditTrigger::NoEditTriggers);//设置里面的数据不可编辑
	m_pListView->setStyleSheet("QListView{background-color:rgb(64,74,84);show-decoration-selected:1;border:none;color:#FFFFFF;outline:none} \
		QListView::item{padding-top:12px;padding-bottom:12px;} \
		QListView::item:alternate{background:#EEEEEE;} \
		QListView::item:selected{border:1px solid #6a6ea9;} \
		QListView::item::selected:!active{background:qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #6a6ea9, stop:1 #888dd9);} \
		QListView::item::hover{background:qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #000000, stop:1 #FFFFFF);}");

	//垂直布局
	QVBoxLayout* pVLay = new QVBoxLayout(this);
	pVLay->addWidget(m_pListView);
	pVLay->setContentsMargins(0, 0, 0, 0);
	this->setLayout(pVLay);

	connect(m_pListView, &QListView::doubleClicked, this, &CPlayListWidget::on_Item_doubleClicked);
}
CPlayListWidget::~CPlayListWidget(){}

//把一长串视频名字填充到列表里
void CPlayListWidget::setPlayList(QStringListModel* listModel) {
	m_pStringListModel = listModel;
	m_pListView->setModel(listModel);
}

//获取数据模型的StringList
QStringList CPlayListWidget::getPlaylist() const
{
	return m_pStringListModel->stringList();  
}

//槽函数
void CPlayListWidget::on_Item_doubleClicked(const QModelIndex& index) {
	QString itemValue = m_pStringListModel->data(index).toString();
	emit sig_doubleClickFileName(itemValue);
}