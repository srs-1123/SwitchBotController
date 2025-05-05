#pragma once

#include "brightness.hpp"
#include "brightnessSensor.hpp"

using domain::model::Brightness;
using domain::model::BrightnessSensor;

/**
 * @brief VCNL4040を用いたセンサー
 * 
 */
class VCNL4040Sensor: public BrightnessSensor {
public:
    VCNL4040Sensor(const char *i2c_device);
    ~VCNL4040Sensor();

    Brightness getBrightness() override;

private:
    int fd;
    uint16_t SetALSConfig(uint8_t cmd);
    uint16_t readRegister(uint8_t reg_addr);
    uint16_t writeRegister(uint8_t reg_addr, uint8_t lsb, uint8_t msb);
};