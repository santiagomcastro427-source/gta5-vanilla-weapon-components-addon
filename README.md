# GTA5 Vanilla Weapon Components Addon

Addon para GTA V Legacy 2026 que carga componentes de armas vanilla con soportes láser.

## Descripción

Este addon carga componentes de armas láser para los siguientes modelos:
- **w_at_pi_flsh_2** - Pistola con flashlight
- **w_at_pi_flsh_3** - Pistola con flashlight
- **w_at_ar_flsh_3** - Rifle de asalto con flashlight

## Características

- Carga `CWeaponComponentLaserSightInfo`
- Extensión `ExtendedWeaponComponentLaserSightInfo`
- Integración de efectos láser (`laserbeam.fxc`)
- Texturas de ruido láser (`laser_noise.dds`)
- Configuración modular mediante archivos INI

## Requisitos

- GTA V (Versión 1.0.2060.0 o superior)
- Script Hook V
- .NET Framework 4.8+

## Instalación

1. Descargar el archivo `VanillaWeaponComponentsAddon.asi`
2. Colocarlo en la carpeta raíz de GTA V
3. El addon se cargará automáticamente al iniciar el juego

## Configuración

Editar `weapon_components.ini` en la carpeta de configuración del addon para personalizar:
- Propiedades del láser
- Distancia del rayo láser
- Color del láser
- Compatibilidad de armas

## Estructura del Proyecto

```
gta5-vanilla-weapon-components-addon/
├── src/
│   ├── VanillaWeaponComponentsAddon.cpp
│   ├── VanillaWeaponComponentsAddon.h
│   ├── WeaponComponentLoader.cpp
│   ├── WeaponComponentLoader.h
│   ├── LaserSightComponent.cpp
│   └── LaserSightComponent.h
├── include/
│   └── gta/
│       └── weapon_components.h
├── config/
│   └── weapon_components.ini
├── CMakeLists.txt
├── LICENSE
└── README.md
```

## Desarrollo

### Compilar

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### Requisitos de Build

- Visual Studio 2019+
- C++17 o superior
- Script Hook V SDK

## Modelos Soportados

| Modelo | Tipo | Descripción |
|--------|------|----------|
| w_at_pi_flsh_2 | Pistola | Pistola con componente láser |
| w_at_pi_flsh_3 | Pistola | Pistola mejorada con componente láser |
| w_at_ar_flsh_3 | Rifle | Rifle de asalto con componente láser |

## Licencia

MIT License - Ver archivo LICENSE

## Autor

Creado para GTA V Legacy 2026

## Soporte

Para reportar bugs o sugerencias, abre un issue en el repositorio.