#pragma once

/**
 * @brief SwitchbotAPIのクライアントクラス
 * 
 */
class SwitchBotAPIClient {
public:
    SwitchBotAPIClient(std::string token);
    ~SwitchBotAPIClient() = default;
private:
    std::string mToken;
    std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> mCurl;
    void SendCommand(const std::string& deviceUrl, const std::string& command);
};