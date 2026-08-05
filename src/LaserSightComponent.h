#pragma once

#include "../include/gta/weapon_components.h"

class LaserSightComponent : public GTA::CWeaponComponentLaserSightInfo
{
public:
    LaserSightComponent();
    ~LaserSightComponent();

    void Initialize() override;
    void Release() override;
    bool LoadFXC(const char* path) override;
    bool LoadTexture(const char* path) override;

    void SetBeamLength(float length) override;
    void SetBeamColor(float r, float g, float b, float a) override;
    void SetEnabled(bool enabled) override;

    float GetBeamLength() const override;
    bool IsEnabled() const override;

    // Additional methods
    void SetBeamWidth(float width);
    float GetBeamWidth() const;

private:
    float m_beamWidth;
};
