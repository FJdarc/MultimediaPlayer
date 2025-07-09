//
// Created by FJdarc on 25-6-27.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), player(new Player(this)),
                                          durationLabel(new QLabel("00:00", this)),
                                          positionLabel(new QLabel("00:00", this)),
                                          progressSlider(new QSlider(Qt::Horizontal, this)),
                                          seekBar(new QHBoxLayout(this)), controlPanel(new QWidget(this)) {
    ui->setupUi(this);
    SetupConnections();
    ui->verticalLayout->setContentsMargins(0, 0, 0, 0);
    ui->verticalLayout->addWidget(player->GetVideoWidget(), 1);
    seekBar->addWidget(positionLabel);
    seekBar->addWidget(progressSlider);
    seekBar->addWidget(durationLabel);
    ui->verticalLayout->addLayout(seekBar);
    InitControlPanel();
    ui->verticalLayout->addWidget(controlPanel);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::UpdateTimeDisplay() {
    qint64 position = player->position();
    qint64 duration = player->duration();

    positionLabel->setText(FormatTime(position));
    durationLabel->setText(FormatTime(duration));
}

QString MainWindow::FormatTime(qint64 ms) {
    if (ms <= 0) return "00:00";

    int seconds = ms / 1000;
    int minutes = seconds / 60;
    seconds %= 60;

    return QString("%1:%2")
            .arg(minutes, 2, 10, QChar('0'))
            .arg(seconds, 2, 10, QChar('0'));
}

void MainWindow::OpenFileWindow() {
    QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("选择文件"),
        QDir::homePath(),
        tr("所有支持的媒体文件 (*.mp4 *.avi *.mkv *.mov *.flv *.wmv *.mp3 *.wav *.flac *.ogg *.aac);;" // 通用类型
            "视频文件 (*.mp4 *.avi *.mkv *.mov *.flv *.wmv);;" // 视频分类
            "音频文件 (*.mp3 *.wav *.flac *.ogg *.aac);;" // 音频分类
            "MP4视频 (*.mp4);;" // 单个格式
            "AVI视频 (*.avi);;"
            "MKV视频 (*.mkv);;"
            "MOV视频 (*.mov);;"
            "FLV视频 (*.flv);;"
            "WMV视频 (*.wmv);;"
            "MP3音频 (*.mp3);;"
            "WAV音频 (*.wav);;"
            "FLAC音频 (*.flac);;"
            "OGG音频 (*.ogg);;"
            "AAC音频 (*.aac)")
    );

    player->setSource(QUrl::fromLocalFile(filePath));
    player->play();
}

void MainWindow::InitControlPanel() {
    // 创建水平布局作为控制面板的内部布局
    QHBoxLayout *controlLayout = new QHBoxLayout(controlPanel);
    controlLayout->setContentsMargins(5, 0, 5, 0); // 可选：设置边距

    // 创建按钮并添加到布局
    QPushButton *pp = new QPushButton("Play/Pause", controlPanel);
    QPushButton *last = new QPushButton("Last", controlPanel);
    QPushButton *stop = new QPushButton("Stop", controlPanel);
    QPushButton *next = new QPushButton("Next", controlPanel);

    controlLayout->addWidget(pp);
    controlLayout->addWidget(last);
    controlLayout->addWidget(stop);
    controlLayout->addWidget(next);

    // 可选：设置按钮大小策略
    pp->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    last->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    stop->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    next->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    connect(pp, &QPushButton::clicked, this, [this]() {
        player->isPlaying() ? player->pause() : player->play();
    });
    connect(stop, &QPushButton::clicked, this, [this]() {
        player->stop();
    });
}

void MainWindow::SetupConnections() {
    // 连接播放器信号到进度条
    connect(player, &QMediaPlayer::positionChanged, this, [this](qint64 pos) {
        if (!progressSlider->isSliderDown()) {
            progressSlider->setValue(pos);
        }
        UpdateTimeDisplay();
    });

    // 连接时长变化信号
    connect(player, &QMediaPlayer::durationChanged, this, [this](qint64 dur) {
        progressSlider->setRange(0, dur);
        progressSlider->setEnabled(dur > 0);
        UpdateTimeDisplay();
    });

    // 连接滑块拖动信号
    connect(progressSlider, &QSlider::sliderMoved, this, [this](int position) {
        player->setPosition(position);
    });

    connect(ui->actionAbout, &QAction::triggered, this, qOverload<>(&MainWindow::ShowHelpAbout));
    connect(ui->actionOpen_File, &QAction::triggered, this, qOverload<>(&MainWindow::OpenFileWindow));
}
