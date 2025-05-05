#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>
#include <sys/ioctl.h>
#include <cerrno>
#include <cstring>

#include "VCNL4040Sensor.hpp"

// デリータの実装
class VCNL4040Sensor::FileDescriptorDeleter {
public:
    void operator()(int* fd) const {
        if (*fd >= 0) {
            close(*fd);
        }
        delete fd;
    }
};

VCNL4040Sensor::VCNL4040Sensor(const char *i2c_device)
    : fd(new int(open(i2c_device, O_RDWR)), FileDescriptorDeleter()) {
    if (*fd < 0) {
        perror("Failed to open I2C device");
        throw std::runtime_error("I2C device open error");
    }
}

Brightness VCNL4040Sensor::getBrightness() {
    uint16_t raw_light = readRegister(ALS_DATA);
    
    // デバッグ出力
    std::cout << "Raw ALS: 0x" << std::hex << raw_light 
              << " (" << std::dec << raw_light << ")" << std::endl;
    
    // 0.01 lux/step変換
    Brightness brightness(raw_light * 0.1f);

    return brightness;
}

uint16_t VCNL4040Sensor::SetAlsConfig(uint8_t cmd) {
    return writeRegister(ALS_CONF, cmd, 0x00);
}

uint16_t VCNL4040Sensor::readRegister(uint8_t reg_addr) {
    uint8_t buffer[2];
    struct i2c_msg messages[] = {
      { I2C_ADDRESS, 0, 1, &reg_addr },      /* レジスタアドレスをセット. */
      { I2C_ADDRESS, I2C_M_RD, 2, buffer },  /* dataにlengthバイト読み込む. */
    };
    struct i2c_rdwr_ioctl_data ioctl_data = { messages, 2 };

    /* I2C-Readを行う. */
    if (ioctl(*fd, I2C_RDWR, &ioctl_data) < 0) {
        std::cerr << "i2c_read: failed to ioctl: " << strerror(errno) << std::endl;
        return -1;
    }

    // デバッグ出力
    uint16_t data = (buffer[1] << 8) | buffer[0];
    // std::cout << "Read data: 0x" << std::hex << data << std::endl;

    // LSBとMSBを16ビット値に結合
    return data;
}

uint16_t VCNL4040Sensor::writeRegister(uint8_t reg_addr, uint8_t lsb, uint8_t msb) {
    /* I2C-Write用のバッファを準備する. */
    uint8_t buffer[3];
    
    buffer[0] = reg_addr;  // 1バイト目にレジスタアドレスをセット
    buffer[1] = lsb;       // 2バイト目にLSBをセット
    buffer[2] = msb;       // 3バイト目にMSBをセット

    /* I2C-Writeメッセージを作成する. */
    struct i2c_msg message = { I2C_ADDRESS, 0, 3, buffer };
    struct i2c_rdwr_ioctl_data ioctl_data = { &message, 1 };

    /* I2C-Writeを行う. */
    if (ioctl(*fd, I2C_RDWR, &ioctl_data) < 0) {
        std::cerr << "i2c_write: failed to ioctl: " << strerror(errno) << std::endl;
        return -1;
    }
    return 0;
}