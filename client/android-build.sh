#! /bin/bash


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

set -eu
mkdir -p build-android
cd build-android
mkdir -p armeabi-v7a

readonly NDK_VERSION=20
readonly ANDROID_ZIP_NAME=android-ndk-r${NDK_VERSION}-linux-x86_64.zip
readonly NDK_DIR=`realpath ./ndk/android-ndk-r${NDK_VERSION}/`

if [ -d ${NDK_DIR} ] ; then
    echo "Using existing Android NDK ${NDK_DIR}"
else
    echo "Downloading Android NDK..."
    wget --no-verbose --directory-prefix ndk https://dl.google.com/android/repository/${ANDROID_ZIP_NAME}
    echo "Unzipping Android NDK..."
    unzip -q -d ndk ndk/${ANDROID_ZIP_NAME}
    rm -rf ndk/${ANDROID_ZIP_NAME}
fi

cmake -DCMAKE_SYSTEM_NAME=Android -DCMAKE_ANDROID_NDK=${NDK_DIR} -DCMAKE_ANDROID_ARCH_ABI=armeabi-v7a -DCMAKE_ANDROID_STL_TYPE=c++_static -DCMAKE_BUILD_TYPE=Debug ..
make
make install
