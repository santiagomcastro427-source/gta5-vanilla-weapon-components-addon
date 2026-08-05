#include "WeaponComponentLoader.h"
#include "LaserSightComponent.h"
#include <cstdio>
#include <cstdarg>

WeaponComponentLoader::WeaponComponentLoader()
    : m_initialized(false)
{
}

WeaponComponentLoader::~WeaponComponentLoader()
{
    Shutdown();
}

bool WeaponComponentLoader::Initialize()
{
    LogMessage("[WeaponComponentLoader] Initializing...");
    m_initialized = true;
    return true;
}

void WeaponComponentLoader::Shutdown()
{
    LogMessage("[WeaponComponentLoader] Shutting down...");
    m_componentCache.clear();
    m_initialized = false;
}

bool WeaponComponentLoader::LoadComponent(const char* modelName)
{
    if (!m_initialized)
    {
        LogMessage("[WeaponComponentLoader] Not initialized");
        return false;
    }

    if (!modelName || modelName[0] == '\0')
    {
        LogMessage("[WeaponComponentLoader] Invalid model name");
        return false;
    }

    LogMessage("[WeaponComponentLoader] Loading component for: %s", modelName);

    // Check if already cached
    auto it = m_componentCache.find(modelName);
    if (it != m_componentCache.end())
    {
        LogMessage("[WeaponComponentLoader] Component already cached: %s", modelName);
        return true;
    }

    // Create and load laser sight component
    if (!CreateLaserSightInfo(modelName))
    {
        LogMessage("[WeaponComponentLoader] Failed to create laser sight info for: %s", modelName);
        return false;
    }

    LogMessage("[WeaponComponentLoader] Successfully loaded component: %s", modelName);
    return true;
}

bool WeaponComponentLoader::LoadLaserSightComponent(const char* modelName)
{
    return LoadComponent(modelName);
}

GTA::ExtendedWeaponComponentLaserSightInfo* WeaponComponentLoader::GetLaserSightComponent(const char* modelName) const
{
    auto it = m_componentCache.find(modelName);
    if (it != m_componentCache.end())
    {
        return it->second.extendedInfo.get();
    }
    return nullptr;
}

GTA::CWeaponComponentLaserSightInfo* WeaponComponentLoader::GetBaseComponent(const char* modelName) const
{
    auto it = m_componentCache.find(modelName);
    if (it != m_componentCache.end())
    {
        return it->second.baseInfo.get();
    }
    return nullptr;
}

bool WeaponComponentLoader::CreateLaserSightInfo(const char* modelName)
{
    LogMessage("[WeaponComponentLoader] Creating laser sight info for: %s", modelName);

    ComponentCache cache;

    // Create base laser sight component
    cache.baseInfo = std::make_unique<LaserSightComponent>();
    if (!cache.baseInfo)
    {
        LogMessage("[WeaponComponentLoader] Failed to create base laser sight component");
        return false;
    }

    cache.baseInfo->Initialize();
    cache.baseInfo->SetBeamLength(50.0f);  // Default beam length
    cache.baseInfo->SetBeamColor(1.0f, 0.0f, 0.0f, 1.0f);  // Red laser
    cache.baseInfo->SetEnabled(true);

    // Load FXC and texture from game resources
    cache.baseInfo->LoadFXC("common:\\data\\clothes\\laser\\laserbeam.fxc");
    cache.baseInfo->LoadTexture("common:\\data\\clothes\\laser\\laser_noise.dds");

    // Create extended component
    cache.extendedInfo = std::make_unique<GTA::ExtendedWeaponComponentLaserSightInfo>();
    if (!cache.extendedInfo)
    {
        LogMessage("[WeaponComponentLoader] Failed to create extended laser sight component");
        return false;
    }

    cache.extendedInfo->SetLaserSightInfo(cache.baseInfo.get());
    cache.extendedInfo->SetIsLaserSight(true);
    cache.extendedInfo->SetLaserBeamEffect("common:\\data\\clothes\\laser\\laserbeam.fxc");
    cache.extendedInfo->SetLaserNoiseTexture("common:\\data\\clothes\\laser\\laser_noise.dds");

    // Store in cache
    m_componentCache[modelName] = std::move(cache);

    LogMessage("[WeaponComponentLoader] Successfully created laser sight info for: %s", modelName);
    return true;
}

void WeaponComponentLoader::LogMessage(const char* message, ...)
{
    char buffer[1024];
    va_list args;
    va_start(args, message);
    vsnprintf(buffer, sizeof(buffer), message, args);
    va_end(args);

    OutputDebugStringA(buffer);
    OutputDebugStringA("\n");
}
