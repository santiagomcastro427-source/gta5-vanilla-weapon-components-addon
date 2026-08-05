#include "VanillaWeaponComponentsAddon.h"
#include <cstdio>
#include <cstdarg>
#include <fstream>
#include <sstream>

VanillaWeaponComponentsAddon& VanillaWeaponComponentsAddon::GetInstance()
{
    static VanillaWeaponComponentsAddon instance;
    return instance;
}

VanillaWeaponComponentsAddon::VanillaWeaponComponentsAddon()
    : m_initialized(false)
{
}

VanillaWeaponComponentsAddon::~VanillaWeaponComponentsAddon()
{
    Shutdown();
}

bool VanillaWeaponComponentsAddon::Initialize()
{
    if (m_initialized)
    {
        LogMessage("[VanillaWeaponComponentsAddon] Already initialized");
        return true;
    }

    LogMessage("[VanillaWeaponComponentsAddon] Initializing addon...");

    // Initialize weapon component loader
    m_weaponLoader = std::make_unique<WeaponComponentLoader>();
    if (!m_weaponLoader->Initialize())
    {
        LogMessage("[VanillaWeaponComponentsAddon] Failed to initialize weapon loader");
        return false;
    }

    LogMessage("[VanillaWeaponComponentsAddon] Weapon loader initialized");

    // Load configuration
    if (!LoadConfigFile())
    {
        LogMessage("[VanillaWeaponComponentsAddon] Failed to load configuration");
        return false;
    }

    // Load all weapon components
    if (!LoadAllWeaponComponents())
    {
        LogMessage("[VanillaWeaponComponentsAddon] Failed to load weapon components");
        return false;
    }

    m_initialized = true;
    LogMessage("[VanillaWeaponComponentsAddon] Addon initialized successfully");
    return true;
}

void VanillaWeaponComponentsAddon::Shutdown()
{
    if (!m_initialized)
        return;

    LogMessage("[VanillaWeaponComponentsAddon] Shutting down addon...");

    m_loadedWeapons.clear();
    m_weaponLoader.reset();

    m_initialized = false;
    LogMessage("[VanillaWeaponComponentsAddon] Addon shutdown complete");
}

void VanillaWeaponComponentsAddon::Update()
{
    if (!m_initialized)
        return;

    // Update logic if needed
    // This would be called every frame
}

bool VanillaWeaponComponentsAddon::LoadWeaponComponent(const char* modelName)
{
    if (!m_initialized || !m_weaponLoader)
    {
        LogMessage("[VanillaWeaponComponentsAddon] Addon not initialized");
        return false;
    }

    LogMessage("[VanillaWeaponComponentsAddon] Loading weapon component: %s", modelName);

    return m_weaponLoader->LoadComponent(modelName);
}

bool VanillaWeaponComponentsAddon::LoadAllWeaponComponents()
{
    LogMessage("[VanillaWeaponComponentsAddon] Loading all weapon components...");

    // Load vanilla weapon models with laser sight components
    const char* weaponModels[] = {
        "w_at_pi_flsh_2",
        "w_at_pi_flsh_3",
        "w_at_ar_flsh_3"
    };

    for (const char* model : weaponModels)
    {
        if (!LoadWeaponComponent(model))
        {
            LogMessage("[VanillaWeaponComponentsAddon] Warning: Failed to load %s", model);
        }
    }

    LogMessage("[VanillaWeaponComponentsAddon] Loaded %zu weapon components", m_loadedWeapons.size());
    return true;
}

WeaponComponentLoader* VanillaWeaponComponentsAddon::GetWeaponComponentLoader() const
{
    return m_weaponLoader.get();
}

bool VanillaWeaponComponentsAddon::LoadConfigFile()
{
    const char* configPath = ".\\scripts\\VanillaWeaponComponentsAddon\\weapon_components.ini";

    LogMessage("[VanillaWeaponComponentsAddon] Loading config from: %s", configPath);

    std::ifstream configFile(configPath);
    if (!configFile.is_open())
    {
        LogMessage("[VanillaWeaponComponentsAddon] Warning: Config file not found, using defaults");
        return true;
    }

    std::string line;
    while (std::getline(configFile, line))
    {
        if (line.empty() || line[0] == ';' || line[0] == '#')
            continue;

        // Parse configuration lines
        // Format: KEY=VALUE
        size_t eqPos = line.find('=');
        if (eqPos != std::string::npos)
        {
            std::string key = line.substr(0, eqPos);
            std::string value = line.substr(eqPos + 1);

            LogMessage("[VanillaWeaponComponentsAddon] Config: %s = %s", key.c_str(), value.c_str());
        }
    }

    configFile.close();
    return true;
}

void VanillaWeaponComponentsAddon::LogMessage(const char* message, ...)
{
    char buffer[1024];
    va_list args;
    va_start(args, message);
    vsnprintf(buffer, sizeof(buffer), message, args);
    va_end(args);

    // Write to console/debugger
    OutputDebugStringA(buffer);
    OutputDebugStringA("\n");

    // Optionally write to file
    FILE* logFile = nullptr;
    errno_t err = fopen_s(&logFile, "VanillaWeaponComponentsAddon.log", "a");
    if (err == 0 && logFile)
    {
        fprintf(logFile, "%s\n", buffer);
        fclose(logFile);
    }
}

// DLL Entry Point
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        VanillaWeaponComponentsAddon::GetInstance().Initialize();
        break;
    case DLL_PROCESS_DETACH:
        VanillaWeaponComponentsAddon::GetInstance().Shutdown();
        break;
    }
    return TRUE;
}
