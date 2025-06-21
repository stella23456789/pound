# Compiling Pound (incomplete documentation!!)

# To use and compile Pound, you will need to **dump your own Switch or Switch 2 firmware** and place it in the following directory:

```
/assets/fw/
```

# No firmware or system files are provided with this emulator.

(linux only rn bc lazy)

## Linux (Fedora/RHEL/openSUSE)

## Linux (Debian/Ubuntu)

### Installing dependencies and cloning Pound

Run the following in your terminal:

``sudo apt update

sudo apt install -y ninja-build clang lld cmake ccache libx11-dev libxext-dev libxrandr-dev libxcursor-dev libxi-dev libxinerama-dev libwayland-dev libxkbcommon-dev wayland-protocols git``

Now run the following:

``git clone https://www.github.com/pound-emu/pound.git``

and then:

``cmake -G Ninja -B (where you put pound source code) -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++``

## Linux (Arch/SteamOS)