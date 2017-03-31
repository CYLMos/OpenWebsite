#ifndef LISTVIEWMODEL_H
#define LISTVIEWMODEL_H

#include <QAbstractListModel>
#include <QMap>
#include <QList>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>

class  MyData{
public:
    MyData(QString tag, QString url, QString status)
    {
        this->tag = tag;
        this->url = url;
        this->status = status;
    }

    QString tagData(){
        return this->tag;
    }
    QString urlData(){
        return this->url;
    }
    QString statusData(){
        return this->status;
    }

private:
    QString tag;
    QString url;
    QString status;

    QVariant obj;

};

class ListViewModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ListViewModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());

    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

    Q_INVOKABLE void updateView();

    QHash<int, QByteArray> roleNames() const;

    enum dataType {
        tag = 1,
        url = 2,
        status = 3
    };

private:
    QList< MyData > myData;
};

#endif // LISTVIEWMODEL_H
