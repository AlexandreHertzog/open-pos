//
// Created by alex on 6/20/20.
//

#include "config/ConfigController.h"
#include "ui/MainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char **argv) {
    Q_INIT_RESOURCE(openposclient);

    openpos::ConfigController::setHighDpiForAndroid();

    QApplication app(argc, argv);
    openpos::ConfigController::setAppData();

    openpos::MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
