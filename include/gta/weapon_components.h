#pragma once

namespace GTA
{
    // Weapon component types
    enum class WeaponComponentType : unsigned char
    {
        LaserSight = 0x00,
        Flashlight = 0x01,
        Suppressor = 0x02,
        ExpandedClip = 0x03
    };

    // Laser sight configuration
    struct LaserSightConfig
    {
        float beamLength;
        float beamWidth;
        float laserRed;
        float laserGreen;
        float laserBlue;
        float laserAlpha;
        bool enabled;
        const char* fxcPath;
        const char* texturePath;
    };

    // Weapon component laser sight info
    class CWeaponComponentLaserSightInfo
    {
    public:
        CWeaponComponentLaserSightInfo();
        ~CWeaponComponentLaserSightInfo();

        virtual void Initialize();
        virtual void Release();
        virtual bool LoadFXC(const char* path);
        virtual bool LoadTexture(const char* path);

        void SetBeamLength(float length);
        void SetBeamColor(float r, float g, float b, float a);
        void SetEnabled(bool enabled);

        float GetBeamLength() const;
        bool IsEnabled() const;

    private:
        float m_beamLength;
        float m_beamR, m_beamG, m_beamB, m_beamA;
        bool m_enabled;
        void* m_fxcBuffer;
        void* m_textureBuffer;
    };

    // Extended weapon component laser sight info
    class ExtendedWeaponComponentLaserSightInfo
    {
    public:
        ExtendedWeaponComponentLaserSightInfo();
        ~ExtendedWeaponComponentLaserSightInfo();

        void SetLaserSightInfo(CWeaponComponentLaserSightInfo* info);
        CWeaponComponentLaserSightInfo* GetLaserSightInfo() const;

        void SetIsLaserSight(bool isLaser);
        bool GetIsLaserSight() const;

        void SetLaserNoiseTexture(const char* texturePath);
        void SetLaserBeamEffect(const char* effectPath);

        const char* GetLaserNoiseTexture() const;
        const char* GetLaserBeamEffect() const;

    private:
        CWeaponComponentLaserSightInfo* m_laserSightInfo;
        bool m_isLaserSight;
        const char* m_laserNoiseTexture;
        const char* m_laserBeamEffect;
    };

    // Weapon model structure
    struct WeaponModel
    {
        const char* modelName;
        unsigned int modelHash;
        WeaponComponentType componentType;
        ExtendedWeaponComponentLaserSightInfo* laserInfo;
    };
}
