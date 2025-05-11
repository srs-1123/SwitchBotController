#pragma once

namespace domain::port {

/**
 * @brief LightControllServiceの出力ポート
 * 
 */
class LightControllPort {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual ~LightControllPort() = default;
};

}