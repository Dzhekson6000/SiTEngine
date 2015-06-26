LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

CLASSES_PATH:= /../../Classes/

$(call import-add-path,$(LOCAL_PATH)/../../SiT/Platform/Android)

LOCAL_WHOLE_STATIC_LIBRARIES := libSiT

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/.. \
                    $(LOCAL_PATH)/../../Classes/ \
					$(LOCAL_PATH)/../../SiT/ \
					

LOCAL_MODULE    := libSiTcpp
LOCAL_SRC_FILES := main.cpp \
$(CLASSES_PATH)AppDelegate.cpp

LOCAL_CFLAGS    := -Werror
LOCAL_LDLIBS    := -llog -lGLESv2 -landroid

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)