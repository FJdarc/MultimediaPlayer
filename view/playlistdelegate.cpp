#include "playlistdelegate.h"


PlaylistDelegate::PlaylistDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {}
PlaylistDelegate::~PlaylistDelegate() {
}

QRect PlaylistDelegate::deleteRect(const QStyleOptionViewItem &option) const {
    const int w = 40;
    return QRect(option.rect.right() - w,
                 option.rect.top(),
                 w,
                 option.rect.height());
}

void PlaylistDelegate::paint(QPainter *painter,
                             const QStyleOptionViewItem &option,
                             const QModelIndex &index) const {
    painter->save();

    if (option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, option.palette.highlight());

    // 获取原始文本
    QString text = Utils::getMediaName(index.data().toString());

    // 创建 elided 文本（超过 rect 显示 ...）
    QFontMetrics fm(option.font);
    QString elidedText = fm.elidedText(text, Qt::ElideRight, 135 - 50);
    // -50 给右侧 Del 按钮留空间

    QRect textRect = option.rect.adjusted(5, 0, -45, 0);
    painter->setPen(option.palette.text().color());
    painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, elidedText);

    // 右侧 Del 按钮
    QRect delRect = deleteRect(option);
    painter->setBrush(Qt::red);
    painter->setPen(Qt::NoPen);
    painter->drawRect(delRect);
    painter->setPen(Qt::white);
    painter->drawText(delRect, Qt::AlignCenter, "Del");

    painter->restore();
}


bool PlaylistDelegate::editorEvent(QEvent *event,
                                   QAbstractItemModel *model,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index) {
    if (event->type() == QEvent::MouseButtonRelease) {
        auto *e = static_cast<QMouseEvent *>(event);

        if (deleteRect(option).contains(e->pos())) {
            // ⭐ 核心：直接删
            model->removeRow(index.row());
            return true;
        }
    }
    return false;
}

QSize PlaylistDelegate::sizeHint(const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const {
    QSize s = QStyledItemDelegate::sizeHint(option, index);
    s.setWidth(135); // 限制宽度，例如 200px
    return s;
}
