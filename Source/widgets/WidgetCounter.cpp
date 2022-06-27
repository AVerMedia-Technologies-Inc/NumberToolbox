#include "WidgetCounter.h"
#include "qfont.h"
#include "qpixmap.h"
#include "QPainter"
#include "QGraphicsView"

WidgetCounter::WidgetCounter(WebsocketApiIconDelegate *apiDelegate, QString context, QObject *parent)
    : QObject{parent}
    , m_apiDelegate(apiDelegate)
    , m_contextId(context)
{
    m_iconList << QPixmap(":/images/mainpage_btn_tool_counter_bg.svg");
}

WidgetCounter::~WidgetCounter()
{
    m_counter = 0;
    m_contextId = "";
}

void WidgetCounter::doInitAction()
{
    QPixmap rawPix = m_iconList[0];

    QPixmap textPix = drawCounterNumber(QString::number(m_counter), rawPix);

    QString base64Image = image2Base64(textPix);
    QJsonObject payload;
    payload.insert("image", base64Image);
    payload.insert("state", 0);
    payload.insert("widget", "com.avermedia.widget.counter");
    m_apiDelegate->sentChangeImage(m_contextId, payload);
}

void WidgetCounter::doKeyUpAction()
{
    if (m_longPressTimer)
    {
        m_isLongPress = false;
    }

    QPixmap rawPix = m_iconList[0];

    QPixmap textPix = drawCounterNumber(QString::number(m_counter), rawPix);

    QString base64Image = image2Base64(textPix);
    QJsonObject payload;
    payload.insert("image", base64Image);
    payload.insert("state", 0);
    payload.insert("widget", "com.avermedia.widget.counter");
    m_apiDelegate->sentChangeImage(m_contextId, payload);
}

void WidgetCounter::doKeyDownAction()
{
    QPixmap rawPix = m_iconList[0];

    QPixmap textPix = drawCounterNumber(QString::number(m_counter), rawPix);

    QString base64Image = image2Base64(textPix.scaled(100,72));
    QJsonObject payload;
    payload.insert("image", base64Image);
    payload.insert("state", 0);
    payload.insert("widget", "com.avermedia.widget.counter");
    m_apiDelegate->sentChangeImage(m_contextId, payload);

    if (m_longPressTimer == Q_NULLPTR)
    {
        m_isLongPress = true;
        m_longPressTimer = new QTimer();
        m_longPressTimer->singleShot(2000, this, [=]()
        {
            if (m_isLongPress)
            {
                m_counter = 0;
            }
            m_longPressTimer->deleteLater();
            m_longPressTimer = Q_NULLPTR;
        });
    }
}

void WidgetCounter::doTriggerAction()
{
    QPixmap rawPix = m_iconList[0];

    QPixmap textPix = drawCounterNumber(QString::number(++m_counter), rawPix);

    QString base64Image = image2Base64(textPix);
    QJsonObject payload;
    payload.insert("image", base64Image);
    payload.insert("state", 0);
    payload.insert("widget", "com.avermedia.widget.counter");
    m_apiDelegate->sentChangeImage(m_contextId, payload);
}

QString WidgetCounter::image2Base64(QPixmap pix)
{
    QImage image = pix.toImage();
    QByteArray imageByteArray;
    QBuffer buffer(&imageByteArray);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "JPG");

    QByteArray base64ByteArray = imageByteArray.toBase64();
    QString base64String = QString::fromLatin1(base64ByteArray);
    buffer.aboutToClose();
    imageByteArray.clear();
    base64ByteArray.clear();
    return base64String;
}

QPixmap WidgetCounter::drawCounterNumber(QString text, QPixmap rawPixmap)
{
    QPainter painter(&rawPixmap);
    painter.setPen(QPen(Qt::white, 8, Qt::SolidLine));
    QFont font;
    font.setFamily("Times New Roman");
    font.setPixelSize(30);
    painter.setFont(font);
    painter.drawText(0, 15, rawPixmap.width(), rawPixmap.height(), Qt::AlignCenter, text);
    painter.end();
    return rawPixmap;
}
