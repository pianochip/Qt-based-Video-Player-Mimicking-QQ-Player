#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QStringList>

//标题栏
class CTitleBar : public QWidget
{
	Q_OBJECT
public:
	CTitleBar(QWidget* parent = nullptr);
	~CTitleBar();
	void setFileNameLabelText(QString name); //设置正在播放的视频标题

private:
	void InitData(); //初始化
	void RestoreUI();

	void mousePressEvent(QMouseEvent* event) override; //鼠标按下事件，实现拖拽移动
	void mouseDoubleClickEvent(QMouseEvent* event) override; //双击动作，实现双击切换全屏/正常
	void resizeEvent(QResizeEvent* event) override; //改变窗口大小事件

	QPushButton* m_pLogoBtn; // 主菜单按钮
	QLabel* m_pFileNameLabel; // 视频名称文本标签
	
	QPushButton* m_pMinimodeBtn; // 迷你小窗按钮
	QPushButton* m_pSettopBtn;  // 置顶
	QPushButton* m_pMinBtn; // 最小化
	QPushButton* m_pMaxBtn; // 最大化/还原
	QPushButton* m_pCloseBtn; // 关闭



signals:
	void sig_close(); //关闭
	void sig_ShowFullFcreen(); //全屏
	void sig_showMiniMode(); //迷你小窗显示
	void sig_openfile(const QStringList& fileList);
	void sig_openUrl(const QString& url);

private slots:
	void onClicked();
	void openFile();
	void openFloder();
	void openNetStream();
	void exit();

};