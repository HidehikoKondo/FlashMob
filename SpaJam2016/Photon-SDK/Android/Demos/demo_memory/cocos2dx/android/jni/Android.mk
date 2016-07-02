# Generated by VisualGDB

LOCAL_PATH := $(call my-dir)
COCOS2DX_ROOT := $(LOCAL_PATH)/../../../../etc-bin/cocos2dx
PHOTON_SDK_ROOT := $(LOCAL_PATH)/../../../../..

include $(CLEAR_VARS)

$(shell mkdir assets)
$(shell cp -rf ../resources/* assets)

LOCAL_MODULE := demomemory
#VisualGDBAndroid: AutoUpdateSourcesInNextLine
LOCAL_SRC_FILES := ../../../../shared/src/Console.cpp ../../../src/BaseView.cpp ../../../src/Game.cpp ../../../src/LoadBalancingListener.cpp ../../src/AppDelegate.cpp ../../src/ListController.cpp ../../src/View.cpp main.cpp

LOCAL_C_INCLUDES := $(COCOS2DX_ROOT)/cocos2dx $(COCOS2DX_ROOT)/cocos2dx/include $(COCOS2DX_ROOT)/cocos2dx/platform/android $(COCOS2DX_ROOT)/cocos2dx/kazmath/include $(PHOTON_SDK_ROOT) $(LOCAL_PATH)/../../inc $(LOCAL_PATH)/../../../../shared/inc

LOCAL_CFLAGS := -DEG_DEBUGGER -D__STDINT_LIMITS -D_EG_ANDROID_PLATFORM
LOCAL_STATIC_LIBRARIES := loadbalancing-cpp-static-prebuilt photon-cpp-static-prebuilt common-cpp-static-prebuilt
LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, $(PHOTON_SDK_ROOT)/LoadBalancing-cpp/lib)
$(call import-add-path, $(COCOS2DX_ROOT))
$(call import-add-path, $(COCOS2DX_ROOT)/cocos2dx/platform/third_party/android/prebuilt)

$(call import-module,loadbalancing-cpp-prebuilt)
$(call import-module,cocos2dx)
