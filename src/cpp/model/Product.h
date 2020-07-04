//
// Created by alex on 6/20/20.
//

#ifndef OPEN_POS_CLIENT_PRODUCT_H
#define OPEN_POS_CLIENT_PRODUCT_H

#include <QtCore/QString>

namespace openpos {
    class Product {
    public:
        Product();
        void setCode(const QString &code);
        void setName(const QString &name);
        void setCost(double cost);
        void setDescription(const QString &description);
        void setImageFileName(const QString &imageFileName);

    private:
        QString code;
        QString name;
        double cost = 0;
        QString description;
        QString imageFileName;
    };
}// namespace openpos

#endif//OPEN_POS_CLIENT_PRODUCT_H
