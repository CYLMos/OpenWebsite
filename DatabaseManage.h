#ifndef CHECKBROWSERLOCATION_H
#define CHECKBROWSERLOCATION_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlDriver>


class DatabaseManage : public QObject
{
    Q_OBJECT
public:
    DatabaseManage();
    ~DatabaseManage();
    Q_INVOKABLE bool checkLocation();
    Q_INVOKABLE void addBrowserAddress(QString address);
    Q_INVOKABLE void addUrl(QString tag, QString url);
    Q_INVOKABLE void removeUrl(QString tag, QString url);
    Q_INVOKABLE void update(QString tag, QString url, QString status);

    //Q_INVOKABLE void static getData(QObject* object, QString query);

private:

};

#endif // CHECKBROWSERLOCATION_H
