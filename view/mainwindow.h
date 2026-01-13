#pragma once

#include "progressbar.h"
#include "playlist.h"
#include "controlpanel.h"
#include "openurl.h"
#include "utils.h"

#include <QtCore/QAbstractItemModel>
#include <QtCore/QUrl>
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtMultimedia/QAudioOutput>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimediaWidgets/QGraphicsVideoItem>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow();
    ~MainWindow();

    QAction *actionOpen_File;
    QAction *actionOpen_URL;
    QAudioOutput *audioOutput;
    QWidget *centralWidget;
    ControlPanel *controlPanel;
    OpenURL *openURL;
    Playlist *playlist;
    QFrame *settings;
    ProgressBar *progressBar;
    QGraphicsView *graphicsView;
    QGraphicsScene *graphicsScene;
    QGraphicsVideoItem *graphicsVideoItem;
    QMediaPlayer *mediaPlayer;
    QMenuBar *menubar;
    QMenu *menuFile;
    QModelIndex currentIndex;

    void setupUi();
    void retranslateUi();

    void setupConnections();
    void playEnd();

protected:
    void resizeEvent(QResizeEvent *event) override ;
public slots:
    void playLast();
    void playNext();
    void on_actionOpen_File_triggered();
    void on_actionOpen_URL_triggered();
};