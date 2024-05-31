#!/bin/bash

BASE_DIR=$PWD

#1 Get raylib-cpp

VER=4.2.8
wget https://github.com/RobLoach/raylib-cpp/archive/refs/tags/v${VER}.tar.gz
tar -xvf v${VER}.tar.gz
mv raylib-cpp-${VER} raylib-cpp

# The largest dir is examples (~5MB). If you want it, remove thse 3 lines:
cd raylib-cpp
shopt -s extglob # permit the following line
rm -rf !(include)
cd ${BASE_DIR}

# shopt? See https://stackoverflow.com/questions/52205526/syntax-error-on-bash-rm-rf-unexpected-token

#2 Export from Vcpkg (about 27MB)

if [[ $(grep -i Microsoft /proc/version) ]]; then     # Running WSL2
  /mnt/c/vcpkg/vcpkg.exe export cpr nlohmann-json raylib --raw --output-dir=$(wslpath -w $BASE_DIR) --output=vcpkg-export
else
  $VCPKG_ROOT/vcpkg export cpr nlohmann-json raylib --raw --output-dir=$PWD --output=vcpkg-export
#  unzip vcpkg-export.zip
fi

cd ${BASE_DIR}

#3 liboia C++ API

#wget https://github.com/D7EAD/liboai/archive/refs/heads/main.zip
wget https://github.com/pkeir/liboai/archive/refs/heads/main.zip
unzip main.zip

mv liboai-main liboai
cd liboai/liboai
mkdir build && cd build

if [[ $(grep -i Microsoft /proc/version) ]]; then     # Running WSL2

  mkdir ${BASE_DIR}/liboai/install # wslpath needs paths to exist already!
  /mnt/c/Program\ Files/CMake/bin/cmake.exe -G "Visual Studio 17 2022" -DCMAKE_INSTALL_PREFIX=$(wslpath -w ${BASE_DIR}/liboai/install) -DCMAKE_TOOLCHAIN_FILE=$(wslpath -w ${BASE_DIR}/vcpkg-export/scripts/buildsystems/vcpkg.cmake) ..
  /mnt/c/Program\ Files/CMake/bin/cmake.exe --build . --target install -j 4

else

  cmake -DCMAKE_INSTALL_PREFIX=${BASE_DIR}/liboai/install \
        -DCMAKE_TOOLCHAIN_FILE=${BASE_DIR}/vcpkg-export/scripts/buildsystems/vcpkg.cmake \
        -DCMAKE_BUILD_TYPE=Debug \
        ..
  cmake --build . --target install -j 4     # i.e. make -j 4 && make install

fi

cd ${BASE_DIR}

#4 raylib-tileson

wget https://github.com/pkeir/raylib-tileson/archive/refs/heads/master.zip
unzip master.zip

mv raylib-tileson-master raylib-tileson
cd raylib-tileson
mkdir build && cd build

if [[ $(grep -i Microsoft /proc/version) ]]; then     # Running WSL2

  mkdir ${BASE_DIR}/raylib-tileson/install # wslpath needs paths to exist ""
  /mnt/c/Program\ Files/CMake/bin/cmake.exe -G "Visual Studio 17 2022" -DCMAKE_INSTALL_PREFIX=$(wslpath -w ${BASE_DIR}/raylib-tileson/install) -DCMAKE_TOOLCHAIN_FILE=$(wslpath -w ${BASE_DIR}/vcpkg-export/scripts/buildsystems/vcpkg.cmake) ..
  /mnt/c/Program\ Files/CMake/bin/cmake.exe --build . --target install -j 4

else

  cmake -DCMAKE_INSTALL_PREFIX=${BASE_DIR}/raylib-tileson/install \
        -DCMAKE_TOOLCHAIN_FILE=${BASE_DIR}/vcpkg-export/scripts/buildsystems/vcpkg.cmake \
        -DCMAKE_BUILD_TYPE=Debug \
        ..
  cmake --build . --target install -j 4

fi

cd ${BASE_DIR}
