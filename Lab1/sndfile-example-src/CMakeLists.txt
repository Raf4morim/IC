cmake_minimum_required(VERSION 3.16)
project(sndfile-example)

SET (CMAKE_BUILD_TYPE "Release")
#SET (CMAKE_BUILD_TYPE "Debug")

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++17")
SET (CMAKE_CXX_FLAGS_RELEASE "-O3")
SET (CMAKE_CXX_FLAGS_DEBUG "-g3 -fsanitize=address")

SET (BASE_DIR ${CMAKE_SOURCE_DIR} )
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BASE_DIR}/../sndfile-example-bin)

add_executable (wav_cp wav_cp.cpp)
target_link_libraries (wav_cp sndfile)
# exc2
add_executable (wav_hist wav_hist.cpp)
target_link_libraries (wav_hist sndfile)

add_executable (wav_dct wav_dct.cpp)
target_link_libraries (wav_dct sndfile fftw3)

add_executable (wav_quant wav_quant.cpp)
target_link_libraries (wav_quant sndfile)

add_executable (wav_cmp wav_cmp.cpp)
target_link_libraries (wav_cmp sndfile)

add_executable(wav_effects wav_effects.cpp)
target_link_libraries(wav_effects sndfile)

add_executable(encoder encoder.cpp)
target_link_libraries(encoder sndfile)

add_executable(decoder decoder.cpp)
target_link_libraries(decoder sndfile)

# add_executable(lossyE lossyE.cpp)
# target_link_libraries(lossyE sndfile)

# add_executable(lossyD lossyD.cpp)
# target_link_libraries(lossyD sndfile)
