#pragma once
#include <QWidget>
#include <QPushButton>

//屏幕中央选择文件按钮组
class COpenFileButton : public QWidget
{
	Q_OBJECT
public:
	COpenFileButton(QWidget* parent = nullptr);
	~COpenFileButton();

private:
	QPushButton* m_pOpenFileButton; //打开文件 按钮
	QPushButton* m_pArrowButton; //下拉菜单 按钮
	int m_totalWidth = 0; //记录两个按钮的宽度

protected:
	void paintEvent(QPaintEvent* event) override; 
	bool eventFilter(QObject* watched, QEvent* event) override; //让下拉菜单向左偏移，与打开文件 按钮对齐

signals:
	void sig_openfile(const QStringList& fileList);
	void sig_openUrl(const QString& url);

private slots:
	void on_openfile();
	void on_openFloder();
	void on_openNetStream();

};