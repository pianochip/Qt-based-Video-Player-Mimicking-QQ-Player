#include "CVolumeSliderDialog.h"
#include <QVBoxLayout> //引入 Qt 里的垂直布局管理器，自动管理它们的位置和大小
#include <QEvent>
#include <windows.h> //调用Windows系统的功能

//构造函数
CVolumeSliderDialog::CVolumeSliderDialog(QWidget* parent)
	:QDialog(parent)
{	
	//设置对话框大小并绑定滑动条
	this->setFixedSize(40, 120);
	m_pSlider = new QSlider(Qt::Vertical, this); //滑动条从属于该对话框，并且垂直显示

	//设置对话框的布局
	QVBoxLayout* pVLay = new QVBoxLayout(this); //将滑动条加入对话框的垂直布局当中
	pVLay->addWidget(m_pSlider);

	//让该对话框变为无边框、无标题栏、不会抢占焦点的窗口
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip); //FramelessWindowHint:去掉操作系统自带的标题栏、关闭按钮、最小化按钮以及外边框
																 //ToolTip:不抢焦点、点击外部自动消失
	this->setStyleSheet("QDialog{background-color: rgba(54, 54, 54, 0.5);}"); //设置对话框样式
	
	//只要滑动条m_pSlider值改变，就会触发sig_SliderValueChanged
	connect(m_pSlider, &QSlider::valueChanged, [this](int value) {
		emit sig_SliderValueChanged(value);
		});
}

CVolumeSliderDialog::~CVolumeSliderDialog() {}

//美化UI(忽略)
bool CVolumeSliderDialog::event(QEvent* event)
{
	static bool class_amended = false;

	if (event->type() == QEvent::WinIdChange)
	{
		HWND hwnd = (HWND)winId();

		if (class_amended == false)
		{
			class_amended = true;
			DWORD class_style = ::GetClassLong(hwnd, GCL_STYLE);
			class_style &= ~CS_DROPSHADOW;
			::SetClassLong(hwnd, GCL_STYLE, class_style); // windows系统函数
		}
	}

	return QWidget::event(event);
}



