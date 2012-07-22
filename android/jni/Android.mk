LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_CPPFLAGS = -std=gnu++0x

LOCAL_SRC_FILES := bootstrap/main.cpp \
                   bootstrap/AppDelegate.cpp \
                   ../../generic/core/Block.cpp \
                   ../../generic/core/Combo.cpp \
                   ../../generic/core/FBPanel.cpp \
                   ../../generic/core/FBPoint.cpp \
                   ../../generic/core/FuriousBlocksCore.cpp \
                   ../../generic/core/Move.cpp \
                   ../../generic/core/PanelEvent.cpp \
                   ../../generic/core/Player.cpp \
                   ../../generic/core/SimpleRNG.cpp \
                   renderer/PanelScene.cpp
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../generic/core \
                    $(LOCAL_PATH)/renderer

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) $(call import-module,cocos2dx)
