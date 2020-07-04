//
// Created by alex on 6/20/20.
//

#ifndef OPEN_POS_CLIENT_MAINWINDOW_H
#define OPEN_POS_CLIENT_MAINWINDOW_H

#include "EditProductDialog.h"
#include <QtWidgets/QMainWindow>

namespace openpos {
    class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        MainWindow();

    protected:
        void closeEvent(QCloseEvent *event) override;

    private slots:
        void about();

    private:
        QMenuBar *buildMenuBar();
        QMenu *buildFileMenu();
        QMenu *buildProductMenu();
        QMenu *buildHelpMenu();
        void initStatusBar();
        void readSettings();
        void writeSettings();

        EditProductDialog *editProductDialog;
    };
}// namespace openpos

#endif//OPEN_POS_CLIENT_MAINWINDOW_H
