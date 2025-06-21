LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := weikton
LOCAL_LDLIBS := -llog

# path
FILE_LIST := $(wildcard $(LOCAL_PATH)/*.cpp)
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_CPPFLAGS := -w -s -fvisibility=hidden -pthread -Wall -fpack-struct=1 -O2 -std=c++14 -fexceptions
LOCAL_CFLAGS := -Wall -D__MODULE__=\"$(LOCAL_MODULE)\" -fcommon -mllvm -fla -mllvm -bcf -mllvm -sub -mllvm -sobf
LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv2
include $(BUILD_SHARED_LIBRARY)