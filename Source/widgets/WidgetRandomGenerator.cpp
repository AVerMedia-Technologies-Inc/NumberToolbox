#include "WidgetRandomGenerator.h"
#include "qfont.h"
#include "qpixmap.h"
#include "QPainter"
#include "QRandomGenerator"

WidgetRandomGenerator::WidgetRandomGenerator(WebsocketApiIconDelegate *apiDelegate, QString context, QObject *parent)
    : QObject{parent}
    , m_apiDelegate(apiDelegate)
    , m_contextId(context)
{
    m_iconList << QPixmap(":/images/mainpage_btn_tool_random_number_bg.svg");
}

WidgetRandomGenerator::~WidgetRandomGenerator()
{
    m_contextId = "";
}

void WidgetRandomGenerator::doInitAction()
{
    QPixmap rawPix = m_iconList[0];

    QPixmap textPix = drawNumberText("?", rawPix);

    QString base64Image = image2Base64(textPix);
    QJsonObject payload;
    payload.insert("image", base64Image);
    payload.insert("state", 0);
    payload.insert("widget", "com.avermedia.widget.random.generator");
    m_apiDelegate->sentChangeImage(m_contextId, payload);
}

void WidgetRandomGenerator::doKeyUpAction()
{
    QPixmap rawPix = m_iconList[0];

    QPixmap textPix = drawNumberText(QString::number(m_randomNumber), rawPix);

    QString base64Image = image2Base64(textPix);
    QJsonObject payload;
    payload.insert("image", base64Image);
    payload.insert("state", 0);
    payload.insert("widget", "com.avermedia.widget.random.generator");
    m_apiDelegate->sentChangeImage(m_contextId, payload);
}

void WidgetRandomGenerator::doKeyDownAction()
{
    QPixmap rawPix = m_iconList[0];

    QPixmap textPix = drawNumberText(QString::number(m_randomNumber), rawPix);

    QString base64Image = image2Base64(textPix.scaled(100,72));
    QJsonObject payload;
    payload.insert("image", base64Image);
    payload.insert("state", 0);
    payload.insert("widget", "com.avermedia.widget.random.generator");
    m_apiDelegate->sentChangeImage(m_contextId, payload);
}

void WidgetRandomGenerator::doTriggerAction()
{
    if (m_randomGeneratorTimer == Q_NULLPTR)
    {
        m_randomGeneratorTimer = new QTimer();
        connect(m_randomGeneratorTimer, SIGNAL(timeout()) ,this, SLOT(onRandomGeneratorNumber()));
        m_randomGeneratorTimer->start(50);
        m_randomCounter = 0;
    }
}

void WidgetRandomGenerator::doPropertyInitial()
{
	// Init Min Value
    QJsonObject minPayload;
    minPayload.insert("action", "set_number");

    QJsonObject minNumberJson;
    minNumberJson.insert("id", "number_1_name");
    minNumberJson.insert("name", "Min");
    minPayload.insert("label_name", minNumberJson);

    QJsonObject minValueJson;
    minValueJson.insert("id", "number_1");
    minPayload.insert("number", minValueJson);

    minPayload.insert("default_value", m_randomMin);
    m_apiDelegate->sentSendToPropertyView("com.avermedia.widget.random.generator", m_contextId, minPayload);

	// Init Max Value
    QJsonObject maxPayload;
    maxPayload.insert("action", "set_number");

    QJsonObject maxNumberJson;
    maxNumberJson.insert("id", "number_2_name");
    maxNumberJson.insert("name", "Max");
    maxPayload.insert("label_name", maxNumberJson);

    QJsonObject maxValueJson;
    maxValueJson.insert("id", "number_2");
    maxPayload.insert("number", maxValueJson);

    maxPayload.insert("default_value", m_randomMax);

    m_apiDelegate->sentSendToPropertyView("com.avermedia.widget.random.generator", m_contextId, maxPayload);
}

void WidgetRandomGenerator::updateRandomNumberRange(int mix, int max)
{
    m_randomMin = mix;
    m_randomMax = max;
}

void WidgetRandomGenerator::onRandomGeneratorNumber()
{
    m_randomCounter++;

    if (m_randomCounter < 50)
    {
        QPixmap rawPix = m_iconList[0];

        m_randomNumber = QRandomGenerator::global()->bounded(m_randomMin, m_randomMax + 1);
        QPixmap textPix = drawNumberText(QString::number(m_randomNumber), rawPix);

        QString base64Image = image2Base64(textPix);
        QJsonObject payload;
        payload.insert("image", base64Image);
        payload.insert("state", 0);
        payload.insert("widget", "com.avermedia.widget.random.generator");
        m_apiDelegate->sentChangeImage(m_contextId, payload);
    }
    else
    {
        if (m_randomGeneratorTimer)
        {
            m_randomGeneratorTimer->stop();
            m_randomGeneratorTimer->deleteLater();
            m_randomGeneratorTimer = Q_NULLPTR;
        }
    }
}

QString WidgetRandomGenerator::image2Base64(QPixmap pix)
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

QPixmap WidgetRandomGenerator::drawNumberText(QString text, QPixmap rawPixmap)
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
