cmake_minimum_required(VERSION 2.8.3)
project(proximal_avoidance)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  sensor_msgs
  pcl_ros
  tf
  std_msgs
  laser_geometry
  pcl_conversions
  urdf

)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend and a run_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependencies might have been
##     pulled in transitively but can be declared for certainty nonetheless:
##     * add a build_depend tag for "message_generation"
##     * add a run_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   sensor_msgs
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES proximal_avoidance
#  CATKIN_DEPENDS roscpp rospy sensor_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Declare a cpp library
# add_library(proximal_avoidance
#   src/${PROJECT_NAME}/proximal_avoidance.cpp
# )

## Declare a cpp executable
# add_executable(proximal_avoidance_node src/proximal_avoidance_node.cpp)
  add_executable(laser_passthrough src/laser_passthrough.cpp)
  add_executable(motor_input src/motor_input.cpp)
  add_executable(error_x src/error_x.cpp)
  add_executable(error_symmetry src/error_symmetry.cpp)
  add_executable(p_controller src/p_controller.cpp)
  add_executable(pi_controller src/pi_controller.cpp)
  add_executable(laser_max_passthrough src/laser_max_passthrough.cpp)
  add_executable(joy_control src/joy_control.cpp)
  add_executable(accu_joy_control src/accu_joy_control.cpp)
  add_executable(urdf_parser src/urdf_parser.cpp)
  add_executable(tf_pub_vrep src/tf_pub_vrep.cpp)
  add_executable(error_test src/error_test.cpp)

## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
# add_dependencies(proximal_avoidance_node proximal_avoidance_generate_messages_cpp)

## Specify libraries to link a library or executable target against
# target_link_libraries(proximal_avoidance_node
#   ${catkin_LIBRARIES}
# )
target_link_libraries(laser_passthrough ${catkin_LIBRARIES})
target_link_libraries(motor_input ${catkin_LIBRARIES})
target_link_libraries(error_x ${catkin_LIBRARIES})
target_link_libraries(error_symmetry ${catkin_LIBRARIES})
target_link_libraries(p_controller ${catkin_LIBRARIES})
target_link_libraries(pi_controller ${catkin_LIBRARIES})
target_link_libraries(laser_max_passthrough ${catkin_LIBRARIES})
target_link_libraries(joy_control ${catkin_LIBRARIES})
target_link_libraries(accu_joy_control ${catkin_LIBRARIES})
target_link_libraries(urdf_parser ${catkin_LIBRARIES})
target_link_libraries(tf_pub_vrep ${catkin_LIBRARIES})
target_link_libraries(error_test ${catkin_LIBRARIES})
#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS proximal_avoidance proximal_avoidance_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_proximal_avoidance.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
