#!/bin/bash

# Install main deps
sudo apt-get update
sudo apt-get install gcc g++

# Build CMake from source
version=3.13
build=4
mkdir ~/temp
cd ~/temp
wget https://cmake.org/files/v$version/cmake-$version.$build.tar.gz
tar -xzvf cmake-$version.$build.tar.gz
cd cmake-$version.$build/
./bootstrap
make -j$(nproc)
sudo make install
