# Guía de Compilación

## Requisitos

- Visual Studio 2019 o superior (Community Edition es suficiente)
- CMake 3.10 o superior
- Windows SDK (incluido con Visual Studio)
- Script Hook V SDK

## Pasos de Compilación

### 1. Clonar el Repositorio

```bash
git clone https://github.com/santiagomcastro427-source/gta5-vanilla-weapon-components-addon.git
cd gta5-vanilla-weapon-components-addon
```

### 2. Crear Directorio de Build

```bash
mkdir build
cd build
```

### 3. Generar Archivos de Build con CMake

```bash
cmake ..
```

O especificar el generador de Visual Studio:

```bash
cmake -G "Visual Studio 16 2019" ..
```

### 4. Compilar el Proyecto

**Opción A: Usando CMake**

```bash
cmake --build . --config Release
```

**Opción B: Usando Visual Studio**

```bash
start VanillaWeaponComponentsAddon.sln
```

Luego en Visual Studio:
- Selecciona `Release` en la configuración
- Click derecho en el proyecto → Build

### 5. Salida

El archivo compilado `VanillaWeaponComponentsAddon.dll` se ubicará en:

```
build/bin/VanillaWeaponComponentsAddon.dll
```

## Instalación Después de Compilar

1. Copia `VanillaWeaponComponentsAddon.dll` a la carpeta raíz de GTA V
2. Renombra el archivo a `VanillaWeaponComponentsAddon.asi` (ASI Loader lo cargará automáticamente)
3. Coloca la carpeta `config` en `scripts/VanillaWeaponComponentsAddon/`
4. Reinicia el juego

## Solución de Problemas

### Error: CMake no encontrado

Instala CMake desde https://cmake.org/download/

### Error: Visual Studio no encontrado

Instala Visual Studio Community desde https://visualstudio.microsoft.com/

### Error: Windows SDK no encontrado

Instala el Windows SDK desde Visual Studio Installer

### DLL no se carga

- Verifica que el ASI Loader esté instalado
- Comprueba que el archivo está en la carpeta correcta
- Revisa que sea `.asi` y no `.dll`
- Activa el Log de ASI Loader para debugging

## Debug

Para compilar en modo Debug:

```bash
cmake --build . --config Debug
```

Esto generará símbolos de debug útiles para troubleshooting.

## Limpiar Build

```bash
cd build
cmake --build . --target clean
```

O simplemente:

```bash
rm -r build/*
```
