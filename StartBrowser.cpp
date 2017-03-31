#include "StartBrowser.h"

StartBrowser::StartBrowser()
{

}

void StartBrowser::start(bool incognito_flag){

    QSqlDatabase db = QSqlDatabase::contains("QSQLITE") ?
                QSqlDatabase::database("QSQLITE"):
                QSqlDatabase::addDatabase("QSQLITE", "../OpenWebsite/URL_Data");

    db.setDatabaseName("../OpenWebsite/URL_Data");

    if(db.open()){
        QSqlQuery query("SELECT * FROM browser_location", db);

        QString location;
        QList<QString> urlList;

        if(query.isActive()){
            qDebug() << "Active111";
        }

        if(query.next()){
            QVariant value = query.value("location");
            location = "\"" + value.toString() + "\"";//"\"C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe\"";
        }

        QSqlQuery query2("SELECT url FROM url_table WHERE status = 'Y'", db);

        while(query2.next()){
            QVariant value = query2.value("url");
            urlList.push_back(value.toString());
        }

        QString commandLine = location;
        if(incognito_flag == true){
            commandLine += " --incognito";
        }

        for(int index = 0; index < urlList.length(); index++){
            commandLine += " --new-tab-page " + urlList.at(index);
        }

        QProcess::execute(commandLine);
    }
}
