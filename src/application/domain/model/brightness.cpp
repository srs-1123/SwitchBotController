#include <stdexcept>
#include <string>
#include <sstream>
#include "brightness.hpp"

namespace domain::model {

/**
 * @brief 明るさオブジェクトを構築する
 * @param value 明るさの値
 */
Brightness::Brightness(const float value) {
  mValue = value;
}

/**
 * @brief 明るさの値を取得します。
 * @return float 現在の明るさの値
 */
[[nodiscard]] float Brightness::getValue() const noexcept {
  return mValue;
}

/**
 * @brief 明るさを設定する
 * @param value 設定する明るさの値 (0-100)
 */
void Brightness::setValue(const float value) {
  mValue = value;
}

} // namespace domain::model 