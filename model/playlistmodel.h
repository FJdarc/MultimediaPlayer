#pragma once

#include <QStringListModel>
#include <QRandomGenerator>

class PlaylistModel : public QStringListModel {
    Q_OBJECT
public:
    explicit PlaylistModel(QObject* parent = nullptr);
    ~PlaylistModel();

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void shuffle();
};