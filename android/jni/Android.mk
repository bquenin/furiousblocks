LOCAL_PATH := $(call my-dir)

#
# libboost_system-gcc-mt-1_49.a
#
include $(CLEAR_VARS)
LOCAL_MODULE    := libboost_thread
LOCAL_SRC_FILES := boost/lib/libboost_system-gcc-mt-1_49.a
include $(PREBUILT_STATIC_LIBRARY)

#
# libgame
#
include $(CLEAR_VARS)

LOCAL_MODULE := furiousblocks_shared

LOCAL_MODULE_FILENAME := libfuriousblocks

LOCAL_CPPFLAGS = -DCOCOS2D_DEBUG -std=gnu++0x -fexceptions -frtti

LOCAL_CPPFLAGS += -I$(LOCAL_PATH)/boost/include/boost-1_49

LOCAL_SRC_FILES := \
bootstrap/main.cpp \
../../generic/animation/Animation.cpp \
../../generic/animation/NonLoopingAnimation.cpp \
../../generic/core/AppDelegate.cpp \
../../generic/core/Block.cpp \
../../generic/core/BlockSituation.cpp \
../../generic/core/BlockState.cpp \
../../generic/core/BlockType.cpp \
../../generic/core/Clearing.cpp \
../../generic/core/Combo.cpp \
../../generic/core/ComboSituation.cpp \
../../generic/core/FuriousBlocksCore.cpp \
../../generic/core/FuriousBlocksCoreDefaults.cpp \
../../generic/core/FuriousBlocksCoreListener.cpp \
../../generic/core/GameSituation.cpp \
../../generic/core/GameType.cpp \
../../generic/core/GarbageBlockType.cpp \
../../generic/core/GarbageSituation.cpp \
../../generic/core/Move.cpp \
../../generic/core/MoveType.cpp \
../../generic/core/Panel.cpp \
../../generic/core/PanelEvent.cpp \
../../generic/core/PanelEventType.cpp \
../../generic/core/PanelListener.cpp \
../../generic/core/PanelSituation.cpp \
../../generic/core/PanelState.cpp \
../../generic/core/Player.cpp \
../../generic/core/Point.cpp \
../../generic/core/SimpleRNG.cpp \
scenes/StarNumber.cpp \
scenes/PanelScene.cpp

LOCAL_C_INCLUDES := \
$(LOCAL_PATH)/../../generic/core \
$(LOCAL_PATH)/../../generic/animation \
$(LOCAL_PATH)/scenes

LOCAL_STATIC_LIBRARIES := libboost_thread

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
