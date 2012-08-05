# set params
# NDK_ROOT=/Users/bquenin/android-ndk-r7-crystax-5.beta2
NDK_ROOT=/Users/bquenin/android-ndk-r8b
COCOS2DX_ROOT=/Users/bquenin/cocos2d-2.0-rc2-x-2.0.1
GAME_ROOT=..
GAME_ANDROID_ROOT=$GAME_ROOT/android

buildexternalsfromsource=

usage(){
cat << EOF
usage: $0 [options]

Build C/C++ native code using Android NDK

OPTIONS:
   -s	Build externals from source
   -h	this help
EOF
}

while getopts "s" OPTION; do
	case "$OPTION" in
		s)
			buildexternalsfromsource=1
			;;
		h)
			usage
			exit 0
			;;
	esac
done

if [[ $buildexternalsfromsource ]]; then
    echo "Building external dependencies from source"
    $NDK_ROOT/ndk-build -C $GAME_ANDROID_ROOT \
        NDK_MODULE_PATH=${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos2dx/platform/third_party/android/source
else
    echo "Using prebuilt externals"
    $NDK_ROOT/ndk-build -C $GAME_ANDROID_ROOT \
        NDK_MODULE_PATH=${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos2dx/platform/third_party/android/prebuilt
fi

cp obj/local/armeabi/libgame.so libs/armeabi/libgame.so

