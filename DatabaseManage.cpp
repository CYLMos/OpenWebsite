#include "DatabaseManage.h"
#include <QDebug>

DatabaseManage::DatabaseManage()
{
    /*QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("URL_Data");

    //db.setConnectOptions();

    if(db.open()){
        qDebug() << "Open Successed";
    }*/
}

DatabaseManage::~DatabaseManage()
{
    /*QSqlDatabase db = QSqlDatabase::contains("QSQLITE") ?
                QSqlDatabase::database("QSQLITE"):
                QSqlDatabase::addDatabase("QSQLITE", "../OpenWebsite/URL_Data");

    db.setDatabaseName("../OpenWebsite/URL_Data");

    db.close();

    db.removeDatabase("../OpenWebsite/URL_Data");*/
}

bool DatabaseManage::checkLocation(){

    QSqlDatabase db = QSqlDatabase::contains("QSQLITE") ?
                QSqlDatabase::database("QSQLITE"):
                QSqlDatabase::addDatabase("QSQLITE", "../OpenWebsite/URL_Data");

    db.setDatabaseName("../OpenWebsite/URL_Data");


    qDebug() << QSqlDatabase::database("../OpenWebsite/URL_Data") << "123";


    bool status = false;

    if(db.open()){
        QSqlQuery* query = new QSqlQuery("SELECT * FROM browser_location", db);

        if(query->next()){
            status = true;
            qDebug() << query->value(1);
        }

        query->clear();
        delete query;
    }

    return status;
}

void DatabaseManage::addBrowserAddress(QString address){    

    QSqlDatabase db = QSqlDatabase::contains("QSQLITE") ?
                QSqlDatabase::database("QSQLITE"):
                QSqlDatabase::addDatabase("QSQLITE", "../OpenWebsite/URL_Data");

    db.setDatabaseName("../OpenWebsite/URL_Data");


    qDebug() << QSqlDatabase::database("../OpenWebsite/URL_Data");

    if(db.open()){

        /**
         * if query is not an empty string, it will be executed
         * if not empty string, don't exec it
         * query will exec twice after you exec
         *
        **/
        QSqlQuery query("INSERT INTO browser_location (location) VALUES('" + address + "')",db);

        if(query.isActive()){
            qDebug() << "Active";
        }
    }

}

void DatabaseManage::addUrl(QString tag, QString url){
    QSqlDatabase db = QSqlDatabase::contains("QSQLITE") ?
                QSqlDatabase::database("QSQLITE"):
                QSqlDatabase::addDatabase("QSQLITE", "../OpenWebsite/URL_Data");

    db.setDatabaseName("../OpenWebsite/URL_Data");

    if(db.open()){
        QSqlQuery query(db);
        query.prepare("INSERT INTO url_table (tag, url, status) VALUES(:tag, :url, :status)");

        query.bindValue(":tag", tag);
        query.bindValue(":url", url);
        query.bindValue(":status", "Y");

        query.exec();

        if(query.isActive()){
            qDebug() << "Active";
        }
    }
}

void DatabaseManage::removeUrl(QString tag, QString url){
    QSqlDatabase db = QSqlDatabase::contains("QSQLITE") ?
                QSqlDatabase::database("QSQLITE"):
                QSqlDatabase::addDatabase("QSQLITE", "../OpenWebsite/URL_Data");

    db.setDatabaseName("../OpenWebsite/URL_Data");

    if(db.open()){
        QSqlQuery query(db);
        query.prepare("DELETE FROM url_table WHERE tag = :tag AND url = :url");

        query.bindValue(":tag", tag);
        query.bindValue(":url", url);

        query.exec();

        if(query.isActive()){
            qDebug() << "Delete";
        }
    }
}

void DatabaseManage::update(QString tag, QString url, QString status){
    QSqlDatabase db = QSqlDatabase::contains("QSQLITE") ?
                QSqlDatabase::database("QSQLITE"):
                QSqlDatabase::addDatabase("QSQLITE", "../OpenWebsite/URL_Data");

    db.setDatabaseName("../OpenWebsite/URL_Data");

    if(db.open()){
        QSqlQuery query(db);
        query.prepare("UPDATE url_table SET tag = :tag, url = :url, status = :status WHERE tag = :tag AND url = :url");

        query.bindValue(":tag", tag);
        query.bindValue(":url", url);
        query.bindValue(":status", status);

        query.exec();

        if(query.isActive()){
            qDebug() << "Active";
        }
    }
}
