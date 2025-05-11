#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <memory>

#include "SwitchbotAPIClient.hpp"

void SwitchBotAPIClient::SendCommand(const std::string& deviceUrl, const std::string& command) {
    // JSONリクエストボディの作成
    nlohmann::json requestBody = {
        {"command", command},
        {"parameter", "default"},
        {"commandType", "command"}
    };

    // レスポンス用のバッファ
    std::string responseBuffer;
    
    // ヘッダーの設定
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, ("Authorization: " + mToken).c_str());
    headers = curl_slist_append(headers, "Content-Type: application/json");

    // CURLの設定
    curl_easy_setopt(mCurl.get(), CURLOPT_URL, deviceUrl.c_str());
    curl_easy_setopt(mCurl.get(), CURLOPT_POST, 1L);
    curl_easy_setopt(mCurl.get(), CURLOPT_POSTFIELDS, requestBody.dump().c_str());
    curl_easy_setopt(mCurl.get(), CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(mCurl.get(), CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(mCurl.get(), CURLOPT_WRITEDATA, &responseBuffer);

    // リクエストの実行
    CURLcode res = curl_easy_perform(mCurl.get());
    
    // ヘッダーの解放
    curl_slist_free_all(headers);

    // エラーチェック
    if (res != CURLE_OK) {
        throw std::runtime_error(
            std::string("Failed to send command to SwitchBot API: ") + 
            curl_easy_strerror(res)
        );
    }

    // レスポンスの処理
    long httpCode = 0;
    curl_easy_getinfo(mCurl.get(), CURLINFO_RESPONSE_CODE, &httpCode);
    
    if (httpCode != 200) {
        throw std::runtime_error(
            "SwitchBot API returned error code: " + std::to_string(httpCode) +
            " Response: " + responseBuffer
        );
    }
}
