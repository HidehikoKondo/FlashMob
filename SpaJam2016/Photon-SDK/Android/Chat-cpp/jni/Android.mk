# Generated by VisualGDB

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := chat-cpp-static
#VisualGDBAndroid: AutoUpdateSourcesInNextLine
LOCAL_SRC_FILES := ../src/AuthenticationValues.cpp ../src/Channel.cpp ../src/Client.cpp ../src/Internal/AuthenticationValuesSecretSetter.cpp ../src/Internal/ChannelFactory.cpp ../src/Internal/ChannelMessageAdder.cpp ../src/Peer.cpp
LOCAL_C_INCLUDES := ..
LOCAL_CFLAGS := 
include $(BUILD_STATIC_LIBRARY)

all: lib/chat-cpp-prebuilt/libchat-cpp-static_${APP_OPTIM}_android_$(TARGET_ARCH_ABI)$(MY_APP_NORTTI_SUFFIX).a
lib/chat-cpp-prebuilt/libchat-cpp-static_${APP_OPTIM}_android_$(TARGET_ARCH_ABI)$(MY_APP_NORTTI_SUFFIX).a : $(LOCAL_BUILT_MODULE)
	cp $< $@


include $(CLEAR_VARS)
LOCAL_MODULE := photon-cpp-static-prebuilt
LOCAL_SRC_FILES := ../../Photon-cpp/obj/local/$(TARGET_ARCH_ABI)/libphoton-cpp-static.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)../../../Photon-cpp/jni
include $(PREBUILT_STATIC_LIBRARY)
