//
// Created by alex on 6/20/20.
//

#include "EditProductDialog.h"

#include <QtWidgets>

class openpos::MoneySpinBox : public QDoubleSpinBox {
public:
    explicit MoneySpinBox(QWidget *parent = nullptr) : QDoubleSpinBox(parent) {
        setAlignment(Qt::AlignRight);
        setMaximum(9999999999.99);
        setMinimum(0.01);
        setSingleStep(0.1);
        setValue(1.0);
    }

    QString textFromValue(double val) const override {
        return this->locale().toCurrencyString(val);
    }
};

openpos::EditProductDialog::EditProductDialog(QWidget *parent) : QDialog(parent) {
    connect(this, &EditProductDialog::doneInputting, this, &EditProductDialog::collectProductInputs);

    productCodeEdit = new QLineEdit(this);
    productCodeEdit->setPlaceholderText(tr("Código do produto"));
    connect(productCodeEdit, &QLineEdit::textChanged, this, &EditProductDialog::colorCodeInput);

    productNameEdit = new QLineEdit(this);
    productNameEdit->setPlaceholderText(tr("Nome do produto"));
    connect(productNameEdit, &QLineEdit::textChanged, this, &EditProductDialog::colorNameInput);

    productCostEdit = new MoneySpinBox(this);
    productDescriptionEdit = new QTextEdit(this);
    productImageEdit = new QLineEdit(this);
    connect(productImageEdit, &QLineEdit::textChanged, this, &EditProductDialog::colorImageInput);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    auto mainLayout = new QVBoxLayout;

    auto topCaptures = new QGridLayout;

    buildProductCodeLayout(topCaptures);
    buildProductNameLayout(topCaptures);
    buildProductCostLayout(topCaptures);

    mainLayout->addLayout(topCaptures);

    buildProductImageLayout(mainLayout);
    buildProductDescriptionLayout(mainLayout);
    buildOkCancelButtons(mainLayout);

    setLayout(mainLayout);
}

void openpos::EditProductDialog::buildProductCodeLayout(QGridLayout *layout) {
    layout->addWidget(new QLabel(tr("Código do produto: ")), 0, 0);
    layout->addWidget(productCodeEdit, 0, 1);
}

void openpos::EditProductDialog::buildProductNameLayout(QGridLayout *layout) {
    layout->addWidget(new QLabel(tr("Nome do produto: ")), 1, 0);
    layout->addWidget(productNameEdit, 1, 1);
}

void openpos::EditProductDialog::buildProductCostLayout(QGridLayout *layout) {
    layout->addWidget(new QLabel(tr("Valor do produto: ")), 2, 0);
    layout->addWidget(productCostEdit, 2, 1);
}

void openpos::EditProductDialog::buildProductImageLayout(QVBoxLayout *layout) {
    auto imageLayout = new QHBoxLayout;
    imageLayout->addWidget(new QLabel(tr("Imagem do produto: ")));

    auto imagePathSelector = new QPushButton(tr("Abrir..."));

    auto imagePathSelectorDialog = new QFileDialog(this);
    imagePathSelectorDialog->setWindowModality(Qt::WindowModal);
    imagePathSelectorDialog->setAcceptMode(QFileDialog::AcceptOpen);
    imagePathSelectorDialog->setFilter(QDir::Filter::Files);

    connect(imagePathSelector, &QPushButton::clicked, imagePathSelectorDialog, &QFileDialog::exec);
    connect(imagePathSelectorDialog, &QFileDialog::fileSelected, productImageEdit, &QLineEdit::setText);

    imageLayout->addWidget(productImageEdit);
    imageLayout->addWidget(imagePathSelector);

    layout->addLayout(imageLayout);
}


void openpos::EditProductDialog::buildProductDescriptionLayout(QVBoxLayout *layout) {
    layout->addWidget(new QLabel(tr("Descrição do produto: ")));
    layout->addWidget(productDescriptionEdit);
}

void openpos::EditProductDialog::buildOkCancelButtons(QVBoxLayout *layout) {
    layout->addWidget(buttonBox);
}

void openpos::EditProductDialog::done(int code) {
    if (code != QDialog::Accepted) {
        QDialog::done(code);
        return;
    }

    bool accept = true;
    if (productCodeEdit->text().isEmpty()) {
        QMessageBox::warning(this, tr("open-pos"), tr("O código do produto não pode ser vazio"), QMessageBox::Ok);
        accept = false;
    }
    if (productNameEdit->text().isEmpty()) {
        QMessageBox::warning(this, tr("open-pos"), tr("O nome do produto não pode ser vazio"), QMessageBox::Ok);
        accept = false;
    }
    if (!productImageEdit->text().isEmpty() && !isImageInputValid()) {
        QMessageBox::warning(this, tr("open-pos"), tr("O arquivo de imagem especificada não existe"), QMessageBox::Ok);
        accept = false;
    }
    if (accept) {
        emit doneInputting();
        QDialog::done(code);
    }
}

void openpos::EditProductDialog::colorCodeInput() {
    emptyInputColorizer(productCodeEdit);
}

void openpos::EditProductDialog::colorNameInput() {
    emptyInputColorizer(productNameEdit);
}

void openpos::EditProductDialog::colorImageInput() {
    QPalette palette = productImageEdit->palette();
    if (productImageEdit->text().isEmpty()) {
        palette.setColor(QPalette::Background, Qt::white);
    } else {
        if (isImageInputValid()) {
            palette.setColor(QPalette::Background, Qt::white);
        } else {
            palette.setColor(QPalette::Background, Qt::red);
        }
    }
    productImageEdit->setPalette(palette);
}

void openpos::EditProductDialog::emptyInputColorizer(QLineEdit *edit) {
    QPalette palette = edit->palette();
    if (!edit->text().isEmpty()) {
        palette.setColor(QPalette::Background, Qt::white);
    } else {
        palette.setColor(QPalette::Background, Qt::red);
    }
    edit->setPalette(palette);
}

bool openpos::EditProductDialog::isImageInputValid() {
    QFile imageFile(productImageEdit->text());
    return imageFile.exists();
}

void openpos::EditProductDialog::collectProductInputs() {
    product.setCode(productCodeEdit->text());
    product.setName(productNameEdit->text());
    product.setCost(productCostEdit->value());
    product.setImageFileName(productImageEdit->text());
    product.setDescription(productDescriptionEdit->toPlainText());
}
