#pragma once

#include "mc/world/actor/player/Player.h"

#include <string>

namespace TLModule {

class Announcement {
private:
    // 标题
    std::string mTitle;
    // 内容
    std::string mContent;

public:
    Announcement(std::string& title, std::string& content) : mTitle(title), mContent(content){};

    std::string getTitle();

    std::string getContent();

    void showAnnouncement(Player& player);
};
} // namespace TLModule