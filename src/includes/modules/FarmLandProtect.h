#pragma once


namespace TSEssential::FarmLandProtect {
enum class ProtectType {
    OnlyEntity,
    OnlyPlayer,
    All,
    NoWork
};
bool Load();
}