#pragma once

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>

class ProgressBar : public QFrame {
    Q_OBJECT
public:
    explicit ProgressBar(QWidget* parent = nullptr);
    ~ProgressBar();

    QProgressBar *progressBar;
    QLabel *startlabel;
    QLabel *endlabel;

    void setupUi();
    void retranslateUi();

    void setupConnections();

    void setProgress(int value) { progressBar->setValue(value); }
    void setLeftTime(const QString &time) { startlabel->setText(time); }
    void setRightTime(const QString &time) { endlabel->setText(time); }
protected:
    void resizeEvent(QResizeEvent *event) override;
};