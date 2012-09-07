LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_CPPFLAGS = -DCOCOS2D_DEBUG -std=gnu++0x

LOCAL_SRC_FILES := \
bootstrap/main.cpp \
../../generic/wip/AppDelegate.cpp \
../../generic/wip/Block.cpp \
../../generic/wip/BlockSituation.cpp \
../../generic/wip/BlockState.cpp \
../../generic/wip/BlockType.cpp \
../../generic/wip/Clearing.cpp \
../../generic/wip/Combo.cpp \
../../generic/wip/ComboSituation.cpp \
../../generic/wip/FuriousBlocksCore.cpp \
../../generic/wip/FuriousBlocksCoreDefaults.cpp \
../../generic/wip/FuriousBlocksCoreListener.cpp \
../../generic/wip/GameSituation.cpp \
../../generic/wip/GameType.cpp \
../../generic/wip/GarbageBlockType.cpp \
../../generic/wip/GarbageSituation.cpp \
../../generic/wip/Move.cpp \
../../generic/wip/MoveType.cpp \
../../generic/wip/Panel.cpp \
../../generic/wip/PanelEvent.cpp \
../../generic/wip/PanelEventType.cpp \
../../generic/wip/PanelListener.cpp \
../../generic/wip/PanelSituation.cpp \
../../generic/wip/PanelState.cpp \
../../generic/wip/Player.cpp \
../../generic/wip/Point.cpp \
../../generic/wip/SimpleRNG.cpp \
renderer/Animation.cpp \
renderer/NonLoopingAnimation.cpp \
renderer/PanelScene.cpp \
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../generic/wip \
                    $(LOCAL_PATH)/renderer

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
