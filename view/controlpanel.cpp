#include "controlpanel.h"

ControlPanel::ControlPanel(QWidget *parent)
    : QFrame(parent) {
    setupUi();
    setupConnections();
}

ControlPanel::~ControlPanel() {
}

void ControlPanel::setupUi() {
    if (this->objectName().isEmpty())
        this->setObjectName("ControlPanel");
    this->resize(640, 58);
    playButton = new QPushButton(this);
    playButton->setObjectName("playButton");
    playButton->setGeometry(QRect(296, 5, 48, 48));
    lastButton = new QPushButton(this);
    lastButton->setObjectName("lastButton");
    lastButton->setGeometry(QRect(254, 13, 32, 32));
    nextButton = new QPushButton(this);
    nextButton->setObjectName("nextButton");
    nextButton->setGeometry(QRect(354, 13, 32, 32));
    randomButton = new QPushButton(this);
    randomButton->setObjectName("randomButton");
    randomButton->setGeometry(QRect(212, 13, 32, 32));
    circleButton = new QPushButton(this);
    circleButton->setObjectName("circleButton");
    circleButton->setGeometry(QRect(396, 13, 32, 32));
    playlistButton = new QPushButton(this);
    playlistButton->setObjectName("playlistButton");
    playlistButton->setGeometry(QRect(598, 13, 32, 32));

    retranslateUi();

    QMetaObject::connectSlotsByName(this);
}

void ControlPanel::retranslateUi() {
    this->setWindowTitle(QCoreApplication::translate("ControlPanel", "ControlPanel", nullptr));
    playButton->setText(QCoreApplication::translate("ControlPanel", "play", nullptr));
    lastButton->setText(QCoreApplication::translate("ControlPanel", "last", nullptr));
    nextButton->setText(QCoreApplication::translate("ControlPanel", "next", nullptr));
    randomButton->setText(QCoreApplication::translate("ControlPanel", "rand", nullptr));
    circleButton->setText(QCoreApplication::translate("ControlPanel", "circle", nullptr));
    playlistButton->setText(QCoreApplication::translate("ControlPanel", "list", nullptr));
}

void ControlPanel::setupConnections() {
}

void ControlPanel::on_playButton_clicked() {
    auto mediaPlayer = parent()->parent()->findChild<QMediaPlayer*>("mediaPlayer");
    if (mediaPlayer->isPlaying()) {
        playButton->setText("pause");
        mediaPlayer->pause();
    }
    else {
        playButton->setText("play");
        mediaPlayer->play();
    }
}


void ControlPanel::on_randomButton_clicked() {
    auto playlist = parent()->parent()->findChild<Playlist*>("playlist");
    if (!playlist || !playlist->playlistModel)
        return;
    auto model = playlist->playlistModel;
    model->shuffle();
}

void ControlPanel::on_circleButton_clicked() {
    circleMode = static_cast<CircleMode>((static_cast<int>(circleMode) + 1) % 3);
    switch (circleMode) {
        case NoREPEAT:
            qDebug() << "NoREPEAT";
            break;
        case OneREPEAT:
            qDebug() << "OneREPEAT";
            break;
        case ListREPEAT:
            qDebug() << "ListREPEAT";
            break;
    }
}

void ControlPanel::on_playlistButton_clicked() {
    auto playlist = parent()->parent()->findChild<Playlist*>("playlist");
    if (playlist->isVisible())
        playlist->hide();
    else
        playlist->show();
}
void ControlPanel::resizeEvent(QResizeEvent *event) {
    QSize newSize = event->size();

    playButton->setGeometry(QRect(newSize.width()/2 - 24, 5, 48, 48));     // 296
    lastButton->setGeometry(QRect(newSize.width()/2 - 66, 13, 32, 32));   // 254
    nextButton->setGeometry(QRect(newSize.width()/2 + 34, 13, 32, 32));   // 354
    randomButton->setGeometry(QRect(newSize.width()/2 - 108, 13, 32, 32));// 212
    circleButton->setGeometry(QRect(newSize.width()/2 + 76, 13, 32, 32)); // 396
    playlistButton->setGeometry(QRect(newSize.width() - 32-10, 13, 32, 32)); // 598

    QWidget::resizeEvent(event); // 保留基类行为
}