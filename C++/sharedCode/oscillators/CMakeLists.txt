add_library(Oscillators oscillator.cpp saw.cpp sine.cpp square.cpp fastSine.cpp
        ../../Effect.h)
target_compile_features(Oscillators PUBLIC cxx_std_20)
target_include_directories(Oscillators PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})