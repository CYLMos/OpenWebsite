#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>
#include <QAbstractItemModel>
#include <QAbstractListModel>
#include "DatabaseManage.h"
#include "ListViewModel.h"
#include "StartBrowser.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QScopedPointer<DatabaseManage> databaseManager(new DatabaseManage);

    QScopedPointer<ListViewModel> listViewModel(new ListViewModel);

    //QAbstractItemModel* model = new ListViewModel();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("database", databaseManager.data());
    engine.rootContext()->setContextProperty("list_view_model", new ListViewModel());
    engine.rootContext()->setContextProperty("browser",new StartBrowser() );

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
