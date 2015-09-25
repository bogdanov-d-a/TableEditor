#include "mytablemodel.h"

int MyTableModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

int MyTableModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant MyTableModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    Record const& dataElem = m_data[index.row()];

    if (index.column() == 0)
        return QVariant(dataElem.label);
    else
        return QVariant(dataElem.number);
}

bool MyTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return QAbstractTableModel::setData(index, value,role);

    Record &dataElem = m_data[index.row()];

    if (index.column() == 0)
        dataElem.label = value.toString();
    else
        dataElem.number = value.toInt();

    emit layoutChanged();
    return true;
}

Qt::ItemFlags MyTableModel::flags(const QModelIndex &index) const
{
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

void MyTableModel::insertRow()
{
    m_data.push_back({ "label", 0 });
    emit layoutChanged();
}
