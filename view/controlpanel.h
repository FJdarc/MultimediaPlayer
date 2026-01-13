#pragma once

#include "playlist.h"

#include <QtCore/QVariant>
#include <QtCore/QRandomGenerator>
#include <QtMultimedia/QMediaPlayer>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>

enum CircleMode {
    NoREPEAT = 0,
    OneREPEAT = 1,
    ListREPEAT = 2,
};

class ControlPanel : public QFrame {
    Q_OBJECT
public:
    explicit ControlPanel(QWidget *parent = nullptr);
    ~ControlPanel();

    QPushButton *playButton;
    QPushButton *lastButton;
    QPushButton *nextButton;
    QPushButton *randomButton;
    QPushButton *circleButton;
    QPushButton *playlistButton;
    CircleMode circleMode = NoREPEAT;

    void setupUi();
    void retranslateUi();

    void setupConnections();
protected:
    void resizeEvent(QResizeEvent *event) override;
public slots:
    void on_playButton_clicked();
    // void on_lastButton_clicked();
    // void on_nextButton_clicked();
    void on_randomButton_clicked();
    void on_circleButton_clicked();
    void on_playlistButton_clicked();
};
