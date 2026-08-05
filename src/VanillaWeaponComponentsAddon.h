#pragma once

#include <windows.h>
#include <memory>
#include <vector>
#include "WeaponComponentLoader.h"
#include "../include/gta/weapon_components.h"

class VanillaWeaponComponentsAddon
{
public:
    static VanillaWeaponComponentsAddon& GetInstance();

    bool Initialize();
    void Shutdown();
    void Update();

    bool LoadWeaponComponent(const char* modelName);
    bool LoadAllWeaponComponents();

    WeaponComponentLoader* GetWeaponComponentLoader() const;

private:
    VanillaWeaponComponentsAddon();
    ~VanillaWeaponComponentsAddon();

    VanillaWeaponComponentsAddon(const VanillaWeaponComponentsAddon&) = delete;
    VanillaWeaponComponentsAddon& operator=(const VanillaWeaponComponentsAddon&) = delete;

    bool m_initialized;
    std::unique_ptr<WeaponComponentLoader> m_weaponLoader;
    std::vector<GTA::WeaponModel> m_loadedWeapons;

    void LogMessage(const char* message, ...);
    bool LoadConfigFile();
};
