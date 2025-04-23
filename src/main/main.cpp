#include <iostream>
#include "application/domain/model/brightness.hpp"

using domain::model::Brightness;

int main() {
    Brightness brightness(50);
    std::cout << "Brightness: " << brightness.getValue() << std::endl;
    std::cout << "[SwitchBotController] 起動しました。" << std::endl;
    return 0;
}