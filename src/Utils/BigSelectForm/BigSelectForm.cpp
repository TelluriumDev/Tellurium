#include "Utils/BigSelectForm/BigSelectForm.h"

#include <mc/world/actor/player/Player.h>

BigSelectForm::BigSelectForm(const std::string& title, const std::vector<std::string>& buttons)
: mTitle(title),
  mButtons(buttons) {}

inline void BigSelectForm::setCallback(const std::function<void(std::vector<std::string>& selectedButtons)>& callback){
    mCallback = callback;
}

void BigSelectForm::sendToPlayer(Player&){
    // pl.send
}
