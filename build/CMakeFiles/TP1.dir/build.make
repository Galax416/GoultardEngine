# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/galax/Desktop/Projet-Moteur-de-Jeux

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/galax/Desktop/Projet-Moteur-de-Jeux/build

# Include any dependencies generated for this target.
include CMakeFiles/TP1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/TP1.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TP1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TP1.dir/flags.make

CMakeFiles/TP1.dir/TP1/TP1.cpp.o: CMakeFiles/TP1.dir/flags.make
CMakeFiles/TP1.dir/TP1/TP1.cpp.o: /home/galax/Desktop/Projet-Moteur-de-Jeux/TP1/TP1.cpp
CMakeFiles/TP1.dir/TP1/TP1.cpp.o: CMakeFiles/TP1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/galax/Desktop/Projet-Moteur-de-Jeux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TP1.dir/TP1/TP1.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP1.dir/TP1/TP1.cpp.o -MF CMakeFiles/TP1.dir/TP1/TP1.cpp.o.d -o CMakeFiles/TP1.dir/TP1/TP1.cpp.o -c /home/galax/Desktop/Projet-Moteur-de-Jeux/TP1/TP1.cpp

CMakeFiles/TP1.dir/TP1/TP1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TP1.dir/TP1/TP1.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/galax/Desktop/Projet-Moteur-de-Jeux/TP1/TP1.cpp > CMakeFiles/TP1.dir/TP1/TP1.cpp.i

CMakeFiles/TP1.dir/TP1/TP1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TP1.dir/TP1/TP1.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/galax/Desktop/Projet-Moteur-de-Jeux/TP1/TP1.cpp -o CMakeFiles/TP1.dir/TP1/TP1.cpp.s

CMakeFiles/TP1.dir/common/shader.cpp.o: CMakeFiles/TP1.dir/flags.make
CMakeFiles/TP1.dir/common/shader.cpp.o: /home/galax/Desktop/Projet-Moteur-de-Jeux/common/shader.cpp
CMakeFiles/TP1.dir/common/shader.cpp.o: CMakeFiles/TP1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/galax/Desktop/Projet-Moteur-de-Jeux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TP1.dir/common/shader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP1.dir/common/shader.cpp.o -MF CMakeFiles/TP1.dir/common/shader.cpp.o.d -o CMakeFiles/TP1.dir/common/shader.cpp.o -c /home/galax/Desktop/Projet-Moteur-de-Jeux/common/shader.cpp

CMakeFiles/TP1.dir/common/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TP1.dir/common/shader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/galax/Desktop/Projet-Moteur-de-Jeux/common/shader.cpp > CMakeFiles/TP1.dir/common/shader.cpp.i

CMakeFiles/TP1.dir/common/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TP1.dir/common/shader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/galax/Desktop/Projet-Moteur-de-Jeux/common/shader.cpp -o CMakeFiles/TP1.dir/common/shader.cpp.s

CMakeFiles/TP1.dir/common/controls.cpp.o: CMakeFiles/TP1.dir/flags.make
CMakeFiles/TP1.dir/common/controls.cpp.o: /home/galax/Desktop/Projet-Moteur-de-Jeux/common/controls.cpp
CMakeFiles/TP1.dir/common/controls.cpp.o: CMakeFiles/TP1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/galax/Desktop/Projet-Moteur-de-Jeux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/TP1.dir/common/controls.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP1.dir/common/controls.cpp.o -MF CMakeFiles/TP1.dir/common/controls.cpp.o.d -o CMakeFiles/TP1.dir/common/controls.cpp.o -c /home/galax/Desktop/Projet-Moteur-de-Jeux/common/controls.cpp

CMakeFiles/TP1.dir/common/controls.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TP1.dir/common/controls.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/galax/Desktop/Projet-Moteur-de-Jeux/common/controls.cpp > CMakeFiles/TP1.dir/common/controls.cpp.i

CMakeFiles/TP1.dir/common/controls.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TP1.dir/common/controls.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/galax/Desktop/Projet-Moteur-de-Jeux/common/controls.cpp -o CMakeFiles/TP1.dir/common/controls.cpp.s

CMakeFiles/TP1.dir/common/texture.cpp.o: CMakeFiles/TP1.dir/flags.make
CMakeFiles/TP1.dir/common/texture.cpp.o: /home/galax/Desktop/Projet-Moteur-de-Jeux/common/texture.cpp
CMakeFiles/TP1.dir/common/texture.cpp.o: CMakeFiles/TP1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/galax/Desktop/Projet-Moteur-de-Jeux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/TP1.dir/common/texture.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP1.dir/common/texture.cpp.o -MF CMakeFiles/TP1.dir/common/texture.cpp.o.d -o CMakeFiles/TP1.dir/common/texture.cpp.o -c /home/galax/Desktop/Projet-Moteur-de-Jeux/common/texture.cpp

CMakeFiles/TP1.dir/common/texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TP1.dir/common/texture.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/galax/Desktop/Projet-Moteur-de-Jeux/common/texture.cpp > CMakeFiles/TP1.dir/common/texture.cpp.i

CMakeFiles/TP1.dir/common/texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TP1.dir/common/texture.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/galax/Desktop/Projet-Moteur-de-Jeux/common/texture.cpp -o CMakeFiles/TP1.dir/common/texture.cpp.s

CMakeFiles/TP1.dir/common/stb_image.cpp.o: CMakeFiles/TP1.dir/flags.make
CMakeFiles/TP1.dir/common/stb_image.cpp.o: /home/galax/Desktop/Projet-Moteur-de-Jeux/common/stb_image.cpp
CMakeFiles/TP1.dir/common/stb_image.cpp.o: CMakeFiles/TP1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/galax/Desktop/Projet-Moteur-de-Jeux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/TP1.dir/common/stb_image.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP1.dir/common/stb_image.cpp.o -MF CMakeFiles/TP1.dir/common/stb_image.cpp.o.d -o CMakeFiles/TP1.dir/common/stb_image.cpp.o -c /home/galax/Desktop/Projet-Moteur-de-Jeux/common/stb_image.cpp

CMakeFiles/TP1.dir/common/stb_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TP1.dir/common/stb_image.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/galax/Desktop/Projet-Moteur-de-Jeux/common/stb_image.cpp > CMakeFiles/TP1.dir/common/stb_image.cpp.i

CMakeFiles/TP1.dir/common/stb_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TP1.dir/common/stb_image.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/galax/Desktop/Projet-Moteur-de-Jeux/common/stb_image.cpp -o CMakeFiles/TP1.dir/common/stb_image.cpp.s

CMakeFiles/TP1.dir/common/objloader.cpp.o: CMakeFiles/TP1.dir/flags.make
CMakeFiles/TP1.dir/common/objloader.cpp.o: /home/galax/Desktop/Projet-Moteur-de-Jeux/common/objloader.cpp
CMakeFiles/TP1.dir/common/objloader.cpp.o: CMakeFiles/TP1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/galax/Desktop/Projet-Moteur-de-Jeux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/TP1.dir/common/objloader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP1.dir/common/objloader.cpp.o -MF CMakeFiles/TP1.dir/common/objloader.cpp.o.d -o CMakeFiles/TP1.dir/common/objloader.cpp.o -c /home/galax/Desktop/Projet-Moteur-de-Jeux/common/objloader.cpp

CMakeFiles/TP1.dir/common/objloader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TP1.dir/common/objloader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/galax/Desktop/Projet-Moteur-de-Jeux/common/objloader.cpp > CMakeFiles/TP1.dir/common/objloader.cpp.i

CMakeFiles/TP1.dir/common/objloader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TP1.dir/common/objloader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/galax/Desktop/Projet-Moteur-de-Jeux/common/objloader.cpp -o CMakeFiles/TP1.dir/common/objloader.cpp.s

CMakeFiles/TP1.dir/common/vboindexer.cpp.o: CMakeFiles/TP1.dir/flags.make
CMakeFiles/TP1.dir/common/vboindexer.cpp.o: /home/galax/Desktop/Projet-Moteur-de-Jeux/common/vboindexer.cpp
CMakeFiles/TP1.dir/common/vboindexer.cpp.o: CMakeFiles/TP1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/galax/Desktop/Projet-Moteur-de-Jeux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/TP1.dir/common/vboindexer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP1.dir/common/vboindexer.cpp.o -MF CMakeFiles/TP1.dir/common/vboindexer.cpp.o.d -o CMakeFiles/TP1.dir/common/vboindexer.cpp.o -c /home/galax/Desktop/Projet-Moteur-de-Jeux/common/vboindexer.cpp

CMakeFiles/TP1.dir/common/vboindexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TP1.dir/common/vboindexer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/galax/Desktop/Projet-Moteur-de-Jeux/common/vboindexer.cpp > CMakeFiles/TP1.dir/common/vboindexer.cpp.i

CMakeFiles/TP1.dir/common/vboindexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TP1.dir/common/vboindexer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/galax/Desktop/Projet-Moteur-de-Jeux/common/vboindexer.cpp -o CMakeFiles/TP1.dir/common/vboindexer.cpp.s

# Object files for target TP1
TP1_OBJECTS = \
"CMakeFiles/TP1.dir/TP1/TP1.cpp.o" \
"CMakeFiles/TP1.dir/common/shader.cpp.o" \
"CMakeFiles/TP1.dir/common/controls.cpp.o" \
"CMakeFiles/TP1.dir/common/texture.cpp.o" \
"CMakeFiles/TP1.dir/common/stb_image.cpp.o" \
"CMakeFiles/TP1.dir/common/objloader.cpp.o" \
"CMakeFiles/TP1.dir/common/vboindexer.cpp.o"

# External object files for target TP1
TP1_EXTERNAL_OBJECTS =

TP1: CMakeFiles/TP1.dir/TP1/TP1.cpp.o
TP1: CMakeFiles/TP1.dir/common/shader.cpp.o
TP1: CMakeFiles/TP1.dir/common/controls.cpp.o
TP1: CMakeFiles/TP1.dir/common/texture.cpp.o
TP1: CMakeFiles/TP1.dir/common/stb_image.cpp.o
TP1: CMakeFiles/TP1.dir/common/objloader.cpp.o
TP1: CMakeFiles/TP1.dir/common/vboindexer.cpp.o
TP1: CMakeFiles/TP1.dir/build.make
TP1: /usr/lib/x86_64-linux-gnu/libGL.so
TP1: /usr/lib/x86_64-linux-gnu/libGLU.so
TP1: external/glfw-3.1.2/src/libglfw3.a
TP1: external/libGLEW_1130.a
TP1: /usr/lib/x86_64-linux-gnu/librt.a
TP1: /usr/lib/x86_64-linux-gnu/libm.so
TP1: /usr/lib/x86_64-linux-gnu/libX11.so
TP1: /usr/lib/x86_64-linux-gnu/libXrandr.so
TP1: /usr/lib/x86_64-linux-gnu/libXinerama.so
TP1: /usr/lib/x86_64-linux-gnu/libXcursor.so
TP1: /usr/lib/x86_64-linux-gnu/librt.a
TP1: /usr/lib/x86_64-linux-gnu/libm.so
TP1: /usr/lib/x86_64-linux-gnu/libX11.so
TP1: /usr/lib/x86_64-linux-gnu/libXrandr.so
TP1: /usr/lib/x86_64-linux-gnu/libXinerama.so
TP1: /usr/lib/x86_64-linux-gnu/libXcursor.so
TP1: /usr/lib/x86_64-linux-gnu/libGL.so
TP1: /usr/lib/x86_64-linux-gnu/libGLU.so
TP1: CMakeFiles/TP1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/galax/Desktop/Projet-Moteur-de-Jeux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable TP1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TP1.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -E copy /home/galax/Desktop/Projet-Moteur-de-Jeux/build/./TP1 /home/galax/Desktop/Projet-Moteur-de-Jeux/TP1/

# Rule to build all files generated by this target.
CMakeFiles/TP1.dir/build: TP1
.PHONY : CMakeFiles/TP1.dir/build

CMakeFiles/TP1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TP1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TP1.dir/clean

CMakeFiles/TP1.dir/depend:
	cd /home/galax/Desktop/Projet-Moteur-de-Jeux/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/galax/Desktop/Projet-Moteur-de-Jeux /home/galax/Desktop/Projet-Moteur-de-Jeux /home/galax/Desktop/Projet-Moteur-de-Jeux/build /home/galax/Desktop/Projet-Moteur-de-Jeux/build /home/galax/Desktop/Projet-Moteur-de-Jeux/build/CMakeFiles/TP1.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/TP1.dir/depend

