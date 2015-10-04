#ifndef MYTABLEMODEL_H
#define MYTABLEMODEL_H

#include <QAbstractTableModel>

class MyTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void insertRow();
    int getSize() const;
    int getNumber(int index) const;

public slots:
    void loadData(QString const& path);
    void saveData(QString const& path) const;

private:
    typedef struct {
        QString label;
        unsigned int number;
    } Record;

    QVector<Record> m_data;
};

#endif // MYTABLEMODEL_H
