#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->Init();
}

MainWindow::~MainWindow()
{
}

void MainWindow::Init()
{
    this->resize(1280,720);
    auto *menuBar = this->menuBar();

    auto *fileMenu = menuBar->addMenu("File");
    auto *openFileAction = new QAction("Open File");
    auto *openURLAction = new QAction("Open URL");
    auto *exitAction = new QAction("Exit");
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
    connect(openFileAction, &QAction::triggered,this, this->openFileWindow);
    connect(openURLAction, &QAction::triggered,this, this->openUrlWindow);
    fileMenu->addActions({openFileAction, openURLAction, exitAction});

    auto *helpMenu = menuBar->addMenu("Help");
    auto *aboutAction = new QAction("About");
    connect(aboutAction, &QAction::triggered, this, this->showAboutWindow);
    helpMenu->addActions({aboutAction});

    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(player);
    audioOutput->setVolume(50);

    QWidget* mainContainer = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(mainContainer);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    setCentralWidget(mainContainer);

    videoWidget = new QVideoWidget(mainContainer);
    videoWidget->setMinimumSize(1280, 670);
    mainLayout->addWidget(videoWidget, 1);

    bottomMenu = new QWidget(mainContainer);
    bottomMenu->setFixedHeight(50);
    mainLayout->addWidget(bottomMenu);

    player->setVideoOutput(videoWidget);
    player->setAudioOutput(audioOutput);

}

void MainWindow::updateSource(QUrl mediaPath)
{
    player->setSource(mediaPath);
    player->play();
}
void MainWindow::openFileWindow()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,                               // 父窗口
        tr("选择文件"),                     // 对话框标题
        QDir::homePath(),                  // 默认目录（这里设为用户主目录）
        tr("所有文件 (*.*);;文本文件 (*.txt)") // 文件过滤器
        );

    QString localpath="file:///";

    this->updateSource(QUrl(localpath.append(filePath)));
}
void MainWindow::openUrlWindow()
{
    auto *ouw = new QWidget();
    QLineEdit *inputField = new QLineEdit(ouw);
    QPushButton *btnConfirm = new QPushButton("确认", ouw);
    QPushButton *btnCancel = new QPushButton("取消", ouw);
    // 设置按钮布局（左右分布）
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(btnConfirm);
    buttonLayout->addStretch();      // 添加弹性空间
    buttonLayout->addWidget(btnCancel);

    // 设置主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(ouw);
    mainLayout->addWidget(inputField, 1);    // 输入框占1份空间
    mainLayout->addLayout(buttonLayout, 0);   // 按钮区域保持最小高度
    // 连接信号槽
    connect(btnConfirm, &QPushButton::clicked, ouw, ouw->close);
    connect(btnCancel, &QPushButton::clicked, ouw, ouw->close);

    ouw->show();
    connect(btnConfirm, &QPushButton::clicked, this, [=](){
        if (!inputField->text().isEmpty()) {
            updateSource(QUrl(inputField->text()));
        }
    });
}



void MainWindow::showAboutWindow()
{
    QMessageBox::about(nullptr, "About",
                       "<h2>Multimedia Player</h2>"
                       "<p>Version 0.0.1</p>"
                       "<p>Copyright © 2025 FJdarc</p>"
                       "<p>This is a simple application.</p>");
}
