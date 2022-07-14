#include "PackageStudioService.h"
#include "QJsonObject"
#include "model/EventType.h"
#include "model/WidgetCategory.h"
#include "qdebug.h"
// Widgets
#include "widgets/WidgetCounter.h"
#include "widgets/WidgetRandomGenerator.h"

PackageStudioService::PackageStudioService(QString inPort, QString inPackageUUID, QString inRegisterEvent, QString inInfo, QWidget *parent)
    : QMainWindow(parent)
    , m_socketApiIconDelegate(new WebsocketApiIconDelegate())
{
    // Plugin Icon
    initSocketClientIcon(inPort.toInt(), inPackageUUID, inRegisterEvent, inInfo);
}

PackageStudioService::~PackageStudioService()
{
    if (m_socketApiIconDelegate)
    {
        m_socketApiIconDelegate->deleteLater();
        m_socketApiIconDelegate = Q_NULLPTR;
    }
}

void PackageStudioService::initSocketClientIcon(int inPort, QString inPackageUUID, QString inRegisterEvent, QString inInfo)
{
    connect(m_socketApiIconDelegate, &WebsocketApiIconDelegate::serverResponse,
            this, &PackageStudioService::onServerIconResponseReceived);
    m_socketApiIconDelegate->connectToServer(inPort, inPackageUUID, inRegisterEvent);
}

void PackageStudioService::onServerIconResponseReceived(const QJsonObject &obj)
{
    QString eventType = obj["event"].toString(); // Event Type
    QString widget = obj["widget"].toString();
    QString context = obj["context"].toString(); // UUID
    QJsonObject payload = obj["payload"].toObject();

    if (eventType == PluginEventReceived::kDidReceiveWidgetSettings)
    {
        receiveWidgetSettings(widget, context, payload);
    }
    else if (eventType == PluginEventReceived::kDidReceivePackageSettings)
    {

    }
    else if (eventType == PluginEventReceived::kActionDown)
    {
        keyDownWidget(widget, context);
    }
    else if (eventType == PluginEventReceived::kActionUp)
    {
        keyUpWidget(widget, context);
    }
    else if (eventType == PluginEventReceived::kActionTriggered)
    {
        triggerWidget(widget, context);
    }
    else if (eventType == PluginEventReceived::kWidgetWillAppear)
    {
        createWidget(widget, context);
    }
    else if (eventType == PluginEventReceived::kWidgetWillDisappear)
    {
        deleteWidget(context);
    }
    else if (eventType == PluginEventReceived::kPropertyViewDidAppear)
    {
        propertyUiInitial(widget, context);
    }
    else if (eventType == PluginEventReceived::kPropertyViewDidDisappear)
    {

    }
    else if (eventType == PluginEventReceived::kSendToPackage)
    {

    }
    else if (eventType == PluginEventReceived::kSendToPropertyView)
    {

    }
}

void PackageStudioService::receiveWidgetSettings(QString widgetCategory, QString context, QJsonObject payload)
{
    for (int i = 0 ; i < m_widgetsInstance.count() ; i++)
    {
        if (m_widgetsInstance.at(i)->objectName() == context)
        {
            if (widgetCategory == WidgetCategory::kWidgetCounter)
            {

            }
            else if (widgetCategory == WidgetCategory::kWidgetRandomGenerator)
            {
                QJsonArray saveDatas = payload.value("saveData").toArray();
                int min = 0;
                int max = 100;
                for (auto saveDate : saveDatas)
                {
                    QString numberId = saveDate.toObject().value("number_id").toString();
                    if (numberId == "number_1")
                    {
                        min = saveDate.toObject().value("text_content").toInt();
                    }
                    else if (numberId == "number_2")
                    {
                        max = saveDate.toObject().value("text_content").toInt();
                    }
                }
                static_cast<WidgetRandomGenerator*>(m_widgetsInstance.at(i))->updateRandomNumberRange(min, max);
                break;
            }
        }
    }
}

void PackageStudioService::createWidget(QString widgetCategory, QString context)
{
    if (widgetCategory == WidgetCategory::kWidgetCounter)
    {
        WidgetCounter *widgetCounter = new WidgetCounter(m_socketApiIconDelegate, context);
        widgetCounter->setObjectName(context);
        m_widgetsInstance.push_back(widgetCounter);
        widgetCounter->doInitAction();
    }
    else if (widgetCategory == WidgetCategory::kWidgetRandomGenerator)
    {
        WidgetRandomGenerator *widgetRandomGenerator = new WidgetRandomGenerator(m_socketApiIconDelegate, context);
        widgetRandomGenerator->setObjectName(context);
        m_widgetsInstance.push_back(widgetRandomGenerator);
        widgetRandomGenerator->doInitAction();
    }
}

void PackageStudioService::deleteWidget(QString context)
{
    for (int i = 0 ; i < m_widgetsInstance.count() ; i++)
    {
        if (m_widgetsInstance.at(i)->objectName() == context)
        {
            QObject *widget = m_widgetsInstance.at(i);
            m_widgetsInstance.removeOne(widget);
            widget->setObjectName("");
            widget->deleteLater();
            widget = Q_NULLPTR;
            break;
        }
    }
}

void PackageStudioService::keyDownWidget(QString widgetCategory, QString context)
{
    for (int i = 0 ; i < m_widgetsInstance.count() ; i++)
    {
        if (m_widgetsInstance.at(i)->objectName() == context)
        {
            if (widgetCategory == WidgetCategory::kWidgetCounter)
            {
                static_cast<WidgetCounter*>(m_widgetsInstance.at(i))->doKeyDownAction();
                break;
            }
            else if (widgetCategory == WidgetCategory::kWidgetRandomGenerator)
            {
                static_cast<WidgetRandomGenerator*>(m_widgetsInstance.at(i))->doKeyDownAction();
                break;
            }
        }
    }
}

void PackageStudioService::keyUpWidget(QString widgetCategory, QString context)
{
    for (int i = 0 ; i < m_widgetsInstance.count() ; i++)
    {
        if (m_widgetsInstance.at(i)->objectName() == context)
        {
            if (widgetCategory == WidgetCategory::kWidgetCounter)
            {
                static_cast<WidgetCounter*>(m_widgetsInstance.at(i))->doKeyUpAction();
                break;
            }
            else if (widgetCategory == WidgetCategory::kWidgetRandomGenerator)
            {
                static_cast<WidgetRandomGenerator*>(m_widgetsInstance.at(i))->doKeyUpAction();
                break;
            }
        }
    }
}

void PackageStudioService::triggerWidget(QString widgetCategory, QString context)
{
    for (int i = 0 ; i < m_widgetsInstance.count() ; i++)
    {
        if (m_widgetsInstance.at(i)->objectName() == context)
        {
            if (widgetCategory == WidgetCategory::kWidgetCounter)
            {
                static_cast<WidgetCounter*>(m_widgetsInstance.at(i))->doTriggerAction();
                break;
            }
            else if (widgetCategory == WidgetCategory::kWidgetRandomGenerator)
            {
                static_cast<WidgetRandomGenerator*>(m_widgetsInstance.at(i))->doTriggerAction();
                break;
            }
        }
    }
}

void PackageStudioService::propertyUiInitial(QString widgetCategory, QString context)
{
    for (int i = 0 ; i < m_widgetsInstance.count() ; i++)
    {
        if (m_widgetsInstance.at(i)->objectName() == context)
        {
            if (widgetCategory == WidgetCategory::kWidgetCounter)
            {
                break;
            }
            else if (widgetCategory == WidgetCategory::kWidgetRandomGenerator)
            {
                static_cast<WidgetRandomGenerator*>(m_widgetsInstance.at(i))->doPropertyInitial();
                break;
            }
        }
    }
}
