//
// Created by alex on 6/20/20.
//

#ifndef OPEN_POS_CLIENT_EDITPRODUCTDIALOG_H
#define OPEN_POS_CLIENT_EDITPRODUCTDIALOG_H

#include "../model/Product.h"
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>

namespace openpos {
    class MoneySpinBox;

    class EditProductDialog : public QDialog {
        Q_OBJECT

    public:
        explicit EditProductDialog(QWidget *parent);

    public Q_SLOTS:
        void done(int code) override;

    private slots:
        void colorCodeInput();
        void colorNameInput();
        void colorImageInput();
        void collectProductInputs();

    signals:
        void doneInputting();

    private:
        void buildProductCodeLayout(QGridLayout *layout);
        void buildProductNameLayout(QGridLayout *layout);
        void buildProductCostLayout(QGridLayout *layout);
        void buildProductDescriptionLayout(QVBoxLayout *layout);
        void buildProductImageLayout(QVBoxLayout *layout);
        void buildOkCancelButtons(QVBoxLayout *layout);
        bool isImageInputValid();

        static void emptyInputColorizer(QLineEdit *);

        QLineEdit *productCodeEdit;
        QLineEdit *productNameEdit;
        MoneySpinBox *productCostEdit;
        QTextEdit *productDescriptionEdit;
        QLineEdit *productImageEdit;
        QDialogButtonBox *buttonBox;

        Product product;
    };
}// namespace openpos

#endif//OPEN_POS_CLIENT_EDITPRODUCTDIALOG_H
