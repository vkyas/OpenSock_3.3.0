#!/bin/sh

BASE_DIR="$(pwd)"
LIBS_DIR="${BASE_DIR}/libs"
OBJ_DIR="${BASE_DIR}/obj"

rm -rf "$LIBS_DIR" "$OBJ_DIR"
sleep 0.2
clear

# su -c "/data/user/0/com.itsaky.androidide/files/home/android-sdk/ndk/17.2.4988734/ndk-build"

su -c "/data/user/0/com.itsaky.androidide/files/home/android-sdk/ndk/24.0.8215888/ndk-build"

cp "${BASE_DIR}/libs/armeabi-v7a/sock" "${BASE_DIR}/libs/arm64-v8a/"
exit