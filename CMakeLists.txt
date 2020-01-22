cmake_minimum_required(VERSION 2.8.3)
project(outdoor_navigation)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
  geometry_msgs
  common_srv
  nav_msgs
  genmsg
)

## Generate messages in the 'msg' folder
add_message_files(
  FILES
#  Message1.msg
)

## Generate services in the 'srv' folder
add_service_files(
  FILES

)

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs
  geometry_msgs
  nav_msgs
  common_srv
)


catkin_package(
  INCLUDE_DIRS include
  LIBRARIES
  CATKIN_DEPENDS
    roscpp
    std_msgs
    message_runtime
    geometry_msgs
    common_srv
    nav_msgs
  DEPENDS
    system_lib
)


include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${catkin_INCLUDE_DIRS}
  include
  ${ReactPhysics3D_INCLUDE_DIRS}
  /usr/local/include/reactphysics3d
)


FILE(GLOB SOURCE_FILES *.hpp *.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
add_dependencies(${PROJECT_NAME} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} libreactphysics3d.a)
