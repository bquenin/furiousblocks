NDK_ROOT=/Users/bq/android-ndk-r8e
COCOS2DX_ROOT=/Users/bq/cocos2d-2.0-x-2.0.4
APP_ROOT=../..
APP_ANDROID_ROOT=$APP_ROOT/android/freemium

echo "NDK_ROOT = $NDK_ROOT"
echo "COCOS2DX_ROOT = $COCOS2DX_ROOT"
echo "APP_ROOT = $APP_ROOT"
echo "APP_ANDROID_ROOT = $APP_ANDROID_ROOT"

echo "Using prebuilt externals"
"$NDK_ROOT"/ndk-build -C "$APP_ANDROID_ROOT" $* "NDK_MODULE_PATH=${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos2dx/platform/third_party/android/prebuilt" V=1 -j16

cp obj/local/armeabi/libfuriousblocks.so libs/armeabi/libfuriousblocks.so
