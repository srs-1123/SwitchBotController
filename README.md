# SwitchBotController

照度センサーに基づき、電気のON/OFFを自動制御するC++アプリケーション。  

---

## 概要
- Raspberry Piを使用し、照度センサーからの入力に応じてSwitchBot経由で照明制御を行う。

---

## 環境構築
docker build -t switchbot-dev .

## ビルド方法
./build.sh