#include "CVideoWidgetTopWidget.h"
#include <QEvent>
#include <QMouseEvent>
#include <string>
#include <iostream>
using namespace std;

CVideoWidgetTopWidget::CVideoWidgetTopWidget(QWidget* p)
	:QWidget(p)
{	//设置样式
	this->setAttribute(Qt::WA_StyledBackground);
	this->setAttribute(Qt::WA_TranslucentBackground);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::SubWindow);
	this->setAutoFillBackground(true);
	this->setMouseTracking(true);

	//实例化中间按钮组和右键按钮
	m_pOpenFileButton = new COpenFileButton(this);
	
	m_pOpenrRightlistButton = new QPushButton(this);
	m_pOpenrRightlistButton->setText("");
	m_pOpenrRightlistButton->setFixedSize(36, 80);
	m_pOpenrRightlistButton->setStyleSheet("QPushButton{background-color:rgb(54,54,54);background-image:url(:/videoWidget/resources/videoWidget/left_arrow.svg); \
		background-position:center; \
		padding-top: 24px; \
		background-repeat: no-repeat; \
		border:none;} \
		QPushButton:hover{background-image:url(:/videoWidget/resources/videoWidget/left_arrow_hover.svg);border:none;} \
		QPushButton:pressed{background-image:url(:/videoWidget/resources/videoWidget/left_arrow.svg);border:none;}");

	connect(m_pOpenFileButton, &COpenFileButton::sig_openfile, this, &CVideoWidgetTopWidget::sig_OpenFile);
	connect(m_pOpenFileButton, &COpenFileButton::sig_openUrl, this, &CVideoWidgetTopWidget::sig_OpenUrl);
	connect(m_pOpenrRightlistButton, &QPushButton::clicked, this, &CVideoWidgetTopWidget::sig_OpenPlaylist);
}
CVideoWidgetTopWidget::~CVideoWidgetTopWidget() {}

// 显示/隐藏右侧侧边栏按钮
void CVideoWidgetTopWidget::showRightBtn(bool flag) {
	if (flag) {
		m_pOpenrRightlistButton->show();
	}
	else
	{
		m_pOpenrRightlistButton->hide();
	}
}

// 显示/隐藏中央选择文件
void CVideoWidgetTopWidget::showOpenFileBtn(bool flag) {
	if (flag) {
		m_pOpenFileButton->show();
	}
	else
	{
		m_pOpenFileButton->hide();
	}
}

//调整界面大小时，确保“打开文件”按钮永远在正中心，“播放列表”按钮永远紧贴右侧。
void CVideoWidgetTopWidget::resizeEvent(QResizeEvent* event) {
	int x1 = this->width() / 2 - m_pOpenFileButton->width() / 2;
	int y1 = this->height() / 2 - m_pOpenFileButton->height() / 2;
	m_pOpenFileButton->move(x1, y1);

	int x2 = this->width() - m_pOpenrRightlistButton->width();
	int y2 = this->height() / 2 - m_pOpenrRightlistButton->height() / 2;
	m_pOpenrRightlistButton->move(x2, y2);
}