#include "WebsocketApiIconDelegate.h"
#include "model/EventType.h"
#include "qdebug.h"

WebsocketApiIconDelegate::WebsocketApiIconDelegate(QObject *parent)
    : QObject{parent}
    , m_clientSocket(new QWebSocket)
{

}

WebsocketApiIconDelegate::~WebsocketApiIconDelegate()
{
    if (m_clientSocket)
    {
        m_clientSocket->close();
        m_clientSocket->deleteLater();
        m_clientSocket = Q_NULLPTR;
    }
}

void WebsocketApiIconDelegate::connectToServer(int port, QString inPackageUUID, QString inRegisterEvent)
{
    m_inPackageUUID = inPackageUUID;

    auto url = QString("ws://127.0.0.1:%1").arg(port);
    m_clientSocket->open(QUrl(url));
    connect(m_clientSocket, &QWebSocket::connected, this, [=]()
    {
        sentRegistration(inPackageUUID, inRegisterEvent);
    });

    connect(m_clientSocket, &QWebSocket::textMessageReceived, this, [=](const QString& msg)
    {
        QJsonDocument doc = QJsonDocument::fromJson(msg.toUtf8());
        QJsonObject obj;
//        if(doc.isObject())
//        {
            obj = doc.object();
//        }
//        else
//        {
//            obj.insert("error", "Content was broken");
//        }
        emit serverResponse(obj);
    });

    connect(m_clientSocket, &QWebSocket::disconnected, this, [=]()
    {

    });
}

// Package Registration
void WebsocketApiIconDelegate::sentRegistration(QString inPackageUUID, QString inRegisterEvent)
{
    QJsonObject jsonRegistration;
    jsonRegistration.insert("event", inRegisterEvent);
    jsonRegistration.insert("uuid", inPackageUUID);
    QJsonDocument doc(jsonRegistration);
    QString registration(doc.toJson(QJsonDocument::Compact));
    m_clientSocket->sendTextMessage(registration);
}

// Events Sent : setWidgetSettings
void WebsocketApiIconDelegate::sentSetWidgetSettings(QString context, QJsonObject payload)
{
    QJsonObject param;
    param.insert("event", PluginEventSent::kSetWidgetSettings);
    param.insert("context", context);
    param.insert("payload", payload); // A JSON object which is persistently saved for the widget's instance.

    QJsonDocument doc(param);
    QString setWidgetSettings(doc.toJson(QJsonDocument::Compact));
    m_clientSocket->sendTextMessage(setWidgetSettings);
}

// Events Sent : getWidgetSettings
void WebsocketApiIconDelegate::sentGetWidgetSettings(QString context)
{
    QJsonObject param;
    param.insert("event", PluginEventSent::kGetWidgetSettings);
    param.insert("context", context);

    QJsonDocument doc(param);
    QString getWidgetSettings(doc.toJson(QJsonDocument::Compact));
    m_clientSocket->sendTextMessage(getWidgetSettings);
}

// Events Sent : setPackageSettings
void WebsocketApiIconDelegate::sentSetPackageSettings(QString context, QJsonObject payload)
{
    QJsonObject param;
    param.insert("event", PluginEventSent::kSetPackageSettings);
    param.insert("context", context);
    param.insert("payload", payload);

    QJsonDocument doc(param);
    QString setPackageSettings(doc.toJson(QJsonDocument::Compact));
    m_clientSocket->sendTextMessage(setPackageSettings);
}

// Events Sent : getWidgetSettings
void WebsocketApiIconDelegate::sentGetPackageSettings(QString context)
{
    QJsonObject param;
    param.insert("event", PluginEventSent::kGetPackageSettings);
    param.insert("context", context);

    QJsonDocument doc(param);
    QString getPackageSettings(doc.toJson(QJsonDocument::Compact));
    m_clientSocket->sendTextMessage(getPackageSettings);
}

// Events Sent : sendLog
void WebsocketApiIconDelegate::sentSendLog(QString log)
{
    QJsonObject param;
    param.insert("event", PluginEventSent::kSendLog);

    QJsonObject message;
    message.insert("message", log);
    param.insert("payload", message);

    QJsonDocument doc(param);
    QString sendLog(doc.toJson(QJsonDocument::Compact));
    m_clientSocket->sendTextMessage(sendLog);
}

void WebsocketApiIconDelegate::sentChangeTitle(QString context, QJsonObject payload)
{
    // payload content sample
    // "payload" : {"title": "New Title","state": zero-based integer}

    QJsonObject param;
    param.insert("event", PluginEventSent::kChangeTitle);
    param.insert("context", context);
    param.insert("payload", payload);

    QJsonDocument doc(param);
    QString changeTitle(doc.toJson(QJsonDocument::Compact));
    m_clientSocket->sendTextMessage(changeTitle);
}

void WebsocketApiIconDelegate::sentChangeImage(QString context, QJsonObject payload)
{
    // payload content sample
    // "payload" : {"image": <base64 encoded image>,"state": zero-based integer}

    QJsonObject param;
    param.insert("event", PluginEventSent::kChangeImage);
    param.insert("context", context);
    param.insert("payload", payload);

    QJsonDocument doc(param);
    QString changeImage(doc.toJson(QJsonDocument::Compact));
    m_clientSocket->sendTextMessage(changeImage);
}

void WebsocketApiIconDelegate::sentChangeState(QString context, QJsonObject payload)
{
    // payload content sample
    // "payload" : {"state": zero-based integer}

    QJsonObject param;
    param.insert("event", PluginEventSent::kChangeState);
    param.insert("context", context);
    param.insert("payload", payload);

    QJsonDocument doc(param);
    QString changeState(doc.toJson(QJsonDocument::Compact));
    m_clientSocket->sendTextMessage(changeState);
}

void WebsocketApiIconDelegate::sentSendToPropertyView(QString widget, QString context, QJsonObject payload)
{
    QJsonObject param;
    param.insert("widget", widget);
    param.insert("event", PluginEventSent::kSendToPropertyView);
    param.insert("context", context);
    param.insert("payload", payload);

    QJsonDocument doc(param);
    QString sendToPropertyView(doc.toJson(QJsonDocument::Compact));
    m_clientSocket->sendTextMessage(sendToPropertyView);
}

void WebsocketApiIconDelegate::sentSendToPackage(QString widget, QString context, QJsonObject payload)
{
    QJsonObject param;
    param.insert("widget", widget);
    param.insert("event", PluginEventSent::kSendToPackage);
    param.insert("context", context);
    param.insert("payload", payload);

    QJsonDocument doc(param);
    QString sendToPackage(doc.toJson(QJsonDocument::Compact));
    m_clientSocket->sendTextMessage(sendToPackage);
}
