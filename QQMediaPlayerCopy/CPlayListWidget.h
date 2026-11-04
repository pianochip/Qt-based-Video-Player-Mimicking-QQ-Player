#pragma once
#include <QWidget>
#include <QListView>
#include <QStringListModel>

//播放列表侧边栏
class CPlayListWidget : public QWidget
{
	Q_OBJECT
public:
	CPlayListWidget(QWidget* parent = nullptr);
	~CPlayListWidget();
	void setPlayList(QStringListModel* listModel); //把一长串视频名字填充到列表里
	void setPlay(bool play) { m_isPlay = play; } //设置播放状态
	bool getPlay() const { return m_isPlay; } //获取播放状态
	QStringList getPlaylist() const; //

private:
	QListView* m_pListView; //侧边栏列表外框(视图)
	QStringListModel* m_pStringListModel; //存储数据(模型)
	bool m_isPlay;

signals:
	void sig_doubleClickFileName(const QString& fileName); //用户双击视频名字时发出信号

private slots:
	void on_Item_doubleClicked(const QModelIndex& index);

};