#include <ll/api/event/Cancellable.h>
#include <ll/api/event/Event.h>

#include <mc/world/actor/player/Player.h>


namespace TSETEvent::inline TPAEvent {
class TPARequestEvent final : public ll::event::Cancellable<ll::event::Event> {
private:
    // 请求发送者
    Player* mSender;
    // 请求目标
    Player* mTarget;

public:
    constexpr explicit TPARequestEvent(Player* sender, Player* target)
    : Cancellable(),
      mSender(sender),
      mTarget(target) {}

    // 获取请求对象
    Player& getSender();
    // 获取接收者
    Player& getTarget();
};
} // namespace TSETEvent::inline TPAEvent
