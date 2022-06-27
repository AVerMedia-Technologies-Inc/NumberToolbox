QT       += core gui websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    PackageStudioService.cpp \
    WebsocketApiIconDelegate.cpp \
    main.cpp \
    widgets/WidgetCounter.cpp \
    widgets/WidgetRandomGenerator.cpp

HEADERS += \
    PackageStudioService.h \
    WebsocketApiIconDelegate.h \
    model/EventType.h \
    model/WidgetCategory.h \
    widgets/WidgetCounter.h \
    widgets/WidgetRandomGenerator.h

RESOURCES += \
    main.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
