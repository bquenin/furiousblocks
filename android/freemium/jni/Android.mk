LOCAL_PATH := $(call my-dir)

#
# libboost_system-gcc-mt-1_49.a
#
#include $(CLEAR_VARS)
#LOCAL_MODULE    := libboost_thread
#LOCAL_SRC_FILES := boost/lib/libboost_system-gcc-mt-1_49.a
#include $(PREBUILT_STATIC_LIBRARY)

#
# libgame
#
include $(CLEAR_VARS)

LOCAL_MODULE := furiousblocks_shared
LOCAL_MODULE_FILENAME := libfuriousblocks

#
# Build flags
#
# LOCAL_CPPFLAGS := -std=gnu++0x -fexceptions -frtti
#
LOCAL_CPPFLAGS := -fexceptions
LOCAL_CPPFLAGS += -frtti
LOCAL_CPPFLAGS += -std=gnu++0x
#LOCAL_CPPFLAGS += -Wall
#LOCAL_CPPFLAGS += -pedantic

#
# Build flags for the FREEMIUM version
#
LOCAL_CPPFLAGS += -DFREEMIUM

#
# Build flags for the DEBUG version
#
LOCAL_CPPFLAGS += -DCOCOS2D_DEBUG=1

LOCAL_C_INCLUDES := \
$(LOCAL_PATH)/bootstrap \
$(LOCAL_PATH)/../../generic \
$(LOCAL_PATH)/../../generic/animation \
$(LOCAL_PATH)/../../generic/core \
$(LOCAL_PATH)/../../generic/ext \
$(LOCAL_PATH)/../../generic/scenes \
$(LOCAL_PATH)/../../generic/script \
$(LOCAL_PATH)/../../generic/tween/easing \
$(LOCAL_PATH)/../../generic/tween

LOCAL_SRC_FILES := \
bootstrap/main.cpp \
../../generic/AppDelegate.cpp \
../../generic/Assets.cpp \
../../generic/animation/Animation.cpp \
../../generic/animation/NonLoopingAnimation.cpp \
../../generic/core/Block.cpp \
../../generic/core/Combo.cpp \
../../generic/core/FuriousBlocksCore.cpp \
../../generic/core/Move.cpp \
../../generic/core/Panel.cpp \
../../generic/core/PanelEvent.cpp \
../../generic/core/Point.cpp \
../../generic/core/SimpleRNG.cpp \
../../generic/ext/CCTexture2DMutable.cpp \
../../generic/scenes/AbstractPanelScene.cpp \
../../generic/scenes/AdScene.cpp \
../../generic/scenes/CreditsScene.cpp \
../../generic/scenes/LogoScene.cpp \
../../generic/scenes/PanelMenuOverlay.cpp \
../../generic/scenes/PanelScene.cpp \
../../generic/scenes/QuitOverlay.cpp \
../../generic/scenes/StarNumber.cpp \
../../generic/scenes/TitleScene.cpp \
../../generic/scenes/TouchPlayer.cpp \
../../generic/scenes/TutorialPlayer.cpp \
../../generic/scenes/TutorialScene.cpp \
../../generic/script/Action.cpp \
../../generic/script/CursorAction.cpp \
../../generic/script/PauseAction.cpp \
../../generic/script/Script.cpp \
../../generic/script/SetBlocksAction.cpp \
../../generic/script/TextToType.cpp \
../../generic/script/TypeTextAction.cpp \
../../generic/tween/easing/easing_back.cpp \
../../generic/tween/easing/easing_bounce.cpp \
../../generic/tween/easing/easing_circ.cpp \
../../generic/tween/easing/easing_cubic.cpp \
../../generic/tween/easing/easing_elastic.cpp \
../../generic/tween/easing/easing_expo.cpp \
../../generic/tween/easing/easing_linear.cpp \
../../generic/tween/easing/easing_none.cpp \
../../generic/tween/easing/easing_quad.cpp \
../../generic/tween/easing/easing_quart.cpp \
../../generic/tween/easing/easing_quint.cpp \
../../generic/tween/easing/easing_sine.cpp \
../../generic/tween/base_tweener.cpp \
../../generic/tween/single_tweener.cpp \
../../generic/tween/tweener.cpp \
../../generic/tween/tweener_group.cpp \
../../generic/tween/tweener_sequence.cpp

# LOCAL_STATIC_LIBRARIES := libboost_thread

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
