#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>

namespace domain::model {

/**
 * @brief 明るさを表現するクラス
 */
class Brightness {
public:
    /**
     * @brief デフォルトコンストラクタ
     * @details 明るさを初期化
     */
    Brightness() noexcept;

    /**
     * @brief 値を指定するコンストラクタ
     * @param value 設定する明るさの値 (kMinBrightness <= value <= kMaxBrightness)
     * @throw std::out_of_range 指定された値が範囲外の場合
     */
    explicit Brightness(uint8_t value);

    /**
     * @brief デストラクタ
     */
    virtual ~Brightness() = default;

    // コピーコンストラクタ、コピー代入演算子をデフォルトで許可
    Brightness(const Brightness&) = default;
    Brightness& operator=(const Brightness&) = default;

    // ムーブコンストラクタ、ムーブ代入演算子をデフォルトで許可
    Brightness(Brightness&&) noexcept = default;
    Brightness& operator=(Brightness&&) noexcept = default;

    /**
     * @brief 明るさの値を取得します。
     * @return uint8_t 現在の明るさの値
     */
    [[nodiscard]] uint8_t getValue() const noexcept;

    /**
     * @brief 明るさの値を設定します。
     * @param value 設定する明るさの値
     */
    void setValue(uint8_t value);

private:
    /**
     * @brief 明るさの値
     */
    uint8_t mValue;

    };

} // namespace domain::model 