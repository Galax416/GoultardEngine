# Install script for directory: /home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libassimp5.2.5" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.5.2.5"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.5"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/bin/libassimp.so.5.2.5"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/bin/libassimp.so.5"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.5.2.5"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.5"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libassimp5.2.5" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/bin/libassimp.so")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/anim.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/aabb.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/ai_assert.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/camera.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/color4.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/color4.inl"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/config.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/ColladaMetaData.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/commonMetaData.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/defs.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/cfileio.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/light.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/material.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/material.inl"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/matrix3x3.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/matrix3x3.inl"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/matrix4x4.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/matrix4x4.inl"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/mesh.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/ObjMaterial.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/pbrmaterial.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/GltfMaterial.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/postprocess.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/quaternion.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/quaternion.inl"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/scene.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/metadata.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/texture.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/types.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/vector2.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/vector2.inl"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/vector3.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/vector3.inl"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/version.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/cimport.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/importerdesc.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/Importer.hpp"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/DefaultLogger.hpp"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/ProgressHandler.hpp"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/IOStream.hpp"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/IOSystem.hpp"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/Logger.hpp"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/LogStream.hpp"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/NullLogger.hpp"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/cexport.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/Exporter.hpp"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/DefaultIOStream.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/DefaultIOSystem.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/ZipArchiveIOSystem.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/SceneCombiner.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/fast_atof.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/qnan.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/BaseImporter.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/Hash.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/MemoryIOWrapper.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/ParsingUtils.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/StreamReader.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/StreamWriter.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/StringComparison.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/StringUtils.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/SGSpatialSort.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/GenericProperty.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/SpatialSort.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/SkeletonMeshBuilder.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/SmallVector.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/SmoothingGroups.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/SmoothingGroups.inl"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/StandardShapes.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/RemoveComments.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/Subdivision.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/Vertex.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/LineSplitter.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/TinyFormatter.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/Profiler.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/LogAux.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/Bitmap.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/XMLTools.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/IOStreamBuffer.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/CreateAnimMesh.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/XmlParser.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/BlobIOSystem.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/MathFunctions.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/Exceptional.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/ByteSwapper.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/Base64.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/Compiler/pushpack1.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/Compiler/poppack1.h"
    "/home/galax/Desktop/Projet-Moteur-de-Jeux/external/assimp/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

