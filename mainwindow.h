//
// Created by FJdarc on 25-6-27.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QPushButton>
#include "player.h"

QT_BEGIN_NAMESPACE

namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

    void SetupConnections();

    void UpdateTimeDisplay();

    void ShowHelpAbout() {
        QMessageBox::about(nullptr, "About",
                           "<h2>Multimedia Player</h2>"
                           "<p>Version 0.0.1</p>"
                           "<p>Copyright © 2025 FJdarc</p>"
                           "<p>This is a dev version.</p>");
    }

    QString FormatTime(qint64 ms);

    void OpenFileWindow();

    void InitControlPanel();

private:
    Ui::MainWindow *ui;
    Player *player;
    QLabel *durationLabel;
    QLabel *positionLabel;
    QSlider *progressSlider;
    QHBoxLayout *seekBar;
    QWidget *controlPanel;
};


#endif //MAINWINDOW_H
