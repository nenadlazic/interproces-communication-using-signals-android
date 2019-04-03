LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS += -DMODULE_DIAGNOTICS_ENABLE

LOCAL_SRC_FILES:= native_test_signal_handler.c
		
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog

LOCAL_MODULE := signal_handler_test

include $(BUILD_MAKE)/crules.mak

include $(BUILD_EXECUTABLE)
