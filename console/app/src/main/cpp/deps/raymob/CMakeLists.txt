# Define a library for raymoblib
add_library(raymoblib STATIC helper.c sensor.c vibrator.c display.c soft_keyboard.c callback.c qcpilot/adaptor.c qcpilot/ui/entry.cpp qcpilot/ui/platform-android.cpp)

# Include headers directory for android_native_app_glue.c
include_directories(${ANDROID_NDK}/sources/android/native_app_glue/ ${CMAKE_SOURCE_DIR}/deps/raymob)

# Add android_native_app_glue.c to the source files
list(APPEND SOURCES ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

# Define compiler macros for the library
target_compile_definitions(raymoblib PRIVATE PLATFORM_ANDROID)

# Include raylib header files
target_include_directories(raymoblib PRIVATE "${CMAKE_SOURCE_DIR}/deps/raylib" "${CMAKE_SOURCE_DIR}/deps")

# Link required libraries to raylib
target_link_libraries(raymoblib raylib)

