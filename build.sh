#!/bin/bash

# === 設定 ===
BUILD_DIR="build"
EXECUTABLE_NAME="SwitchBotController"

# === Git タグからバージョン取得 ===
VERSION=$(git describe --tags --abbrev=0 2>/dev/null)

if [ -z "$VERSION" ]; then
  echo "[ERROR] Git タグが存在しません。ビルドを中止します。"
  echo "        少なくとも1つのタグ（例: git tag v1.0.0）を作成してください。"
  exit 1
fi

# `v` を除いた純粋なバージョンに整形（例: v1.0.0 → 1.0.0）
VERSION_CLEANED="${VERSION#v}"

TARGET_DIR="target/release/$VERSION_CLEANED"

# === --clean オプション ===
if [ "$1" == "--clean" ]; then
  echo "[BUILD] 成果物ディレクトリを削除: $TARGET_DIR"
  rm -rf "$TARGET_DIR"
  echo "[BUILD] CMakeビルドディレクトリを削除: $BUILD_DIR"
  rm -rf "$BUILD_DIR"
  exit 0
fi

echo "[BUILD] バージョン: $VERSION_CLEANED"
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
