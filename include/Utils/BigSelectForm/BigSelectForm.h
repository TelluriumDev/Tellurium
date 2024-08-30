#pragma once
#include <functional>
#include <string>
#include <vector>

#include <ll/api/form/CustomForm.h>

class Player;
class BigSelectForm { // 可用头文件 cpp不可用
private:
    std::string                                                    mTitle;
    std::vector<std::string>                                       mButtons;
    std::vector<std::string>                                       mSelectedButtons{};
    std::function<void(std::vector<std::string>& selectedButtons)> mCallback;

public:
    BigSelectForm(const std::string& title, const std::vector<std::string>& buttons);

    inline void setCallback(const std::function<void(std::vector<std::string>& selectedButtons)>& callback);
    void        sendToPlayer(Player& pl);

private:
    void makeForm(ll::form::CustomForm& form);
};