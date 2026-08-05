#pragma once

#include <memory>
#include <unordered_map>
#include "../include/gta/weapon_components.h"

class WeaponComponentLoader
{
public:
    WeaponComponentLoader();
    ~WeaponComponentLoader();

    bool Initialize();
    void Shutdown();

    bool LoadComponent(const char* modelName);
    bool LoadLaserSightComponent(const char* modelName);

    GTA::ExtendedWeaponComponentLaserSightInfo* GetLaserSightComponent(const char* modelName) const;
    GTA::CWeaponComponentLaserSightInfo* GetBaseComponent(const char* modelName) const;

private:
    struct ComponentCache
    {
        std::unique_ptr<GTA::ExtendedWeaponComponentLaserSightInfo> extendedInfo;
        std::unique_ptr<GTA::CWeaponComponentLaserSightInfo> baseInfo;
    };

    std::unordered_map<std::string, ComponentCache> m_componentCache;
    bool m_initialized;

    bool CreateLaserSightInfo(const char* modelName);
    void LogMessage(const char* message, ...);
};
