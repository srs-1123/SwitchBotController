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
     * @param value 設定する明るさの値
     */
    explicit Brightness(float value);

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
     * @return float 現在の明るさの値
     */
    [[nodiscard]] float getValue() const noexcept;

    /**
     * @brief 明るさの値を設定します。
     * @param value 設定する明るさの値
     */
    void setValue(float value);

private:
    /**
     * @brief 明るさの値
     */
    float mValue;

    };

} // namespace domain::model 