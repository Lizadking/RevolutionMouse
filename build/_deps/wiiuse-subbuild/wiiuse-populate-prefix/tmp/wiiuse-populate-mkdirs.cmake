# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/run/media/lizadking/Programming/RevolutionMouse/build/_deps/wiiuse-src")
  file(MAKE_DIRECTORY "/run/media/lizadking/Programming/RevolutionMouse/build/_deps/wiiuse-src")
endif()
file(MAKE_DIRECTORY
  "/run/media/lizadking/Programming/RevolutionMouse/build/_deps/wiiuse-build"
  "/run/media/lizadking/Programming/RevolutionMouse/build/_deps/wiiuse-subbuild/wiiuse-populate-prefix"
  "/run/media/lizadking/Programming/RevolutionMouse/build/_deps/wiiuse-subbuild/wiiuse-populate-prefix/tmp"
  "/run/media/lizadking/Programming/RevolutionMouse/build/_deps/wiiuse-subbuild/wiiuse-populate-prefix/src/wiiuse-populate-stamp"
  "/run/media/lizadking/Programming/RevolutionMouse/build/_deps/wiiuse-subbuild/wiiuse-populate-prefix/src"
  "/run/media/lizadking/Programming/RevolutionMouse/build/_deps/wiiuse-subbuild/wiiuse-populate-prefix/src/wiiuse-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/run/media/lizadking/Programming/RevolutionMouse/build/_deps/wiiuse-subbuild/wiiuse-populate-prefix/src/wiiuse-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/run/media/lizadking/Programming/RevolutionMouse/build/_deps/wiiuse-subbuild/wiiuse-populate-prefix/src/wiiuse-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
