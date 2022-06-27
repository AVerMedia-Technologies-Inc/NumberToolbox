#ifndef WEBSOCKETAPIICONDELEGATE_H
#define WEBSOCKETAPIICONDELEGATE_H

#include <QObject>
#include <QtWebSockets>

class WebsocketApiIconDelegate : public QObject
{
    Q_OBJECT
public:
    explicit WebsocketApiIconDelegate(QObject *parent = nullptr);
    ~WebsocketApiIconDelegate();
    void connectToServer(int port, QString inPackageUUID, QString inRegisterEvent);
    // Events Sent
    void sentSetWidgetSettings(QString context, QJsonObject payload);
    void sentGetWidgetSettings(QString context);
    void sentSetPackageSettings(QString context, QJsonObject payload);
    void sentGetPackageSettings(QString context);
    void sentSendLog(QString log);
    void sentChangeTitle(QString context, QJsonObject payload);
    void sentChangeImage(QString context, QJsonObject payload);
    void sentChangeState(QString context, QJsonObject payload);
    void sentSendToPropertyView(QString widget, QString context, QJsonObject payload);
    void sentSendToPackage(QString widget, QString context, QJsonObject payload);

signals:
    void serverResponse(const QJsonObject &result);

private:
    QWebSocket *m_clientSocket = Q_NULLPTR;
    // Package Registration
    QString m_inPackageUUID;
    void sentRegistration(QString inPackageUUID, QString inRegisterEvent);


};

#endif // WEBSOCKETAPIICONDELEGATE_H
