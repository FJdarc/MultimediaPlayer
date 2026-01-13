#include "openurl.h"

OpenURL::OpenURL(QWidget *parent)
    : QFrame(parent){
    setupUi();
    setupConnections();
    setStyleSheet("background-color: rgba(255, 255, 255, 128);");
    label->setStyleSheet("background: transparent;");
}

OpenURL::~OpenURL() {
}

void OpenURL::setupUi() {
    if (this->objectName().isEmpty())
        this->setObjectName("OpenURL");
    this->resize(320, 120);
    cancelButton = new QPushButton(this);
    cancelButton->setObjectName("cancelButton");
    cancelButton->setGeometry(QRect(80, 80, 60, 30));
    loadButton = new QPushButton(this);
    loadButton->setObjectName("loadButton");
    loadButton->setGeometry(QRect(180, 80, 60, 30));
    label = new QLabel(this);
    label->setObjectName("label");
    label->setGeometry(QRect(115, 10, 90, 30));
    lineEdit = new QLineEdit(this);
    lineEdit->setObjectName("lineEdit");
    lineEdit->setGeometry(QRect(20, 40, 280, 30));

    retranslateUi();

    QMetaObject::connectSlotsByName(this);
}

void OpenURL::retranslateUi() {
    this->setWindowTitle(QCoreApplication::translate("OpenURL", "OpenURL", nullptr));
    cancelButton->setText(QCoreApplication::translate("OpenURL", "Cancel", nullptr));
    loadButton->setText(QCoreApplication::translate("OpenURL", "Load", nullptr));
    label->setText(QCoreApplication::translate("OpenURL", "Load from URL", nullptr));
    lineEdit->setPlaceholderText(QCoreApplication::translate("OpenURL", "URL:", nullptr));
}

void OpenURL::setupConnections() {
}

void OpenURL::on_cancelButton_clicked() {
    this->hide();
}

void OpenURL::on_loadButton_clicked() {
    auto mediaPlayer = parent()->parent()->findChild<QMediaPlayer*>("mediaPlayer");
    mediaPlayer->setSource(QUrl(lineEdit->text()));
    this->hide();
}
