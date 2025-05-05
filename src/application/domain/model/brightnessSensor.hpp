#pragma once


#include "brightness.hpp"

namespace domain::model {

/**
 * @brief 明るさセンサーの基底クラス
 * 
 */
class BrightnessSensor {
public:
    virtual Brightness getBrightness() = 0;
    virtual ~BrightnessSensor() = default;
};

}
