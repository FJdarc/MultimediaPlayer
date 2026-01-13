#pragma once

#include "playlistmodel.h"
#include "playlistdelegate.h"
#include "utils.h"

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>

class Playlist : public QFrame {
    Q_OBJECT
public:
    explicit Playlist(QWidget* parent = nullptr);
    ~Playlist();

    QLabel *label;
    QPushButton *addButton;
    QListView *listView;

    PlaylistModel *playlistModel;
    PlaylistDelegate *playlistDelegate;

    void setupUi();
    void retranslateUi();

    void setupConnections();
protected:
    void resizeEvent(QResizeEvent *event) override;
public slots:
    void on_addButton_clicked();
};