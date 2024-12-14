LOCAL_PATH := $(call my-dir)

# Untuk armeabi-v7a
ifeq ($(TARGET_ARCH_ABI), armeabi-v7a)
include $(CLEAR_VARS)

LOCAL_MODULE := sock
LOCAL_SRC_FILES := Kamid.cpp
LOCAL_C_INCLUDES += $(LOCAL_PATH)

LOCAL_CFLAGS := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w
LOCAL_CFLAGS += -fno-rtti -fno-exceptions -fpermissive
LOCAL_CPPFLAGS := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w -Werror -s -std=c++17
LOCAL_CPPFLAGS += -Wno-error=c++11-narrowing -fms-extensions -fno-rtti -fno-exceptions -fpermissive
LOCAL_LDFLAGS += -Wl,--gc-sections,--strip-all, -llog
LOCAL_ARM_MODE := arm

LOCAL_LDFLAGS += -Wl,--gc-sections
LOCAL_LDFLAGS += -L$(SYSROOT)/usr/lib -lz -llog

include $(BUILD_EXECUTABLE)
endif

# Untuk arm64-v8a
ifeq ($(TARGET_ARCH_ABI), arm64-v8a)
include $(CLEAR_VARS)

LOCAL_MODULE := sock64
LOCAL_SRC_FILES := Kamid64.cpp
LOCAL_C_INCLUDES += $(LOCAL_PATH)

LOCAL_CFLAGS := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w
LOCAL_CFLAGS += -fno-rtti -fno-exceptions -fpermissive
LOCAL_CPPFLAGS := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w -Werror -s -std=c++17
LOCAL_CPPFLAGS += -Wno-error=c++11-narrowing -fms-extensions -fno-rtti -fno-exceptions -fpermissive
LOCAL_LDFLAGS += -Wl,--gc-sections,--strip-all, -llog

LOCAL_LDFLAGS += -Wl,--gc-sections
LOCAL_LDFLAGS += -L$(SYSROOT)/usr/lib -lz -llog

include $(BUILD_EXECUTABLE)
endif
