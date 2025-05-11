#pragma once

#include <optional>
#include <memory>
#include "../../application/domain/model/brightness.hpp"
#include "../../application/domain/model/brightnessSensor.hpp"

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
    bool AlsActivate();

private:
    class FileDescriptorDeleter{
    public:
        void operator()(int* fd) const {
        if (*fd >= 0) {
            close(*fd);
        }
        delete fd;
        }
    };
    std::unique_ptr<int, FileDescriptorDeleter> fd;

    static constexpr uint8_t ALS_CONF = 0x00;
    static constexpr uint8_t I2C_ADDRESS = 0x60;
    static constexpr uint8_t DEVICE_ID = 0x0C;
    static constexpr uint8_t ALS_DATA = 0x09;

    std::optional<uint16_t> readRegister(uint8_t reg_addr);
    bool writeRegister(uint8_t reg_addr, uint8_t lsb, uint8_t msb);
};