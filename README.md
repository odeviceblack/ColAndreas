# ColAndreas

ColAndreas is a plugin for SA-MP that creates a simulation of the San Andreas world. Using the [Bullet Physics library](http://bulletphysics.org/), ColAndreas gives the server knowledge of the game environment itself.

**Watch it in action:** [https://www.youtube.com/watch?v=aSabQWqQBkI](https://www.youtube.com/watch?v=aSabQWqQBkI)

## Download

Go to the [releases page](https://github.com/Pottus/ColAndreas/releases) and grab the latest *ColAndreas_Precompiled* zip file. It contains:

 * Windows and Linux versions of the plugin.
 * The PAWN include file.
 * The Wizard executable.

> **Important:** The Wizard-generated file must be placed in `/scriptfiles/ColAndreas/` with the name `ColAndreas.cadb`.

## Wizard

The Wizard generates the collision database file (`ColAndreas.cadb`) from your GTA: San Andreas installation files.

### Usage

```bash
./wizard <GTA_SA_DIRECTORY> [OPTIONS]
```

Option Description
<dir> Path to GTA:SA installation (required).
--output <file> Output file path (default: ColAndreas.cadb).
--samp Include SA-MP objects (SAMP.img, SAMP.ipl, SAMP.ide).
--custom Include objects from CUSTOM.img.

Examples

Linux/Termux:

```bash
./wizard /home/user/gta_sa --output ColAndreas.cadb --samp
```

Windows:

```powershell
wizard.exe "C:\Program Files\GTA San Andreas" --output ColAndreas.cadb --samp
```

File Fallback

The Wizard automatically tries alternative paths when a file is not found:

Primary Fallback
models/gta_int.img texdb/gta_int.img
models/gta3.img texdb/gta3.img

If neither is found, the file is skipped with a warning.

Build Wizard from Source

Requirements:

· C++11 compiler (GCC ≥ 4.8, Clang ≥ 3.3, MSVC ≥ 2015)
· CMake ≥ 3.10

Linux / Termux:

```bash
cd WizardCLI
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
./wizard /path/to/gta_sa --output ColAndreas.cadb
```

Windows (MinGW-w64):

```powershell
cd WizardCLI
mkdir build && cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
mingw32-make -j
wizard.exe "C:\GTA San Andreas" --output ColAndreas.cadb
```

Windows (MSVC):

```powershell
cd WizardCLI
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
wizard.exe "C:\GTA San Andreas" --output ColAndreas.cadb
```

Plugin Installation

Windows

Copy ColAndreas.dll to your plugins/ folder and add it to server.cfg:

```
plugins ColAndreas
```

Linux

Copy ColAndreas.so to your plugins/ folder and add it to server.cfg:

```
plugins ColAndreas.so
```

Linux Note:
If you get the error Failed (libBulletCollision.so.2.82: cannot open shared object file), your system doesn't have the required libraries.
Solutions:

1. Use the statically linked version of the plugin (ColAndreas_static.so).
2. Install the Bullet libraries (32-bit/i386 version):
   ```bash
   sudo apt-get install libbulletcollision2.82:i386 libbulletdynamics2.82:i386 liblinearmath2.82:i386 libbulletsoftbody2.82:i386
   ```

Build Instructions (Plugin)

Debian/Ubuntu

```bash
sudo apt-get install libbullet-dev cmake
cd ColAndreas
cmake -B build
cd build
make
```

Windows (Visual Studio)

Requirements:

· Visual Studio 2015 or later.
· CMake ≥ 3.10.
· Bullet Physics SDK.

Steps:

1. Download the SDK from the Bullet3 Repository.
2. Build Bullet or use prebuilt binaries.
3. Run CMake:

```powershell
cd ColAndreas
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022" -DBULLET_ROOT="C:\path\to\bullet" -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```
