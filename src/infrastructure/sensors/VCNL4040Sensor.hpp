#pragma once

#include <memory>
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
    ~VCNL4040Sensor() = default;

    Brightness getBrightness() override;
    uint16_t SetALSConfig(uint8_t cmd);

private:
#if 0
    int fd;
#else
    class FileDescriptorDeleter;
    std::unique_ptr<int, FileDescriptorDeleter> fd;
#endif

    static constexpr uint8_t ALS_CONF = 0x00;
    static constexpr uint8_t I2C_ADDRESS = 0x60;
    static constexpr uint8_t DEVICE_ID = 0x0C;
    static constexpr uint8_t ALS_DATA = 0x09;

    uint16_t readRegister(uint8_t reg_addr);
    uint16_t writeRegister(uint8_t reg_addr, uint8_t lsb, uint8_t msb);
};