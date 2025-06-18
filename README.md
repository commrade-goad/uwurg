# UwUrg

a port of [turg](https://github.com/commrade-goad/turg) from C to C++ with for `OOP Class` Project.

## Library used

- [raylib](https://github.com/raysan5/raylib)

## Build
### Arch Linux
Run : `sudo pacman -S base-devel clang glu cmake libx11 git libglvnd gcc-libs libxcb libxau libxdmcp libxcursor libxinerama libxrandr`

### Ubuntu
```bash
sudo apt install -y cmake libgl1-mesa-dev libglu1-mesa-dev libx11-dev libxcb1-dev libxau-dev libxdmcp-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libasound2-dev git build-essential clang
```

> **Note:**  
> Disarankan install `cmake` via **Snap** supaya dapat versi terbaru (karena versi dari apt biasanya ketinggalan jauh):
```bash
sudo snap install cmake --classic
```

### Shared

```sh
git clone https://github.com/commrade-goad/uwurg
cd uwurg
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release .. #or `Debug` for debug build.
make -j`nproc`
cd ..
./build/uwurg
```
