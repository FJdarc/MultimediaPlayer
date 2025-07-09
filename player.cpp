//
// Created by FJdarc on 25-6-27.
//

#include "player.h"

Player::Player(QObject *parent)
    : QMediaPlayer(parent), audioOutput(new QAudioOutput(this)), videoWidget(new QVideoWidget()) {
    setAudioOutput(audioOutput);
    setVideoOutput(videoWidget);
}

Player::~Player() {
    delete videoWidget;
}
