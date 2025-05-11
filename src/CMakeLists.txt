cmake_minimum_required(VERSION 3.16)

# --- Domain Model ライブラリ ---
add_library(domain_model
    application/domain/model/brightness.cpp
    # 他の domain/model のソースファイルがあればここに追加
)
# --- Domain Model ライブラリ ---
add_library(infrastructure_lib
    infrastructure/sensors/VCNL4040Sensor.cpp
    # 他の infrastructure のソースファイルがあればここに追加
)
# ライブラリのインクルードパスを設定
target_include_directories(domain_model PUBLIC
    # このライブラリを使用する側がヘッダーを見つけられるように PUBLIC にする
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# --- メインターゲット ---
add_executable(SwitchBotController
    main/main.cpp
)

# ライブラリ同士の依存関係を記述
target_link_libraries(infrastructure_lib PRIVATE
    domain_model
)

# メインターゲットが依存するライブラリをリンク
target_link_libraries(SwitchBotController PRIVATE
    domain_model
    infrastructure_lib
)