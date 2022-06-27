#pragma once
#include "QString"

namespace PluginEventReceived {
const static QString kDidReceiveWidgetSettings = "didReceiveWidgetSettings";
const static QString kDidReceivePackageSettings = "didReceivePackageSettings";
const static QString kKeyDown = "keyDown";
const static QString kKeyUp = "keyUp";
const static QString kWidgetTriggered = "widgetTriggered";
const static QString kWidgetWillAppear = "widgetWillAppear";
const static QString kWidgetWillDisappear = "widgetWillDisappear";
const static QString kPropertyViewDidAppear = "propertyViewDidAppear";
const static QString kPropertyViewDidDisappear = "propertyViewDidDisappear";
const static QString kSendToPackage = "sendToPackage";
const static QString kSendToPropertyView = "sendToPropertyView";
};

namespace PluginEventSent {
const static QString kSetWidgetSettings = "setWidgetSettings";
const static QString kGetWidgetSettings = "getWidgetSettings";
const static QString kSetPackageSettings = "setPackageSettings";
const static QString kGetPackageSettings = "getPackageSettings";
const static QString kSendLog = "sendLog";
const static QString kChangeTitle = "changeTitle";
const static QString kChangeImage = "changeImage";
const static QString kChangeState = "changeState";
const static QString kSendToPropertyView = "sendToPropertyView";
const static QString kSendToPackage = "sendToPackage";
};
