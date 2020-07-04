//
// Created by alex on 6/20/20.
//

#include "Product.h"

openpos::Product::Product() = default;

void openpos::Product::setCode(const QString &code) {
    this->code = code;
}

void openpos::Product::setName(const QString &name) {
    this->name = name;
}

void openpos::Product::setCost(double cost) {
    this->cost = cost;
}

void openpos::Product::setDescription(const QString &description) {
    this->description = description;
}

void openpos::Product::setImageFileName(const QString &imageFileName) {
    this->imageFileName = imageFileName;
}
