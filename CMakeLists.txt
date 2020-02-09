######################################################################################################################
#
# JeVois Smart Embedded Machine Vision Toolkit - Copyright (C) 2016 by Laurent Itti, the University of Southern
# California (USC), and iLab at USC. See http://iLab.usc.edu and http://jevois.org for information about this project.
#
# This file is part of the JeVois Smart Embedded Machine Vision Toolkit.  This program is free software; you can
# redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software
# Foundation, version 2.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
# without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
# License for more details.  You should have received a copy of the GNU General Public License along with this program;
# if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
#
# Contact information: Laurent Itti - 3641 Watt Way, HNB-07A - Los Angeles, BA 90089-2520 - USA.
# Tel: +1 213 740 3527 - itti@pollux.usc.edu - http://iLab.usc.edu - http://jevois.org
######################################################################################################################

## CMake build rules for JeVois Base library and executables

## You may provide the installed JeVois config root as:
#   cmake -DJEVOIS_CONFIG=/jevois/config ..

cmake_minimum_required(VERSION 3.1)

## Set vendor names, our modules will be placed in a directory by that name under /jevois/modules:
set(JEVOIS_VENDOR "JeVois")
set(JEVOIS_CONFIG "/jevois/config" CACHE STRING "Path to JeVois config to use")

## Include helper functions, config, etc from the JeVois install:
set(CMAKE_MODULE_PATH ${JEVOIS_CONFIG})
include(jevois_config)
include(JeVois)

## Set project name, detects compiler (which has been set by our helper module). Then set some complation flags:
project(monoslam)
jevois_project_set_flags()
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

## Setup our modules that are in src/Modules:
jevois_setup_modules(src/Modules "")

## Include Eigen
# Fix path assumptions in the optical flow code for Eigen:
if (JEVOIS_PLATFORM)
  add_definitions(-I${JEVOIS_BUILDROOT_BASE}/host/usr/arm-buildroot-linux-gnueabihf/sysroot/usr/include/eigen3)
else (JEVOIS_PLATFORM)
  add_definitions(-I/usr/include/eigen3)
endif (JEVOIS_PLATFORM)

## Include Pangolin
set(BUILD_EXAMPLES OFF CACHE BOOL "Build Tools" FORCE)
set(BUILD_TESTS OFF CACHE BOOL "Build Tests" FORCE)
set(BUILD_PYPANGOLIN_MODULE OFF CACHE BOOL "" FORCE)
set(BUILD_PANGOLIN_GUI OFF CACHE BOOL "Build support for Pangolin GUI" FORCE)

add_subdirectory("Pangolin")

## Include SceneLib2
set(SCE ${CMAKE_CURRENT_SOURCE_DIR}/SceneLib2/scenelib2)
include_directories(SceneLib2/scenelib2
	SceneLib2/scenelib2/framegrabber
	SceneLib2/scenelib2/graphic
	SceneLib2/scenelib2/improc
	SceneLib2/scenelib2/support)
target_sources(MonoSLAM PRIVATE
	${SCE}/motion_model.cpp
	${SCE}/camera.cpp
	${SCE}/graphic/graphictool.cpp
	${SCE}/support/eigen_util.cpp
	${SCE}/support/pangolin_util.cpp
	${SCE}/support/math_util.cpp
	${SCE}/improc/improc.cpp
	${SCE}/improc/search_multiple_overlapping_ellipses.cpp
	${SCE}/feature.cpp
	${SCE}/kalman.cpp
	${SCE}/full_feature_model.cpp
	${SCE}/feature_init_info.cpp
	${SCE}/feature_model.cpp
	${SCE}/framegrabber/filegrabber.cpp
	${SCE}/framegrabber/framegrabber.cpp
	${SCE}/framegrabber/usbcamgrabber.cpp
	${SCE}/monoslam.cpp
	${SCE}/part_feature_model.cpp
)

## Add any link libraries for each module. Add 'jevoisbase' here if you want to link against it:
target_link_libraries(MonoSLAM ${JEVOIS_OPENCV_LIBS} opencv_imgproc opencv_core)

## Install any shared resources (cascade classifiers, neural network weights, etc) in the share/ sub-directory:
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/share"
  DESTINATION "${JEVOIS_INSTALL_ROOT}" COMPONENT bin)

## Wrapping up:
jevois_project_finalize()  # call this last in your CMakeLists.txt, will un-mount the live microSD if applicable
