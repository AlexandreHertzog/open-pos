//
// Created by alex on 6/20/20.
//

#include "MainWindow.h"

#include <QtWidgets>

openpos::MainWindow::MainWindow() {
    editProductDialog = new EditProductDialog(this);

    auto *mainWidget = new QWidget(this);

    auto *mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(buildMenuBar());
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
    setWindowTitle(tr("open-pos"));

    readSettings();
    initStatusBar();
}

QMenuBar *openpos::MainWindow::buildMenuBar() {
    auto *menuBar = new QMenuBar;
    menuBar->addMenu(buildFileMenu());
    menuBar->addMenu(buildProductMenu());
    menuBar->addMenu(buildHelpMenu());
    return menuBar;
}

QMenu *openpos::MainWindow::buildFileMenu() {
    auto menu = new QMenu(tr("&Arquivo"), this);
    QAction *exitAction = menu->addAction(tr("&Sair"));
    exitAction->setStatusTip(tr("Encerra o App de Pagamento"));
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);

    return menu;
}

QMenu *openpos::MainWindow::buildProductMenu() {
    auto menu = new QMenu(tr("&Produtos"), this);
    QAction *newProduct = menu->addAction(tr("&Novo produto"));
    newProduct->setStatusTip(tr("Abre a tela de adição de novo produto"));
    connect(newProduct, &QAction::triggered, editProductDialog, &QDialog::exec);
    return menu;
}

QMenu *openpos::MainWindow::buildHelpMenu() {
    auto menu = new QMenu(tr("A&juda"), this);
    QAction *aboutAction = menu->addAction(tr("S&obre"));
    aboutAction->setStatusTip(tr("Mostra as informações da aplicação"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
    return menu;
}

void openpos::MainWindow::about() {
    QMessageBox::about(this, tr("open-pos"), tr("Aplicação de pagamento, texto dummy"));
}

void openpos::MainWindow::initStatusBar() {
    statusBar()->showMessage("Pronto");
}

void openpos::MainWindow::readSettings() {
    QSettings settings(QCoreApplication::organizationDomain(), QCoreApplication::applicationName());
    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty()) {
        const QRect availableGeometry = screen()->availableGeometry();
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }
}

void openpos::MainWindow::writeSettings() {
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
}

void openpos::MainWindow::closeEvent(QCloseEvent *event) {
    writeSettings();
    event->accept();
}