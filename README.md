# UwUrg

A port of [turg](https://github.com/commrade-goad/turg) from C to C++ for an `OOP Class` project.

## Library used

- [raylib](https://github.com/raysan5/raylib)

## Build

### Windows

You can download the release by going to the `tags` section.  
Currently, the app is not in its final version, but you can try it from the `pre-release`.  
Download the file named `rc1-x86_64-win32.zip`, extract it to your preferred folder,  
then open the `UwUrg's Release` folder and run `uwurg.exe`.

### Arch Linux

Install dependencies:
```sh
sudo pacman -S base-devel clang glu cmake libx11 git libglvnd gcc-libs libxcb libxau libxdmcp libxcursor libxinerama libxrandr
```

### Ubuntu / Linux Mint

#### Install from Release

You can download the release by going to the `tags` section.  
Currently, the app is not in its final version, but you can try it from the `pre-release`.  
Download the file named `rc1-x86_64-linux.zip`, extract it to your preferred folder,  
then open the `UwUrg's Release` folder and run `uwurg`.

#### Build from Source

Install dependencies:
```bash
sudo apt install -y cmake libgl1-mesa-dev libglu1-mesa-dev libx11-dev libxcb1-dev libxau-dev libxdmcp-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libasound2-dev git build-essential clang
```

> **Note:**  
> It is recommended to install `cmake` via **Snap** to get the latest version (the version from apt is usually outdated):
```bash
sudo snap install cmake --classic
```

### Shared

```sh
git clone https://github.com/commrade-goad/uwurg
cd uwurg
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release .. # or use `Debug` for debug build
make -j$(nproc)
cd ..
./build/uwurg
```
