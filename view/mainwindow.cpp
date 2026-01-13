#include "mainwindow.h"

MainWindow::MainWindow() {
    setupUi();
    setupConnections();
}

MainWindow::~MainWindow() {
}

void MainWindow::setupUi()
{
    if (this->objectName().isEmpty())
        this->setObjectName("MainWindow");
    this->resize(640, 480);
    actionOpen_File = new QAction(this);
    actionOpen_File->setObjectName("actionOpen_File");
    actionOpen_URL = new QAction(this);
    actionOpen_URL->setObjectName("actionOpen_URL");
    centralWidget = new QWidget(this);
    centralWidget->setObjectName("centralWidget");
    graphicsView = new QGraphicsView(centralWidget);
    graphicsView->setFrameStyle(QFrame::NoFrame);
    graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsScene = new QGraphicsScene(graphicsView);
    graphicsView->setScene(graphicsScene);
    graphicsVideoItem = new QGraphicsVideoItem();
    graphicsVideoItem->setObjectName("graphicsVideoItem");
    graphicsVideoItem->setSize(QSize(640, 400));
    graphicsScene->addItem(graphicsVideoItem);
    audioOutput = new QAudioOutput();
    audioOutput->setObjectName("audioOutput");
    mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setObjectName("mediaPlayer");
    mediaPlayer->setVideoOutput(graphicsVideoItem);
    mediaPlayer->setAudioOutput(audioOutput);
    controlPanel = new ControlPanel(centralWidget);
    controlPanel->setObjectName("controlPanel");
    controlPanel->setGeometry(QRect(0, 400, 640, 58));
    controlPanel->setFrameShape(QFrame::Shape::StyledPanel);
    controlPanel->setFrameShadow(QFrame::Shadow::Raised);
    openURL = new OpenURL(centralWidget);
    openURL->setObjectName("openURL");
    openURL->setGeometry(QRect(160, 120, 320, 120));
    openURL->setFrameShape(QFrame::Shape::StyledPanel);
    openURL->setFrameShadow(QFrame::Shadow::Raised);
    openURL->hide();
    playlist = new Playlist(centralWidget);
    playlist->setObjectName("playlist");
    playlist->setGeometry(QRect(480, 0, 160, 385));
    playlist->setFrameShape(QFrame::Shape::StyledPanel);
    playlist->setFrameShadow(QFrame::Shadow::Raised);
    playlist->hide();
    // settings = new QFrame(centralWidget);
    // settings->setObjectName("settings");
    // settings->setGeometry(QRect(480, 0, 160, 385));
    // settings->setFrameShape(QFrame::Shape::StyledPanel);
    // settings->setFrameShadow(QFrame::Shadow::Raised);
    // settings->hide();
    progressBar = new ProgressBar(centralWidget);
    progressBar->setObjectName("progressBar");
    progressBar->setGeometry(QRect(0, 385, 640, 15));
    progressBar->setFrameShape(QFrame::Shape::StyledPanel);
    progressBar->setFrameShadow(QFrame::Shadow::Raised);
    this->setCentralWidget(centralWidget);
    menubar = new QMenuBar(this);
    menubar->setObjectName("menubar");
    menubar->setGeometry(QRect(0, 0, 640, 22));
    menuFile = new QMenu(menubar);
    menuFile->setObjectName("menuFile");
    this->setMenuBar(menubar);

    menubar->addAction(menuFile->menuAction());
    menuFile->addAction(actionOpen_File);
    menuFile->addAction(actionOpen_URL);

    retranslateUi();

    QMetaObject::connectSlotsByName(this);
}

void MainWindow::retranslateUi()
{
    this->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
    actionOpen_File->setText(QCoreApplication::translate("MainWindow", "Open File", nullptr));
    actionOpen_URL->setText(QCoreApplication::translate("MainWindow", "Open URL", nullptr));
    menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
}

void MainWindow::setupConnections() {
    connect(mediaPlayer, &QMediaPlayer::positionChanged,
            this, [this](qint64 position) {
        progressBar->setProgress(position); // 当前进度
        progressBar->setLeftTime(Utils::formatTime(position));
    });
    connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged,
        this, [this](QMediaPlayer::MediaStatus status) {
            if (status == QMediaPlayer::LoadedMedia){
                qint64 duration = mediaPlayer->duration();
                progressBar->progressBar->setRange(0, mediaPlayer->duration());
                progressBar->setProgress(0);

                progressBar->setRightTime(Utils::formatTime(duration));
                mediaPlayer->play();
            }
            else if (status == QMediaPlayer::EndOfMedia) {
                playEnd();
                progressBar->setProgress(0);
                progressBar->setLeftTime("00:00:00");
            }
        });
    connect(playlist->playlistModel, &QAbstractItemModel::dataChanged,
            this,
            [this](const QModelIndex &topLeft,
                   const QModelIndex &bottomRight,
                   const QList<int> &roles) {
        if (topLeft.row() <= 0 && bottomRight.row() >= 0) {
            if (mediaPlayer->source().isEmpty()){
                currentIndex = playlist->playlistModel->index(0, 0);
                QVariant value = playlist->playlistModel->data(currentIndex);
                mediaPlayer->setSource(QUrl::fromLocalFile(value.toString()));
            }
        }
    });
    connect(controlPanel->lastButton, &QPushButton::clicked, this, &MainWindow::playLast);
    connect(controlPanel->nextButton, &QPushButton::clicked, this, &MainWindow::playNext);
}

void MainWindow::playLast() {
    if (!playlist || !playlist->playlistModel)
        return;
    switch (controlPanel->circleMode) {
        case NoREPEAT:
            return;
        case OneREPEAT:
        case ListREPEAT:
            if (currentIndex.isValid()) {
                int nextRow = currentIndex.row() - 1;
                if (nextRow == -1)
                    nextRow = playlist->playlistModel->rowCount() - 1;
                currentIndex = playlist->playlistModel->index(nextRow, 0);
                QString filePath = playlist->playlistModel->data(currentIndex).toString();
                mediaPlayer->setSource(QUrl::fromLocalFile(filePath));
            }
            break;
    }
}

void MainWindow::playNext() {
    if (!playlist || !playlist->playlistModel)
        return;
    switch (controlPanel->circleMode) {
        case NoREPEAT:
            return;
        case OneREPEAT:
        case ListREPEAT:
            if (currentIndex.isValid()) {
                int nextRow = currentIndex.row() + 1;
                if (nextRow == playlist->playlistModel->rowCount())
                    nextRow = 0;
                currentIndex = playlist->playlistModel->index(nextRow, 0);
                QString filePath = playlist->playlistModel->data(currentIndex).toString();
                mediaPlayer->setSource(QUrl::fromLocalFile(filePath));
            }
            break;
    }
}

void MainWindow::playEnd() {
    if (!playlist || !playlist->playlistModel)
        return;
    switch (controlPanel->circleMode) {
        case NoREPEAT:
            return;
        case OneREPEAT:
            mediaPlayer->setPosition(0);
            break;
        case ListREPEAT:
            if (currentIndex.isValid()) {
                int nextRow = currentIndex.row() + 1;
                if (nextRow == playlist->playlistModel->rowCount())
                    nextRow = 0;
                currentIndex = playlist->playlistModel->index(nextRow, 0);
                QString filePath = playlist->playlistModel->data(currentIndex).toString();
                mediaPlayer->setSource(QUrl::fromLocalFile(filePath));
            }
            break;
    }
}


void MainWindow::on_actionOpen_File_triggered() {
    QString mediaPath = Utils::getMediaPath();
    if (!mediaPath.isEmpty())
        mediaPlayer->setSource(QUrl::fromLocalFile(mediaPath));
}

void MainWindow::on_actionOpen_URL_triggered() {
    openURL->show();
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QSize newSize = event->size();

    graphicsView->setGeometry(0,0,newSize.width(),newSize.height() - 58 - 22 - 15);
    graphicsVideoItem->setSize(QSize(newSize.width(), newSize.height()-58-22));
    controlPanel->setGeometry(QRect(0, newSize.height()-58-22, newSize.width(), 58));
    progressBar->setGeometry(QRect(0, newSize.height()-58-22-15, newSize.width(), 15));
    playlist->setGeometry(QRect(newSize.width()-160, 0, 160, newSize.height()-58-22-15));
    openURL->setGeometry(QRect(newSize.width()/2-160, newSize.height()/2-120, 320, 120));

    QWidget::resizeEvent(event); // 保留基类行为
}