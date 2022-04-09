#! /bin/bash


if [[ $# < 1 ]]; then
    echo "Please provide the path to your ndk"
    exit 1
fi

requirements=(wget unzip cmake git make)

for requirement in ${requirements[@]} ; do
    if ! type "${requirement}" > /dev/null 2>&1; then
            echo "Requirement '${requirement}' not found!"
            exit 1
    fi
done

bad_cmake_version(){
    echo "Minimum required CMake version is ${REQUIRED_CMAKE_MAJOR}.${REQUIRED_CMAKE_MINOR}.${REQUIRED_CMAKE_PATCH}"
    echo "You only have ${CMAKE_VERSION}"
    echo "Please upgrade your CMake"
    exit 1
}

readonly REQUIRED_CMAKE_MAJOR=3
readonly REQUIRED_CMAKE_MINOR=7
readonly REQUIRED_CMAKE_PATCH=2

readonly CMAKE_VERSION=$(cmake --version | head -n 1 | sed 's/cmake version //g')
readonly CMAKE_MAJOR=$(echo ${CMAKE_VERSION} | sed -r 's/^([0-9]+).*$/\1/')
readonly CMAKE_MINOR=$(echo ${CMAKE_VERSION} | sed -r 's/^[0-9]+\.([0-9]+).*$/\1/')
readonly CMAKE_PATCH=$(echo ${CMAKE_VERSION} | sed -r 's/^[0-9]+\.[0-9]+\.([0-9]+).*$/\1/')

if (( ${CMAKE_MAJOR} < ${REQUIRED_CMAKE_MAJOR} )) ; then
    bad_cmake_version
elif (( ${CMAKE_MAJOR} == ${REQUIRED_CMAKE_MAJOR} )) ; then

    if (( ${CMAKE_MINOR} < ${REQUIRED_CMAKE_MINOR} )) ; then
        bad_cmake_version
    elif (( ${CMAKE_MINOR} == ${REQUIRED_CMAKE_MINOR} )) ; then
        if (( ${CMAKE_PATCH} < ${REQUIRED_CMAKE_PATCH} )) ; then
            bad_cmake_version
        fi
    fi
fi


if [[ $? != 0 ]]; then
    exit 1
fi

ndk_input_path=$1
if [[ ${1: -1} != / ]]; then
    ndk_input_path=${ndk_input_path}/
fi

readonly CURRENT_PATH=$(dirname "$(readlink -f "$0")")

if [[ ${ndk_input_path:0:1} != / ]]; then
    readonly NDK_PATH=${CURRENT_PATH}/${ndk_input_path}
else
    readonly NDK_PATH=${ndk_input_path}
fi

set -eu
mkdir -p build-android
cd build-android
mkdir -p armeabi-v7a
cmake -DCMAKE_SYSTEM_NAME=Android -DCMAKE_ANDROID_NDK=${NDK_PATH} -DCMAKE_ANDROID_ARCH_ABI=armeabi-v7a -DCMAKE_ANDROID_STL_TYPE=c++_static -DCMAKE_BUILD_TYPE=Debug ..
make
make install
