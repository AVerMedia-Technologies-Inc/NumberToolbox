#ifndef WIDGETCOUNTER_H
#define WIDGETCOUNTER_H

#include <QObject>
#include "WebsocketApiIconDelegate.h"
#include <QPixmap>

class WidgetCounter : public QObject
{
    Q_OBJECT
public:
    explicit WidgetCounter(WebsocketApiIconDelegate *apiDelegate = nullptr, QString context = "", QObject *parent = nullptr);
    ~WidgetCounter();
    void doInitAction();
    void doKeyUpAction();
    void doKeyDownAction();
    void doTriggerAction();

private:
    WebsocketApiIconDelegate *m_apiDelegate = nullptr;
    QString m_contextId;
    QList<QPixmap> m_iconList;
    QString image2Base64(QPixmap pix);
    QPixmap drawCounterNumber(QString text, QPixmap rawPixmap);
    QTimer *m_longPressTimer = Q_NULLPTR;
    int m_counter = 0;
    bool m_isLongPress = false;

};

#endif // WIDGETCOUNTER_H
