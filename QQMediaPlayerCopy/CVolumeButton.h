#pragma once
#include <QPushButton>
#include "CVolumeSliderDialog.h"

//音量按钮及音量条
class CVolumeButton : public QPushButton 
{
	Q_OBJECT
public:
	CVolumeButton(QWidget* parent = nullptr);
	~CVolumeButton();

	//检查是否处于静音状态
	bool getMute() const
	{
		return m_isMute;
	}
	//设置静音状态或非静音状态
	void setMute(bool mute) { 
		m_isMute = mute; 
	}

//当音量滑动条被拉动时，将音量值传给主窗口，尤其去控制音量
signals:
	void sig_VolumeValue(int value);

protected:
	void paintEvent(QPaintEvent* event) override; //绘图事件，确保按钮图片和背景正确渲染
	void enterEvent(QEnterEvent* event) override; //鼠标进入事件，当鼠标光标移到按钮时触发;计算坐标并召唤（弹出）音量悬浮窗
	void mousePressEvent(QMouseEvent* event) override; //鼠标按下事件。当用户点击左键时触发;切换静音状态
	void timerEvent(QTimerEvent* event) override; //定时器事件;不断检测鼠标坐标，判断鼠标是不是离开了“安全区”，如果是，就立刻隐藏悬浮窗。

private:
	bool m_isMute = false;  //是否静音
	CVolumeSliderDialog* m_pVolumeSliderDlg = nullptr; //音量滑动条的悬浮窗口实体
};