cmake_minimum_required(VERSION 3.27)
project(MinecraftEffect VERSION 0.0.1)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "../cmake/Modules/")
include_directories("include")
add_subdirectory("JUCE")
add_subdirectory("sharedCode")
juce_add_console_app(MinecraftEffect PRODUCT_NAME "MinecraftEffect")
target_sources(MinecraftEffect PRIVATE main.cpp osc.cpp sine.cpp oscillator.cpp wavetableGenerator.cpp saw.cpp square.cpp)
find_package(liblo REQUIRED)
target_compile_definitions(MinecraftEffect PRIVATE JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0)
include_directories(${LIBLO_INCLUDE_DIRS})
target_link_libraries(MinecraftEffect PRIVATE ${LIBLO_LIBRARIES})
target_link_libraries(MinecraftEffect
        PRIVATE
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_audio_processors

        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags
)

target_compile_features(MinecraftEffect PRIVATE cxx_std_20)
