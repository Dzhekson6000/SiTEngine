LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

SIT_PATH := /../..

LOCAL_MODULE    := libSiT
LOCAL_SRC_FILES := Application.cpp \
GLViewImpl.cpp \
FileUtilsImpl.cpp \
$(SIT_PATH)/Macros.cpp \
$(SIT_PATH)/Director.cpp \
$(SIT_PATH)/Base/Node.cpp \
$(SIT_PATH)/Base/PoolManager.cpp \
$(SIT_PATH)/Base/Ref.cpp \
$(SIT_PATH)/Base/Scene.cpp \
$(SIT_PATH)/Events/Event.cpp \
$(SIT_PATH)/Events/Events.cpp \
$(SIT_PATH)/Events/EventTouch.cpp \
$(SIT_PATH)/external/math_3d.cpp \
$(SIT_PATH)/Geometry/Rotate.cpp \
$(SIT_PATH)/Geometry/Scale.cpp \
$(SIT_PATH)/Geometry/Size.cpp \
$(SIT_PATH)/Graphics/GLView.cpp \
$(SIT_PATH)/Graphics/2d/Sprite.cpp \
$(SIT_PATH)/Graphics/Render/Renderer.cpp \
$(SIT_PATH)/Graphics/Render/Command/CustomCommand.cpp \
$(SIT_PATH)/Graphics/Render/Command/RenderCommand.cpp \
$(SIT_PATH)/Graphics/Shader/Shaders.cpp \
$(SIT_PATH)/Graphics/Shader/ShaderManager.cpp \
$(SIT_PATH)/Graphics/Shader/Shader.cpp \
$(SIT_PATH)/Resource/ResourceHandle.cpp \
$(SIT_PATH)/Resource/ResourceManager.cpp \
$(SIT_PATH)/Resource/Data.cpp \
$(SIT_PATH)/Resource/FileUtils.cpp \
$(SIT_PATH)/Resource/Image.cpp \
$(SIT_PATH)/Resource/Texture.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/.. \
                    $(LOCAL_PATH)/../.. \
					$(LOCAL_PATH)/../../SiT/external/jpeg/prebuilt/android/ \
					$(LOCAL_PATH)/../../SiT/external/png/prebuilt/android/ \

LOCAL_LDLIBS    := -llog -lGLESv2

LOCAL_CPPFLAGS := -Wno-extern-c-compat

LOCAL_EXPORT_CPPFLAGS := -Wno-extern-c-compat

include $(BUILD_STATIC_LIBRARY)
