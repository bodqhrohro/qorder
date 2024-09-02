#include "actions_model.h"
#include <QApplication>

ActionsModel::ActionsModel(QObject *parent) : QAbstractItemModel(parent)
{
}

ActionsModel::~ActionsModel() = default;

QModelIndex ActionsModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row, column, &parent);
}

QModelIndex ActionsModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child)

    return QModelIndex();
}

int ActionsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return actions.size();
}

int ActionsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return 4;
}

QVariant ActionsModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DecorationRole) {
	switch (index.column()) {
	case 0:
	case 2:
	    return QApplication::style()->standardIcon(QStyle::SP_MessageBoxWarning);
	}
    } else if (role == Qt::DisplayRole) {
	switch (index.column()) {
	case 1:
	    return actions.at(index.row()).source;
	case 3:
	    return actions.at(index.row()).dest;
	}
    }

    return QVariant();
}

QVariant ActionsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
	switch (section) {
	case 0:
	    return tr("");
	case 1:
	    return tr("Source");
	case 2:
	    return tr("");
	case 3:
	    return tr("Destination");
	}
    }

    return QVariant();
}

bool ActionsModel::insertRows(int row, int count, const QModelIndex &parent)
{
    this->beginInsertRows(parent, row, row+count-1);
    actions.insert(row, count, Action("", ""));
    this->endInsertRows();

    return true;
}

void ActionsModel::addAction(const QString source, const QString dest)
{
    this->beginInsertRows(QModelIndex(), actions.size(), actions.size());
    actions.push_back(Action(source, dest));
    this->endInsertRows();

    Q_EMIT dataChanged();
}
