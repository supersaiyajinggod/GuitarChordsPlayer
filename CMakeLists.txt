cmake_minimum_required(VERSION 3.10)

project(GuitarChordsPlayer)

set(Qt_COMPONENTS Core Gui Widgets)
set(Qt_LIBRARIES Qt5::Core Qt5::Gui Qt5::Widgets)
find_package(Qt5 REQUIRED COMPONENTS ${Qt_COMPONENTS})

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(HEADER_DIR ${PROJECT_SOURCE_DIR}/include)

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
else()
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb -fpermissive")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -w -fpermissive")

# Check C++17 or C++11 support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX17)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
   add_definitions(-DCOMPILEDWITHC17)
   message(STATUS "Using flag -std=c++17.")
elseif(COMPILER_SUPPORTS_CXX0X)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
   add_definitions(-DCOMPILEDWITHC11)
   message(STATUS "Using flag -std=c++11.")
else()
   message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

include_directories(
   ${HEADER_DIR}
)

link_directories(
)

file (GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp ${SRC_DIR}/*.c)
file (GLOB_RECURSE HEADER_FILES ${HEADER_DIR}/*.h)
file (GLOB_RECURSE UI_FILES ${SRC_DIR}/*.ui)
file (GLOB_RECURSE QRC_SRC_FILES ${SRC_DIR}/*.qrc)

# set(CMAKE_SKIP_RPATH true)
# set(CMAKE_SKIP_BUILD_RPATH true)
# set(CMAKE_SKIP_INSTALL_RPATH true)
#set(CMAKE_EXE_LINKER_FLAGS '-Wl,-rpath=.')

set(CMAKE_INCLUDE_CURRENT_DIR ON)
qt5_wrap_ui(WRAP_FILES ${UI_FILES})
qt5_wrap_cpp(MOC_FILES ${HEADER_FILES})
qt5_add_resources(QRC_FILES ${QRC_SRC_FILES})

# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../bin)

add_executable(${PROJECT_NAME} ${WRAP_FILES} ${MOC_FILES} ${SRC_FILES} ${QRC_FILES})

target_link_libraries(${PROJECT_NAME} 
#    ${OpenCV_LIBRARIES} 
#    ${Boost_LIBRARIES} 
   ${Qt_LIBRARIES}
#    liblz4.so.1 #?
)