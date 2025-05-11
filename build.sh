#!/bin/bash

# === docker環境でなければdocker runで自分自身を実行 ===
if [ -z "$IN_DOCKER" ]; then
  echo "[BUILD] Entering Docker container for build environment..."
  docker run --rm -e IN_DOCKER=1 -v "$(pwd)":/app -w /app switchbot-dev bash "$0" "$@"
  exit $?
fi

# === 設定 ===
BUILD_DIR="build"
EXECUTABLE_NAME="SwitchBotController"

# === versionファイルからバージョン取得 ===
if [ ! -f "./version" ]; then
  echo "[ERROR] versionファイルが存在しません。ビルドを中止します。"
  exit 1
fi

VERSION=$(cat ./version | tr -d ' \n')

if [ -z "$VERSION" ]; then
  echo "[ERROR] versionファイルが空です。バージョンを記載してください。"
  exit 1
fi

TARGET_DIR="target/release/$VERSION"

# === --clean オプション ===
if [ "$1" == "--clean" ]; then
  echo "[BUILD] 成果物ディレクトリを削除: $TARGET_DIR"
  rm -rf "$TARGET_DIR"
  echo "[BUILD] CMakeビルドディレクトリを削除: $BUILD_DIR"
  rm -rf "$BUILD_DIR"
  exit 0
fi

echo "[BUILD] バージョン: $VERSION"
echo "[BUILD] 成果物出力先: $TARGET_DIR"

# === 成果物ディレクトリは毎回クリーン ===
echo "[BUILD] 成果物ディレクトリを削除: $TARGET_DIR"
rm -rf "$TARGET_DIR"
echo "[BUILD] CMakeビルドディレクトリを削除: $BUILD_DIR"
rm -rf "$BUILD_DIR"

# === ビルド処理 ===
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR" || exit 1

cmake .. -DCMAKE_BUILD_TYPE=Release || { echo "[ERROR] CMake失敗"; exit 1; }
make -j$(nproc) || { echo "[ERROR] ビルド失敗"; exit 1; }

# === 成果物コピー ===
cd ..
mkdir -p "$TARGET_DIR"
mv "$BUILD_DIR/src/$EXECUTABLE_NAME" "$TARGET_DIR/"

echo "[BUILD] 完了：$TARGET_DIR/$EXECUTABLE_NAME"
