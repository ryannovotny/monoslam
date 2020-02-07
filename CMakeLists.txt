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
set(EIG ${CMAKE_CURRENT_SOURCE_DIR}/Eigen/Eigen)
include_directories(${EIG}/src)
target_sources(MonoSLAM PRIVATE 
	${EIG}/LU
	${EIG}/SuperLUSupport
	${EIG}/Eigenvalues
	${EIG}/IterativeLinearSolvers
	${EIG}/SPQRSupport
	${EIG}/Cholesky
	${EIG}/Dense
	${EIG}/SparseLU
	${EIG}/SparseQR
	${EIG}/PardisoSupport
	${EIG}/StdList
	${EIG}/MetisSupport
	${EIG}/QR
	${EIG}/StdDeque
	${EIG}/Geometry
	${EIG}/Core
	${EIG}/SparseCore
	${EIG}/Householder
	${EIG}/CholmodSupport
	${EIG}/Eigen
	${EIG}/StdVector
	${EIG}/QtAlignedMalloc
	${EIG}/PaStiXSupport
	${EIG}/Sparse
	${EIG}/OrderingMethods
	${EIG}/Jacobi
	${EIG}/SVD
	${EIG}/UmfPackSupport
	${EIG}/SparseCholesky )

## Include Pangolin
#set(EXPORT_Pangolin OFF CACHE BOOL "")
#set(BUILD_EXAMPLES OFF CACHE BOOL "")
#set(BUILD_TESTS OFF CACHE BOOL "")
#set(BUILD_PYPANGOLIN_MODULE OFF CACHE BOOL "")
#add_subdirectory(Pangolin)

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

## Include Pangolin source files
## set(PAN "${CMAKE_CURRENT_SOURCE_DIR}/Pangolin/src")
## target_sources(MonoSLAM PRIVATE ${PAN}/plot/plotter.cpp ${PAN}/plot/datalog.cpp ${PAN}/geometry/geometry_ply.cpp ${PAN}/geometry/glgeometry.cpp ${PAN}/geometry/tinyobj.cpp ${PAN}/geometry/geometry_obj.cpp ${PAN}/geometry/geometry.cpp ${PAN}/display/view.cpp ${PAN}/display/display.cpp ${PAN}/display/window_factory.cpp ${PAN}/display/image_view.cpp ${PAN}/display/device/display_headless.cpp ${PAN}/display/device/display_android.cpp ${PAN}/display/device/display_wayland.cpp ${PAN}/display/device/display_win.cpp ${PAN}/display/device/display_x11.cpp ${PAN}/display/opengl_render_state.cpp ${PAN}/display/viewport.cpp ${PAN}/display/widgets/widgets.cpp ${PAN}/utils/posix/shared_memory_buffer.cpp ${PAN}/utils/posix/semaphore.cpp ${PAN}/utils/posix/condition_variable.cpp ${PAN}/utils/threadedfilebuf.cpp ${PAN}/utils/file_utils.cpp ${PAN}/utils/uri.cpp ${PAN}/utils/sigstate.cpp ${PAN}/utils/timer.cpp ${PAN}/utils/file_extension.cpp ${PAN}/console/ConsoleView.cpp ${PAN}/image/image_io_exr.cpp ${PAN}/image/image_io_tga.cpp ${PAN}/image/image_io_packed12bit.cpp ${PAN}/image/image_io_raw.cpp ${PAN}/image/image_io.cpp ${PAN}/image/image_io_png.cpp ${PAN}/image/image_io_jpg.cpp ${PAN}/image/image_io_zstd.cpp ${PAN}/image/image_io_pango.cpp ${PAN}/image/pixel_format.cpp ${PAN}/image/image_io_ppm.cpp ${PAN}/image/image_io_lz4.cpp ${PAN}/handler/handler_image.cpp ${PAN}/handler/handler.cpp ${PAN}/handler/handler_glbuffer.cpp ${PAN}/log/packetstream_reader.cpp ${PAN}/log/packetstream.cpp ${PAN}/log/packet.cpp ${PAN}/log/packetstream_writer.cpp ${PAN}/log/playback_session.cpp ${PAN}/gl/glfont.cpp ${PAN}/gl/glchar.cpp ${PAN}/gl/gltext.cpp ${PAN}/gl/gltexturecache.cpp ${PAN}/gl/compat/gl2engine.cpp ${PAN}/gl/glpangoglu.cpp ${PAN}/gl/gldraw.cpp ${PAN}/tools/video_viewer.cpp ${PAN}/var/input_record_repeat.cpp ${PAN}/var/vars.cpp ${PAN}/video/video_output_interface_factory.cpp ${PAN}/video/video_input.cpp ${PAN}/video/stream_encoder_factory.cpp ${PAN}/video/video_output.cpp ${PAN}/video/video_interface_factory.cpp ${PAN}/video/drivers/v4l.cpp ${PAN}/video/drivers/thread.cpp ${PAN}/video/drivers/realsense2.cpp ${PAN}/video/drivers/deinterlace.cpp ${PAN}/video/drivers/images_out.cpp ${PAN}/video/drivers/firewire.cpp ${PAN}/video/drivers/shared_memory.cpp ${PAN}/video/drivers/unpack.cpp ${PAN}/video/drivers/mirror.cpp ${PAN}/video/drivers/test.cpp ${PAN}/video/drivers/pleora.cpp ${PAN}/video/drivers/uvc.cpp ${PAN}/video/drivers/join.cpp ${PAN}/video/drivers/pvn.cpp ${PAN}/video/drivers/debayer.cpp ${PAN}/video/drivers/images.cpp ${PAN}/video/drivers/openni2.cpp ${PAN}/video/drivers/merge.cpp ${PAN}/video/drivers/truncate.cpp ${PAN}/video/drivers/depthsense.cpp ${PAN}/video/drivers/uvc_mediafoundation.cpp ${PAN}/video/drivers/realsense.cpp ${PAN}/video/drivers/openni.cpp ${PAN}/video/drivers/pango_video_output.cpp ${PAN}/video/drivers/pack.cpp ${PAN}/video/drivers/split.cpp ${PAN}/video/drivers/json.cpp ${PAN}/video/drivers/teli.cpp ${PAN}/video/drivers/pango.cpp ${PAN}/video/drivers/shift.cpp ${PAN}/video/drivers/ffmpeg.cpp ${PAN}/video/video.cpp)

## Include SceneLib2 source files
## set(SCE "${CMAKE_CURRENT_SOURCE_DIR}/SceneLib2/scenelib2")
## target_sources(MonoSLAM PRIVATE ${SCE}/motion_model.cpp ${SCE}/camera.cpp ${SCE}/graphic/graphictool.cpp ${SCE}/support/eigen_util.cpp ${SCE}/support/pangolin_util.cpp ${SCE}/support/math_util.cpp ${SCE}/improc/improc.cpp ${SCE}/improc/search_multiple_overlapping_ellipses.cpp ${SCE}/feature.cpp ${SCE}/kalman.cpp ${SCE}/full_feature_model.cpp ${SCE}/feature_init_info.cpp ${SCE}/feature_model.cpp ${SCE}/framegrabber/filegrabber.cpp ${SCE}/framegrabber/framegrabber.cpp ${SCE}/framegrabber/usbcamgrabber.cpp ${SCE}/monoslam.cpp ${SCE}/part_feature_model.cpp)

## Add any link libraries for each module. Add 'jevoisbase' here if you want to link against it:
target_link_libraries(MonoSLAM ${JEVOIS_OPENCV_LIBS} opencv_imgproc opencv_core)

## Install any shared resources (cascade classifiers, neural network weights, etc) in the share/ sub-directory:
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/share"
  DESTINATION "${JEVOIS_INSTALL_ROOT}" COMPONENT bin)

## Wrapping up:
jevois_project_finalize()  # call this last in your CMakeLists.txt, will un-mount the live microSD if applicable
