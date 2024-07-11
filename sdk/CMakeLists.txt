################################################################################
# Set minimum required version of cmake, project name and compile options
################################################################################
cmake_minimum_required(VERSION 3.5)
project(rplidar_sdk)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if(MSVC)
  add_compile_definitions(
    _USE_MATH_DEFINES
  )
endif()

set(SLLIDAR_SDK_PATH ".")

FILE(GLOB SLLIDAR_SDK_SRC 
  "${SLLIDAR_SDK_PATH}/src/arch/linux/*.cpp"
  "${SLLIDAR_SDK_PATH}/src/hal/*.cpp"
  "${SLLIDAR_SDK_PATH}/src/*.cpp"
  "${SLLIDAR_SDK_PATH}/src/dataunpacker/*.cpp"
  "${SLLIDAR_SDK_PATH}/src/dataunpacker/unpacker/*.cpp"
)

################################################################################
# Build
################################################################################
include_directories(
  ${SLLIDAR_SDK_PATH}/include
  ${SLLIDAR_SDK_PATH}/src
  ${Boost_INCLUDE_DIRS}
)

add_library(rplidar_sdk SHARED src/rplidar_python_interface.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER include/rplidar_python_interface.h)