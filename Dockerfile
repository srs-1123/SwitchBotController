# ベースイメージにUbuntuの最新LTS版を使用
FROM ubuntu:22.04

# タイムゾーンの設定（ビルド時の対話式プロンプトを回避）
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Asia/Tokyo

# 必要なパッケージのインストール
RUN apt update && apt install -y \
    build-essential \
    cmake \
    git \
    libcurl4-openssl-dev \
    nlohmann-json3-dev \
    libspdlog-dev \
    libi2c-dev \
    pkg-config \
    libgtest-dev \
    && apt clean \
    && rm -rf /var/lib/apt/lists/*

# gtestのビルドとインストール
RUN cd /usr/src/gtest && cmake . && make && cp lib/*.a /usr/lib

# 作業ディレクトリの設定
WORKDIR /app

# ソースコードのコピー
# COPY . .
