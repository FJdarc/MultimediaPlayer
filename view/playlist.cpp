#include "playlist.h"

Playlist::Playlist(QWidget *parent)
    : QFrame(parent){
    setupUi();
    setupConnections();
    setStyleSheet("background-color: white;");
    playlistModel = new PlaylistModel();
    playlistDelegate = new PlaylistDelegate();
    listView->setModel(playlistModel);
    listView->setItemDelegate(playlistDelegate);
}

Playlist::~Playlist() {
}

void Playlist::setupUi() {
    if (this->objectName().isEmpty())
        this->setObjectName("Playlist");
    this->resize(160, 385);
    label = new QLabel(this);
    label->setObjectName("label");
    label->setGeometry(QRect(10, 10, 70, 32));
    QFont font;
    font.setPointSize(15);
    label->setFont(font);
    addButton = new QPushButton(this);
    addButton->setObjectName("addButton");
    addButton->setGeometry(QRect(118, 10, 32, 32));
    listView = new QListView(this);
    listView->setObjectName("listView");
    listView->setGeometry(QRect(10, 52, 140, 323));
    listView->setFrameShape(QFrame::Shape::StyledPanel);
    listView->setFrameShadow(QFrame::Shadow::Raised);

    retranslateUi();

    QMetaObject::connectSlotsByName(this);
}

void Playlist::retranslateUi() {
    this->setWindowTitle(QCoreApplication::translate("Playlist", "Playlist", nullptr));
    label->setText(QCoreApplication::translate("Playlist", "Playlist", nullptr));
    addButton->setText(QCoreApplication::translate("Playlist", "add", nullptr));
}

void Playlist::setupConnections() {
}

void Playlist::on_addButton_clicked() {
    QString mediaPath = Utils::getMediaPath();

    if (mediaPath.isEmpty())
        return;
    int row = playlistModel->rowCount();
    playlistModel->insertRow(row);

    QModelIndex index = playlistModel->index(row);
    playlistModel->setData(index, mediaPath);
}

void Playlist::resizeEvent(QResizeEvent *event) {
    QSize newSize = event->size();

    listView->setGeometry(QRect(10, 52, 140, newSize.height()-62));

    QWidget::resizeEvent(event); // 保留基类行为
}