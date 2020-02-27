#!/usr/bin/env bash

conan remote add conan https://api.bintray.com/conan/conan/conan-center
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan

conan profile update settings.cppstd=17 default

rm -rf build && mkdir build && cd build && conan install .. --build=missing && cmake .. -G "Unix Makefiles" && cmake --build .