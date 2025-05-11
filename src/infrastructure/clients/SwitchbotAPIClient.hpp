#pragma once

/**
 * @brief SwitchbotAPIのクライアントクラス
 * 
 */
class SwitchBotAPIClient {
public:
    SwitchBotAPIClient();
    ~SwitchBotAPIClient() = default;
private:
    void SendCommand(const std::string& deviceUrl, const std::string& command);
};