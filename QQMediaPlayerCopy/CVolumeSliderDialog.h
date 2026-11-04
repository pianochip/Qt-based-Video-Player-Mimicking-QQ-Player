#pragma once
#include <QDialog>
#include <QSlider>

class CVolumeSliderDialog : public QDialog //弹出式音量条悬浮窗
{
	Q_OBJECT

public:
	CVolumeSliderDialog(QWidget* parent = nullptr);
	~CVolumeSliderDialog();

	//修改音量
	void setSliderValue(int value) //修改滑动条的值
	{
		m_pSlider->setValue(value);
	}

protected:
	bool event(QEvent* event) override; //美化UI

//用户拉动音量时触发信号
signals:
	void sig_SliderValueChanged(int value); //让槽函数更改音量大小

private:
	QSlider* m_pSlider = nullptr; //滑动条控件
};