#include "playlistmodel.h"

PlaylistModel::PlaylistModel(QObject *parent) {
}

PlaylistModel::~PlaylistModel() {
}

Qt::ItemFlags PlaylistModel::flags(const QModelIndex &index) const {
    return Qt::NoItemFlags;
}

void PlaylistModel::shuffle() {
    QStringList list = stringList();

    if (list.size() <= 1)
        return;

    std::shuffle(
        list.begin(),
        list.end(),
        *QRandomGenerator::global()
    );

    setStringList(list);
}
