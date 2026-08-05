#include "LaserSightComponent.h"
#include <cstdio>

LaserSightComponent::LaserSightComponent()
    : GTA::CWeaponComponentLaserSightInfo()
    , m_beamWidth(2.0f)
{
}

LaserSightComponent::~LaserSightComponent()
{
    Release();
}

void LaserSightComponent::Initialize()
{
    // Initialize laser sight component
    // Set default values
    SetBeamLength(50.0f);
    SetBeamColor(1.0f, 0.0f, 0.0f, 1.0f);
    SetBeamWidth(2.0f);
    SetEnabled(true);

    OutputDebugStringA("[LaserSightComponent] Initialized\n");
}

void LaserSightComponent::Release()
{
    // Release resources
    OutputDebugStringA("[LaserSightComponent] Released\n");
}

bool LaserSightComponent::LoadFXC(const char* path)
{
    if (!path || path[0] == '\0')
    {
        OutputDebugStringA("[LaserSightComponent] Invalid FXC path\n");
        return false;
    }

    // Load FXC shader from file
    FILE* file = nullptr;
    errno_t err = fopen_s(&file, path, "rb");
    if (err != 0 || !file)
    {
        OutputDebugStringA("[LaserSightComponent] Failed to open FXC file: ");
        OutputDebugStringA(path);
        OutputDebugStringA("\n");
        return false;
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (fileSize == 0)
    {
        OutputDebugStringA("[LaserSightComponent] FXC file is empty\n");
        fclose(file);
        return false;
    }

    // Read file into buffer
    void* buffer = new char[fileSize];
    if (!buffer)
    {
        OutputDebugStringA("[LaserSightComponent] Failed to allocate memory for FXC\n");
        fclose(file);
        return false;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, file);
    fclose(file);

    if (bytesRead != fileSize)
    {
        OutputDebugStringA("[LaserSightComponent] Failed to read complete FXC file\n");
        delete[] static_cast<char*>(buffer);
        return false;
    }

    OutputDebugStringA("[LaserSightComponent] Successfully loaded FXC: ");
    OutputDebugStringA(path);
    OutputDebugStringA("\n");

    return true;
}

bool LaserSightComponent::LoadTexture(const char* path)
{
    if (!path || path[0] == '\0')
    {
        OutputDebugStringA("[LaserSightComponent] Invalid texture path\n");
        return false;
    }

    // Load texture from file
    FILE* file = nullptr;
    errno_t err = fopen_s(&file, path, "rb");
    if (err != 0 || !file)
    {
        OutputDebugStringA("[LaserSightComponent] Failed to open texture file: ");
        OutputDebugStringA(path);
        OutputDebugStringA("\n");
        return false;
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (fileSize == 0)
    {
        OutputDebugStringA("[LaserSightComponent] Texture file is empty\n");
        fclose(file);
        return false;
    }

    // Read file into buffer
    void* buffer = new char[fileSize];
    if (!buffer)
    {
        OutputDebugStringA("[LaserSightComponent] Failed to allocate memory for texture\n");
        fclose(file);
        return false;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, file);
    fclose(file);

    if (bytesRead != fileSize)
    {
        OutputDebugStringA("[LaserSightComponent] Failed to read complete texture file\n");
        delete[] static_cast<char*>(buffer);
        return false;
    }

    OutputDebugStringA("[LaserSightComponent] Successfully loaded texture: ");
    OutputDebugStringA(path);
    OutputDebugStringA("\n");

    return true;
}

void LaserSightComponent::SetBeamLength(float length)
{
    GTA::CWeaponComponentLaserSightInfo::SetBeamLength(length);
    OutputDebugStringA("[LaserSightComponent] Beam length set to: ");
    char buffer[32];
    sprintf_s(buffer, sizeof(buffer), "%.2f\n", length);
    OutputDebugStringA(buffer);
}

void LaserSightComponent::SetBeamColor(float r, float g, float b, float a)
{
    GTA::CWeaponComponentLaserSightInfo::SetBeamColor(r, g, b, a);
    char buffer[128];
    sprintf_s(buffer, sizeof(buffer), "[LaserSightComponent] Beam color set to: RGBA(%.2f, %.2f, %.2f, %.2f)\n", r, g, b, a);
    OutputDebugStringA(buffer);
}

void LaserSightComponent::SetEnabled(bool enabled)
{
    GTA::CWeaponComponentLaserSightInfo::SetEnabled(enabled);
    OutputDebugStringA("[LaserSightComponent] Laser sight ");
    OutputDebugStringA(enabled ? "enabled\n" : "disabled\n");
}

float LaserSightComponent::GetBeamLength() const
{
    return GTA::CWeaponComponentLaserSightInfo::GetBeamLength();
}

bool LaserSightComponent::IsEnabled() const
{
    return GTA::CWeaponComponentLaserSightInfo::IsEnabled();
}

void LaserSightComponent::SetBeamWidth(float width)
{
    m_beamWidth = width;
    char buffer[32];
    sprintf_s(buffer, sizeof(buffer), "[LaserSightComponent] Beam width set to: %.2f\n", width);
    OutputDebugStringA(buffer);
}

float LaserSightComponent::GetBeamWidth() const
{
    return m_beamWidth;
}
