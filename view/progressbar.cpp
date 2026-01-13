#include "progressbar.h"

#include <qevent.h>

ProgressBar::ProgressBar(QWidget *parent)
    : QFrame(parent) {
    setupUi();
    setupConnections();
    setStyleSheet("background-color: rgba(255, 255, 255, 128);");
    progressBar->setStyleSheet("background: transparent;");
    startlabel->setStyleSheet("background: transparent;");
    endlabel->setStyleSheet("background: transparent;");
}

ProgressBar::~ProgressBar() {
}

void ProgressBar::setupUi() {
    if (this->objectName().isEmpty())
        this->setObjectName("ProgressBar");
    this->resize(640, 15);
    progressBar = new QProgressBar(this);
    progressBar->setObjectName("progressBar");
    progressBar->setGeometry(QRect(60, 0, 520, 15));
    progressBar->setValue(0);
    progressBar->setTextVisible(false);
    startlabel = new QLabel(this);
    startlabel->setObjectName("startlabel");
    startlabel->setGeometry(QRect(5, 0, 50, 15));
    endlabel = new QLabel(this);
    endlabel->setObjectName("endlabel");
    endlabel->setGeometry(QRect(585, 0, 50, 15));

    retranslateUi();

    QMetaObject::connectSlotsByName(this);
}

void ProgressBar::retranslateUi() {
    this->setWindowTitle(QCoreApplication::translate("ProgressBar", "Frame", nullptr));
    startlabel->setText(QCoreApplication::translate("ProgressBar", "00:00:00", nullptr));
    endlabel->setText(QCoreApplication::translate("ProgressBar", "00:00:00", nullptr));
}

void ProgressBar::setupConnections() {
}
void ProgressBar::resizeEvent(QResizeEvent *event) {
    QSize newSize = event->size();

    progressBar->setGeometry(QRect(60, 0, newSize.width()-60-60, 15));
    endlabel->setGeometry(QRect(newSize.width()-55, 0, 50, 15));

    QWidget::resizeEvent(event); // 保留基类行为
}