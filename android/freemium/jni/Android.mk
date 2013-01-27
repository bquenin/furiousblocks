LOCAL_PATH := $(call my-dir)
POCO_ROOT = /Users/bquenin/workspace/furiousblocks/third-party/poco-1.5.1-all
OPENSSL_ROOT = /Users/bquenin/workspace/furiousblocks/third-party/android-external-openssl-ndk-static

#
# libgame
#
include $(CLEAR_VARS)

LOCAL_MODULE := furiousblocks_shared
LOCAL_MODULE_FILENAME := libfuriousblocks

#
# POCO lib
#
LOCAL_CFLAGS := -DPOCO_ANDROID -DPOCO_NO_FPENVIRONMENT -DPOCO_NO_WSTRING -DPOCO_NO_SHAREDMEMORY

LOCAL_C_INCLUDES += $(POCO_ROOT)/Foundation/include
LOCAL_C_INCLUDES += $(POCO_ROOT)/Util/include
LOCAL_C_INCLUDES += $(POCO_ROOT)/Crypto/include
LOCAL_C_INCLUDES += $(POCO_ROOT)/Net/include
LOCAL_C_INCLUDES += $(POCO_ROOT)/NetSSL_OpenSSL/include
LOCAL_C_INCLUDES += $(POCO_ROOT)/JSON/include
LOCAL_C_INCLUDES += $(POCO_ROOT)/XML/include

LOCAL_LDFLAGS += -L $(POCO_ROOT)/lib/Android/armeabi

LOCAL_LDLIBS += -lPocoNetSSL
LOCAL_LDLIBS += -lPocoNet
LOCAL_LDLIBS += -lPocoUtil
LOCAL_LDLIBS += -lPocoXML
LOCAL_LDLIBS += -lPocoCrypto
LOCAL_LDLIBS += -lPocoJSON
LOCAL_LDLIBS += -lPocoFoundation

#
# OpenSSL
#

LOCAL_C_INCLUDES += $(OPENSSL_ROOT)/include

LOCAL_LDFLAGS += -L $(OPENSSL_ROOT)/obj/local/armeabi

LOCAL_LDLIBS += -lssl
LOCAL_LDLIBS += -lcrypto

#
# Build flags
#
LOCAL_CPPFLAGS := -fexceptions -frtti -std=gnu++0x
LOCAL_CPPFLAGS += -DFREEMIUM
LOCAL_CPPFLAGS += -O2 -DNDEBUG -fomit-frame-pointer
#LOCAL_CPPFLAGS += -DCOCOS2D_DEBUG -DDEBUG

LOCAL_C_INCLUDES += $(LOCAL_PATH)/bootstrap
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../generic
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../generic/animation
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../generic/core
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../generic/ext
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../generic/scenes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../generic/script
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../generic/social
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../generic/tween/easing
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../generic/tween

LOCAL_SRC_FILES := \
bootstrap/main.cpp \
../../../generic/AppDelegate.cpp \
../../../generic/Assets.cpp \
../../../generic/animation/Animation.cpp \
../../../generic/animation/NonLoopingAnimation.cpp \
../../../generic/core/Block.cpp \
../../../generic/core/Combo.cpp \
../../../generic/core/FuriousBlocksCore.cpp \
../../../generic/core/Move.cpp \
../../../generic/core/Panel.cpp \
../../../generic/core/PanelEvent.cpp \
../../../generic/core/Point.cpp \
../../../generic/core/SimpleRNG.cpp \
../../../generic/ext/CCTexture2DMutable.cpp \
../../../generic/scenes/AbstractPanelScene.cpp \
../../../generic/scenes/AdScene.cpp \
../../../generic/scenes/CreditsScene.cpp \
../../../generic/scenes/LogoScene.cpp \
../../../generic/scenes/PanelMenuOverlay.cpp \
../../../generic/scenes/PanelScene.cpp \
../../../generic/scenes/QuitOverlay.cpp \
../../../generic/scenes/ScoresScene.cpp \
../../../generic/scenes/StarNumber.cpp \
../../../generic/scenes/TitleScene.cpp \
../../../generic/scenes/TouchPlayer.cpp \
../../../generic/scenes/TutorialPlayer.cpp \
../../../generic/scenes/TutorialScene.cpp \
../../../generic/script/Action.cpp \
../../../generic/script/CursorAction.cpp \
../../../generic/script/PauseAction.cpp \
../../../generic/script/Script.cpp \
../../../generic/script/SetBlocksAction.cpp \
../../../generic/script/TextToType.cpp \
../../../generic/script/TypeTextAction.cpp \
../../../generic/social/Social.cpp \
../../../generic/social/SocialPlayer.cpp \
../../../generic/tween/easing/easing_back.cpp \
../../../generic/tween/easing/easing_bounce.cpp \
../../../generic/tween/easing/easing_circ.cpp \
../../../generic/tween/easing/easing_cubic.cpp \
../../../generic/tween/easing/easing_elastic.cpp \
../../../generic/tween/easing/easing_expo.cpp \
../../../generic/tween/easing/easing_linear.cpp \
../../../generic/tween/easing/easing_none.cpp \
../../../generic/tween/easing/easing_quad.cpp \
../../../generic/tween/easing/easing_quart.cpp \
../../../generic/tween/easing/easing_quint.cpp \
../../../generic/tween/easing/easing_sine.cpp \
../../../generic/tween/base_tweener.cpp \
../../../generic/tween/single_tweener.cpp \
../../../generic/tween/tweener.cpp \
../../../generic/tween/tweener_group.cpp \
../../../generic/tween/tweener_sequence.cpp

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
