#ifndef WIDGETRANDOMGENERATOR_H
#define WIDGETRANDOMGENERATOR_H

#include <QObject>
#include "WebsocketApiIconDelegate.h"
#include <QPixmap>

class WidgetRandomGenerator : public QObject
{
    Q_OBJECT
public:
    explicit WidgetRandomGenerator(WebsocketApiIconDelegate *apiDelegate = nullptr, QString context = "", QObject *parent = nullptr);
    ~WidgetRandomGenerator();
    void doInitAction();
    void doKeyUpAction();
    void doKeyDownAction();
    void doTriggerAction();
    void doPropertyInitial();
    void updateRandomNumberRange(int mix, int max);

private slots:
    void onRandomGeneratorNumber();

private:
    WebsocketApiIconDelegate *m_apiDelegate;
    QString m_contextId;
    QList<QPixmap> m_iconList;
    QString image2Base64(QPixmap pix);
    QPixmap drawNumberText(QString text, QPixmap rawPixmap);
    QTimer *m_randomGeneratorTimer = Q_NULLPTR;
    int m_randomNumber = 0;
    int m_randomMin = 0;
    int m_randomMax = 100;
    int m_randomCounter = 0;

};

#endif // WIDGETRANDOMGENERATOR_H
