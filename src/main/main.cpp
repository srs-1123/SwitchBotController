#include <iostream>
#include <unistd.h>
#include "application/domain/model/brightness.hpp"
#include "infrastructure/sensors/VCNL4040Sensor.hpp"

using domain::model::Brightness;

int main() {
    Brightness brightness(50);
    std::cout << "Brightness: " << brightness.getValue() << std::endl;
    std::cout << "[SwitchBotController] 起動しました。" << std::endl;

#ifdef GET_BRIGHTNESS
    VCNL4040Sensor brightnessSensor("/dev/i2c-1"); // 使用するI2Cバスに応じて変更
    brightnessSensor.AlsActivate();
    sleep(1);

    while (true) {
        Brightness brightness = brightnessSensor.getBrightness();
        std::cout << "Ambient Light: " << std::dec << brightness.getValue() << " lux" << std::endl;
        sleep(1);
    }
#endif
    return 0;
}