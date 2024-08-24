#pragma once


namespace TSEssential::FarmLandProtect {
enum class ProtectType {
    All,
    OnlyEntity,
    OnlyPlayer,
    NoWork
};
bool Load();
}