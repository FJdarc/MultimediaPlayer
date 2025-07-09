//
// Created by FJdarc on 25-6-27.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <QAudioOutput>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QSlider>
#include <QLabel>

class Player : public QMediaPlayer {
    Q_OBJECT

public:
    explicit Player(QObject *parent = nullptr);

    ~Player() override;

    QVideoWidget *GetVideoWidget() {
        return videoWidget;
    }

private:
    QAudioOutput *audioOutput;
    QVideoWidget *videoWidget;
};

#endif //PLAYER_H
