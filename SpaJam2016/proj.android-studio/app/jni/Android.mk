#--------------------------------------------------------
LOCAL_PATH := $(call my-dir)

#Photon
PHOTON_SDK_ROOT := $(LOCAL_PATH)/../../../Photon-SDK/Android


#--------------------------------------------------------
include $(CLEAR_VARS)


$(call import-add-path, $(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path, $(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path, $(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path, $(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

#Photon
#$(call import-add-path, $(PHOTON_SDK_ROOT)/Chat-cpp/lib)
$(call import-add-path, $(PHOTON_SDK_ROOT)/Common-cpp/lib)
$(call import-add-path, $(PHOTON_SDK_ROOT)/LoadBalancing-cpp/lib)
$(call import-add-path, $(PHOTON_SDK_ROOT)/Photon-cpp/lib)


#--------------------------------------------------------
LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame


#--------------------------------------------------------
LOCAL_SRC_FILES := hellocpp/main.cpp 

CPP_FILES := $(shell find $(LOCAL_PATH)/../../../Classes -name *.cpp)
LOCAL_SRC_FILES += $(CPP_FILES:$(LOCAL_PATH)/%=%)


LOCAL_C_INCLUDES := $(shell find $(LOCAL_PATH)/../../../Classes -type d)

#Photon
LOCAL_C_INCLUDES += $(PHOTON_SDK_ROOT)


# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


#--------------------------------------------------------
LOCAL_STATIC_LIBRARIES := cocos2dx_static

#Photon
LOCAL_STATIC_LIBRARIES += loadbalancing-cpp-static-prebuilt
LOCAL_STATIC_LIBRARIES += photon-cpp-static-prebuilt
LOCAL_STATIC_LIBRARIES += common-cpp-static-prebuilt

#Photon
LOCAL_CFLAGS := -DEG_DEBUGGER -D__STDINT_LIMITS -D_EG_ANDROID_PLATFORM
LOCAL_LDLIBS := -llog


# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END


#--------------------------------------------------------
include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

#Photon
#$(call import-module, chat-cpp-prebuilt)
$(call import-module, common-cpp-prebuilt)
$(call import-module, loadbalancing-cpp-prebuilt)
$(call import-module, photon-cpp-prebuilt)


# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
