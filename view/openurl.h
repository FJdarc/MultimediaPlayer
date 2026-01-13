#pragma once

#include <QtCore/QUrl>
#include <QtCore/QVariant>
#include <QtMultimedia/QMediaPlayer>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

class OpenURL : public QFrame {
    Q_OBJECT
public:
    explicit OpenURL(QWidget* parent = nullptr);
    ~OpenURL();

    QPushButton *cancelButton;
    QPushButton *loadButton;
    QLabel *label;
    QLineEdit *lineEdit;

    void setupUi();
    void retranslateUi();

    void setupConnections();

public slots:
    void on_cancelButton_clicked();
    void on_loadButton_clicked();
};