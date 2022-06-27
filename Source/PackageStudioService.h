#ifndef PACKAGESTUDIOSERVICE_H
#define PACKAGESTUDIOSERVICE_H

#include <QMainWindow>
#include <QJsonObject>
#include "WebsocketApiIconDelegate.h"
#include "qwebsocketserver.h"

class PackageStudioService : public QMainWindow
{
    Q_OBJECT

public:
    PackageStudioService(QString inPort, QString inPackageUUID, QString inRegisterEvent, QString inInfo, QWidget *parent = nullptr);
    ~PackageStudioService();
    void initSocketClientIcon(int inPort, QString inPackageUUID, QString inRegisterEvent, QString inInfo);

private slots:
    void onServerIconResponseReceived(const QJsonObject &obj);

private:
    WebsocketApiIconDelegate *m_socketApiIconDelegate = Q_NULLPTR;
    QList<QObject*> m_widgetsInstance;
    void receiveWidgetSettings(QString widgetCategory, QString context, QJsonObject payload);
    void createWidget(QString widgetCategory, QString context);
    void deleteWidget(QString context);
    void keyDownWidget(QString widgetCategory, QString context);
    void keyUpWidget(QString widgetCategory, QString context);
    void triggerWidget(QString widgetCategory, QString context);
    void propertyUiInitial(QString widgetCategory, QString context);
    QWebSocket *m_socketIcon;
    QString m_counterContext;
    QString m_randomGeneratorContext;
};
#endif // PACKAGESTUDIOSERVICE_H
