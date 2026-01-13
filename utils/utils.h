#pragma once

#include <QtCore/QStandardPaths>
#include <QtCore/QString>
#include <QtWidgets/QFileDialog>
#include <QtCore/QFileInfo>

class Utils {
public:
    static QString getMediaPath() {
        return QFileDialog::getOpenFileName(
            nullptr,
            "选择媒体文件",
            QStandardPaths::writableLocation(QStandardPaths::MoviesLocation),
            "音频文件 (*.mp3);;视频文件 (*.mp4)"
        );
    }

    static QString getMediaName(QString path) {
        return QFileInfo(path).fileName();
    }

    static QString formatTime(qint64 ms) {
        int seconds = ms / 1000;
        int h = seconds / 3600;
        int m = (seconds % 3600) / 60;
        int s = seconds % 60;
        return QString("%1:%2:%3")
                .arg(h, 2, 10, QChar('0'))
                .arg(m, 2, 10, QChar('0'))
                .arg(s, 2, 10, QChar('0'));
    }
};
