#ifndef STARTBROWSER_H
#define STARTBROWSER_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QList>
#include <QProcess>
#include <QVariant>
#include <QDebug>


class StartBrowser : public QObject
{
    Q_OBJECT
public:
    StartBrowser();

    Q_INVOKABLE void start(bool incognito_flag);
};

#endif // STARTBROWSER_H
