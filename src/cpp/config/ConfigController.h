//
// Created by alex on 6/20/20.
//

#ifndef OPEN_POS_CLIENT_CONFIGCONTROLLER_H
#define OPEN_POS_CLIENT_CONFIGCONTROLLER_H

namespace openpos {
    class ConfigController {
    public:
        static void setHighDpiForAndroid();
        static void setAppData();
    };
}// namespace openpos

#endif//OPEN_POS_CLIENT_CONFIGCONTROLLER_H
