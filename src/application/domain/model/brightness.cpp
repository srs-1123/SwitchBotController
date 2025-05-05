#include <stdexcept>
#include <string>
#include <sstream>
#include "brightness.hpp"

namespace domain::model {

/**
 * @brief 明るさオブジェクトを構築する
 * @param value 明るさの値
 */
Brightness::Brightness(const uint8_t value) {
  mValue = value;
}

/**
 * @brief 明るさの値を取得します。
 * @return uint8_t 現在の明るさの値
 */
[[nodiscard]] uint8_t Brightness::getValue() const noexcept {
  return mValue;
}

/**
 * @brief 明るさを設定する
 * @param value 設定する明るさの値 (0-100)
 */
void Brightness::setValue(const uint8_t value) {
  mValue = value;
}

} // namespace domain::model 