#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QMediaPlayer>
#include <QUrl>
#include <QVideoWidget>
#include <QAudioOutput>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLineEdit>
#include <QPushButton>
#include <string>
#include <QFileDialog>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Init();
    void openFileWindow();
    void openUrlWindow();
    void showAboutWindow();
    void updateSource(QUrl mediaPath);

private:
    QMediaPlayer *player = nullptr;
    QAudioOutput *audioOutput = nullptr;
    QVideoWidget *videoWidget = nullptr;
    QWidget *videoWindow = nullptr;
    QWidget *bottomMenu = nullptr;

};
#endif // MAINWINDOW_H
