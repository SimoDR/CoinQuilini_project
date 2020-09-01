#include "punteggiopanel.h"

punteggioPanel::punteggioPanel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant punteggioPanel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex punteggioPanel::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex punteggioPanel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int punteggioPanel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int punteggioPanel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant punteggioPanel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
