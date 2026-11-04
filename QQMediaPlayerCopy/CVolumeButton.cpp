#include "CVolumeButton.h"
#include <QMouseEvent>
#include <QStylePainter>
#include <QStyleOptionButton>
#include <iostream>
#include <QThread>

using namespace std;

//构造函数
CVolumeButton::CVolumeButton(QWidget* parent)
	: QPushButton(parent)
{	// 设置按钮样式
	setFixedSize(32, 32);
	setStyleSheet("QPushButton{background-image:url(:/playCtrlBar/resources/playctrlBar/audio_open.svg);border:none;}"
		"QPushButton:hover{background-image:url(:/playCtrlBar/resources/playctrlBar/audio_open_hover.svg);border:none;}"
		"QPushButton:pressed{background-image:url(:/playCtrlBar/resources/playctrlBar/audio_open.svg);border:none;}");

	m_pVolumeSliderDlg = new CVolumeSliderDialog(this);
	connect(m_pVolumeSliderDlg, &CVolumeSliderDialog::sig_SliderValueChanged, [this](int value) {
		emit sig_VolumeValue(value);
		});
}

CVolumeButton::~CVolumeButton(){}

//绘画事件
void CVolumeButton::paintEvent(QPaintEvent* event) {
	// 创建画笔
	QStylePainter p(this);

	// 创建样式选项，用来记录按钮的状态信息
	QStyleOptionButton option;

	// 初始化选项，将按钮的状态信息计入option
	this->initStyleOption(&option);

	// 画一个标准按钮，按照option的数据来画
	p.drawControl(QStyle::CE_PushButton, option);
}

//定义按钮点击后的操作(静音切换)
void CVolumeButton::mousePressEvent(QMouseEvent* event) {
	//检查是否是左键点击按钮
	if (event->button() == Qt::LeftButton) {
		if (getMute()) {// 目前是静音状态，点击后音量调为50
			m_pVolumeSliderDlg->setSliderValue(50);
			setMute(false);
		}
		else { //目前不是静音状态，点击后静音
			m_pVolumeSliderDlg->setSliderValue(0);
			setMute(true);
		}
	}
}

//定义悬停进入事件(显示弹窗)
void CVolumeButton::enterEvent(QEnterEvent* event) {
	//获取喇叭图标的绝对位置
	QPoint p1 = this->mapToGlobal(QPoint(0, 0));

	//音量条要与喇叭按钮居中对齐
	//1.计算出居中对齐时，音量条的x坐标和y坐标
	int x = p1.x() + (this->width() - m_pVolumeSliderDlg->width()) / 2;
	int y = p1.y() - m_pVolumeSliderDlg->height();

	//2.将音量条移到此位置并显示
	m_pVolumeSliderDlg->move(x, y);
	m_pVolumeSliderDlg->show();

	//3.定时检测鼠标是否离开图标按钮
	startTimer(250);
}

//当startTimer定时器到点后，调用timeEvent函数
void CVolumeButton::timerEvent(QTimerEvent* event) {
	if (!m_pVolumeSliderDlg->isVisible()) {
		killTimer(event->timerId());
		return;
	}
	
	//获取鼠标的实时位置
	QPoint p1 = QCursor::pos();

	//获取按钮和音量条的宽和高(包含在rect里)
	QRect rect1 = this->rect();
	QRect rect2 = m_pVolumeSliderDlg->rect();

	//获取按钮的绝对位置
	QPoint p2 = this->mapToGlobal(QPoint(0, 0));
	//获取音量条相较于按钮的位置，以及其宽和高
	QRect rect3 = m_pVolumeSliderDlg->geometry();
	
	//创建一个包含按钮和音量条的大矩形
	QRect area(rect3.left(), rect3.top(), rect2.width(), rect1.height() + rect2.height());

	if (!area.contains(p1)) {
		m_pVolumeSliderDlg->hide();
	}
}
