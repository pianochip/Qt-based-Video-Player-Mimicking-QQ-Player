#include "CTimeSlider.h"
#include <QEvent>
#include <QMouseEvent>
#include <QPoint>

//构造函数,改变进度条外观
CTimeSlider::CTimeSlider(QWidget* p)
	:QSlider(p)
{
	setAttribute(Qt::WA_StyledBackground);
	this->setOrientation(Qt::Horizontal);
	this->setFixedHeight(m_SliderHeight);
	
	// 给事件滑动条安装事件，处理点击效果
	this->installEventFilter(this);

	connect(this, &QSlider::sliderMoved, this, &CTimeSlider::onSliderMoved);
}

CTimeSlider::~CTimeSlider()
{
}

//定义事件过滤器操作
bool CTimeSlider::eventFilter(QObject* slider, QEvent* event) {
	if (event->type() == QEvent::MouseButtonPress && slider == this) {
		QMouseEvent* mouseEvent = static_cast<QMouseEvent*> (event);
		if (mouseEvent->button() == Qt::LeftButton) {
			slider_mouseLButtonPress(slider, event);
		}
	}
	return QSlider::eventFilter(slider, event);
}

//实现点击进度条后， 跳往对应位置
void CTimeSlider::slider_mouseLButtonPress(QObject* slider, QEvent* event) {
	//类型转换
	QSlider* sliderCtrl = static_cast<QSlider*> (slider);
	QMouseEvent* mouseEvent = static_cast<QMouseEvent*> (event);

	int cxctl = 0; //滑块宽度
	int cxwnd = 0; //滑槽宽度
	int mxpos = 0; //鼠标按下的位置 距 进度条起点的像素距离

	//获取鼠标按下的位置距进度条起点的像素距离
	if (Qt::Horizontal == sliderCtrl->orientation()) {//判断是水平进度条还是垂直进度条
		cxwnd = sliderCtrl->width();
		//判断进度条是从左至右还是从右至左
		if (sliderCtrl->invertedAppearance()) {
			mxpos = cxwnd - mouseEvent->pos().x();
		}
		else
			mxpos = mouseEvent->pos().x();
	}
	else {
		cxwnd = sliderCtrl->height();
		if (sliderCtrl->invertedAppearance()) {
			mxpos = mouseEvent->pos().y();
		}
		else {
			mxpos = cxwnd - mouseEvent->pos().y();
		}
	}

	//将mxpos转化为在进度条上的位置
	int scpos = sliderCtrl->minimum() 
				+ (1.0 * mxpos / cxwnd) 
				* (sliderCtrl->maximum() - sliderCtrl->minimum());

	//比较滑块的位置与鼠标点击的位置
	if (sliderCtrl->sliderPosition() != scpos) {
		sliderCtrl->setSliderPosition(scpos);
	}
}

//槽函数 
void CTimeSlider::onSliderMoved(int position)
{
	emit sig_SliderMove(position);
}

//设置进度条范围
void CTimeSlider::setTimeSliderRange(qint64 value)
{
	this->setRange(0, value);
}

//设置进度条的值
void CTimeSlider::setSliderValue(qint64 value)
{
	this->setValue(value);
}