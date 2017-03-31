#include "ListViewModel.h"

ListViewModel::ListViewModel(QObject* parent)
    : QAbstractListModel(parent)
{
    QSqlDatabase db = QSqlDatabase::contains("QSQLITE") ?
                QSqlDatabase::database("QSQLITE"):
                QSqlDatabase::addDatabase("QSQLITE", "../OpenWebsite/URL_Data");

    db.setDatabaseName("../OpenWebsite/URL_Data");

    if(db.open()){
        QSqlQuery query("SELECT tag, url, status FROM url_table", db);

        qDebug() << "aaaaa";

        while(query.next()){
            QVariant tag = query.value("tag");
            QVariant url = query.value("url");
            QVariant status = query.value("status");

            MyData subData(tag.toString(), url.toString(), status.toString());

            this->myData.push_back(subData);

        }

        if(query.isActive()){
            qDebug() << "aaaaa";
        }
    }

}

void ListViewModel::updateView(){
    beginResetModel();
    endResetModel();
}

int ListViewModel::rowCount(const QModelIndex &parent) const{
    return this->myData.size();
}

QVariant ListViewModel::data(const QModelIndex &index, int role) const{

    if (!index.isValid())
        return QVariant();

    if (index.row() >= this->myData.size())
        return QVariant();

    MyData data = this->myData.at(index.row());
    if (role == this->dataType::tag){
        return data.tagData();
    }
    else if(role == this->dataType::url){
        return data.urlData();
    }
    else if(role == this->dataType::status){
        return data.statusData();
    }
    else
        return QVariant();

    return QVariant();
}

QVariant ListViewModel::headerData(int section, Qt::Orientation orientation, int role) const{
    return QVariant();
}

bool ListViewModel::insertRows(int position, int rows, const QModelIndex &index){
    beginInsertColumns(QModelIndex(), position, position+rows-1);

    /*for (int row = 0; row < rows; ++row) {
        QMap<QString, QString> data;
        QString keys[3] = {"tag","url","status"};

        QMap<QString, QString> subData;
        subData.insert(keys[0], keys[0]);
        subData.insert(keys[1], keys[1]);
        subData.insert(keys[2], keys[2]);

        this->myData.push_back(subData);
    }
*/
    endInsertRows();
    return true;
}

bool ListViewModel::removeRows(int position, int rows, const QModelIndex &index){
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        this->myData.removeAt(position);
    }

    endRemoveRows();
    return true;
}

QHash<int, QByteArray> ListViewModel::roleNames() const{
    QHash<int, QByteArray> d ;
    d[dataType::tag] = "tag";
    d[dataType::url] = "url";
    d[dataType::status] = "status";

    return d;
}
