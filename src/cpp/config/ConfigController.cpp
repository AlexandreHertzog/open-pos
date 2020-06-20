//
// Created by alex on 6/20/20.
//

#include "ConfigController.h"
#include <QCoreApplication>
#include <config.h>

void openpos::ConfigController::setHighDpiForAndroid() {
#if defined(Q_OS_ANDROID)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
}

void openpos::ConfigController::setAppData() {
    QCoreApplication::setOrganizationName("Alexandre Hertzog");
    QCoreApplication::setApplicationName(PROJECT_DESCRIPTION);
    QCoreApplication::setApplicationVersion(PROJECT_VERSION);
}
