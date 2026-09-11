# SPDX-License-Identifier: Apache-2.0
# Copyright 2026, Ne.app. All rights reserved
# Official repository: https://github.com/ne-app/adb

cmake_minimum_required(VERSION 3.25.1)

project(ADB DESCRIPTION "The ADB SDK in modern C++" HOMEPAGE_URL "docs.adb.nekernel.org")

set(CMAKE_CXX_STANDARD 23)

find_package(Boost REQUIRED)
find_package(TBB REQUIRED)
find_package(GTK REQUIRED)

if (NOT DEFINED CMAKE_HOST_WIN32)
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(JSC REQUIRED javascriptcoregtk-4.1)
  pkg_check_modules(GTK REQUIRED gtk4)
  pkg_check_modules(WGTK REQUIRED webkit2gtk-4.1)
endif()

set(NEAPP_ADB_SOURCES
  src/ne_app/app/pdf.viewer.cpp
  src/ne_app/app/html.viewer.cpp
  src/ne_app/quickstart.cpp
  src/ne_app/pdf.cpp
  src/ne_app/store.cpp
)

add_library(ADB SHARED ${NEAPP_ADB_SOURCES})

set_target_properties(ADB PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

if (NOT DEFINED CMAKE_HOST_WIN32)
  target_include_directories(ADB PUBLIC include/ ${JSC_INCLUDE_DIRS} 
                            ${WGTK_INCLUDE_DIRS} ${GTK_INCLUDE_DIRS})
  target_link_libraries(ADB ${JSC_LIBRARIES} ${WGTK_LIBRARIES} ${GTK_LIBRARIES})
else()
  target_include_directories(ADB PUBLIC include/ ${OCL_INSTALL_DIR})
  target_include_directories(ADB PUBLIC include/ ${BOOST_INSTALL_DIR})
endif()

if (DEFINED NEAPP_INSTALL_ADB)
  install(DIRECTORY include/ne_app DESTINATION include)
  install_targets(llib ADB)
endif()
