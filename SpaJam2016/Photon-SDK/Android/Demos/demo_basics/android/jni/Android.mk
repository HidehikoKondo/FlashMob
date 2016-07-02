# Generated by VisualGDB

LOCAL_PATH := $(call my-dir)
PHOTON_SDK_ROOT := $(LOCAL_PATH)/../../../..

include $(CLEAR_VARS)

LOCAL_MODULE := demobasics
#VisualGDBAndroid: AutoUpdateSourcesInNextLine
LOCAL_SRC_FILES := ../../src/BasicsApplication.cpp ../../src/Photon_lib.cpp ../../src/StdIO_main.cpp ../../src/StdIO_UIListener.cpp Listener.cpp main.cpp

LOCAL_C_INCLUDES := $(PHOTON_SDK_ROOT) ../inc/
LOCAL_CFLAGS := -DEG_DEBUGGER -D__STDINT_LIMITS -D_EG_ANDROID_PLATFORM
LOCAL_STATIC_LIBRARIES := loadbalancing-cpp-static-prebuilt photon-cpp-static-prebuilt common-cpp-static-prebuilt
LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, $(PHOTON_SDK_ROOT)/LoadBalancing-cpp/lib)

$(call import-module,android/native_app_glue)
$(call import-module,loadbalancing-cpp-prebuilt)
