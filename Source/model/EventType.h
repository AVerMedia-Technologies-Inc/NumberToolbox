#pragma once
#include "QString"

namespace PluginEventReceived {
const static QString kDidReceiveWidgetSettings = "didReceiveWidgetSettings";
const static QString kDidReceivePackageSettings = "didReceivePackageSettings";
const static QString kActionDown = "actionDown";
const static QString kActionUp = "actionUp";
const static QString kActionTriggered = "actionTriggered";
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
