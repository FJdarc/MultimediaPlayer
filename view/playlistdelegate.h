#pragma once

#include "utils.h"

#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include <QStyledItemDelegate>
#include <QSize>

class PlaylistDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit PlaylistDelegate(QObject* parent = nullptr);
    ~PlaylistDelegate();

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize	sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
protected:
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
private:
    QRect deleteRect(const QStyleOptionViewItem &option) const;
};