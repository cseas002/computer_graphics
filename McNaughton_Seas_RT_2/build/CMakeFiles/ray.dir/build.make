# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/build"

# Include any dependencies generated for this target.
include CMakeFiles/ray.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ray.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ray.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ray.dir/flags.make

CMakeFiles/ray.dir/src/image.cpp.o: CMakeFiles/ray.dir/flags.make
CMakeFiles/ray.dir/src/image.cpp.o: ../src/image.cpp
CMakeFiles/ray.dir/src/image.cpp.o: CMakeFiles/ray.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ray.dir/src/image.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ray.dir/src/image.cpp.o -MF CMakeFiles/ray.dir/src/image.cpp.o.d -o CMakeFiles/ray.dir/src/image.cpp.o -c "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/image.cpp"

CMakeFiles/ray.dir/src/image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ray.dir/src/image.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/image.cpp" > CMakeFiles/ray.dir/src/image.cpp.i

CMakeFiles/ray.dir/src/image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ray.dir/src/image.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/image.cpp" -o CMakeFiles/ray.dir/src/image.cpp.s

CMakeFiles/ray.dir/src/lode/lodepng.cpp.o: CMakeFiles/ray.dir/flags.make
CMakeFiles/ray.dir/src/lode/lodepng.cpp.o: ../src/lode/lodepng.cpp
CMakeFiles/ray.dir/src/lode/lodepng.cpp.o: CMakeFiles/ray.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ray.dir/src/lode/lodepng.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ray.dir/src/lode/lodepng.cpp.o -MF CMakeFiles/ray.dir/src/lode/lodepng.cpp.o.d -o CMakeFiles/ray.dir/src/lode/lodepng.cpp.o -c "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/lode/lodepng.cpp"

CMakeFiles/ray.dir/src/lode/lodepng.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ray.dir/src/lode/lodepng.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/lode/lodepng.cpp" > CMakeFiles/ray.dir/src/lode/lodepng.cpp.i

CMakeFiles/ray.dir/src/lode/lodepng.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ray.dir/src/lode/lodepng.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/lode/lodepng.cpp" -o CMakeFiles/ray.dir/src/lode/lodepng.cpp.s

CMakeFiles/ray.dir/src/main.cpp.o: CMakeFiles/ray.dir/flags.make
CMakeFiles/ray.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/ray.dir/src/main.cpp.o: CMakeFiles/ray.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ray.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ray.dir/src/main.cpp.o -MF CMakeFiles/ray.dir/src/main.cpp.o.d -o CMakeFiles/ray.dir/src/main.cpp.o -c "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/main.cpp"

CMakeFiles/ray.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ray.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/main.cpp" > CMakeFiles/ray.dir/src/main.cpp.i

CMakeFiles/ray.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ray.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/main.cpp" -o CMakeFiles/ray.dir/src/main.cpp.s

CMakeFiles/ray.dir/src/objloader.cpp.o: CMakeFiles/ray.dir/flags.make
CMakeFiles/ray.dir/src/objloader.cpp.o: ../src/objloader.cpp
CMakeFiles/ray.dir/src/objloader.cpp.o: CMakeFiles/ray.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ray.dir/src/objloader.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ray.dir/src/objloader.cpp.o -MF CMakeFiles/ray.dir/src/objloader.cpp.o.d -o CMakeFiles/ray.dir/src/objloader.cpp.o -c "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/objloader.cpp"

CMakeFiles/ray.dir/src/objloader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ray.dir/src/objloader.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/objloader.cpp" > CMakeFiles/ray.dir/src/objloader.cpp.i

CMakeFiles/ray.dir/src/objloader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ray.dir/src/objloader.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/objloader.cpp" -o CMakeFiles/ray.dir/src/objloader.cpp.s

CMakeFiles/ray.dir/src/raytracer.cpp.o: CMakeFiles/ray.dir/flags.make
CMakeFiles/ray.dir/src/raytracer.cpp.o: ../src/raytracer.cpp
CMakeFiles/ray.dir/src/raytracer.cpp.o: CMakeFiles/ray.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ray.dir/src/raytracer.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ray.dir/src/raytracer.cpp.o -MF CMakeFiles/ray.dir/src/raytracer.cpp.o.d -o CMakeFiles/ray.dir/src/raytracer.cpp.o -c "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/raytracer.cpp"

CMakeFiles/ray.dir/src/raytracer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ray.dir/src/raytracer.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/raytracer.cpp" > CMakeFiles/ray.dir/src/raytracer.cpp.i

CMakeFiles/ray.dir/src/raytracer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ray.dir/src/raytracer.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/raytracer.cpp" -o CMakeFiles/ray.dir/src/raytracer.cpp.s

CMakeFiles/ray.dir/src/scene.cpp.o: CMakeFiles/ray.dir/flags.make
CMakeFiles/ray.dir/src/scene.cpp.o: ../src/scene.cpp
CMakeFiles/ray.dir/src/scene.cpp.o: CMakeFiles/ray.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/ray.dir/src/scene.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ray.dir/src/scene.cpp.o -MF CMakeFiles/ray.dir/src/scene.cpp.o.d -o CMakeFiles/ray.dir/src/scene.cpp.o -c "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/scene.cpp"

CMakeFiles/ray.dir/src/scene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ray.dir/src/scene.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/scene.cpp" > CMakeFiles/ray.dir/src/scene.cpp.i

CMakeFiles/ray.dir/src/scene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ray.dir/src/scene.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/scene.cpp" -o CMakeFiles/ray.dir/src/scene.cpp.s

CMakeFiles/ray.dir/src/shapes/quad.cpp.o: CMakeFiles/ray.dir/flags.make
CMakeFiles/ray.dir/src/shapes/quad.cpp.o: ../src/shapes/quad.cpp
CMakeFiles/ray.dir/src/shapes/quad.cpp.o: CMakeFiles/ray.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/ray.dir/src/shapes/quad.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ray.dir/src/shapes/quad.cpp.o -MF CMakeFiles/ray.dir/src/shapes/quad.cpp.o.d -o CMakeFiles/ray.dir/src/shapes/quad.cpp.o -c "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/shapes/quad.cpp"

CMakeFiles/ray.dir/src/shapes/quad.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ray.dir/src/shapes/quad.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/shapes/quad.cpp" > CMakeFiles/ray.dir/src/shapes/quad.cpp.i

CMakeFiles/ray.dir/src/shapes/quad.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ray.dir/src/shapes/quad.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/shapes/quad.cpp" -o CMakeFiles/ray.dir/src/shapes/quad.cpp.s

CMakeFiles/ray.dir/src/shapes/solvers.cpp.o: CMakeFiles/ray.dir/flags.make
CMakeFiles/ray.dir/src/shapes/solvers.cpp.o: ../src/shapes/solvers.cpp
CMakeFiles/ray.dir/src/shapes/solvers.cpp.o: CMakeFiles/ray.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/ray.dir/src/shapes/solvers.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ray.dir/src/shapes/solvers.cpp.o -MF CMakeFiles/ray.dir/src/shapes/solvers.cpp.o.d -o CMakeFiles/ray.dir/src/shapes/solvers.cpp.o -c "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/shapes/solvers.cpp"

CMakeFiles/ray.dir/src/shapes/solvers.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ray.dir/src/shapes/solvers.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/shapes/solvers.cpp" > CMakeFiles/ray.dir/src/shapes/solvers.cpp.i

CMakeFiles/ray.dir/src/shapes/solvers.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ray.dir/src/shapes/solvers.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/shapes/solvers.cpp" -o CMakeFiles/ray.dir/src/shapes/solvers.cpp.s

CMakeFiles/ray.dir/src/shapes/sphere.cpp.o: CMakeFiles/ray.dir/flags.make
CMakeFiles/ray.dir/src/shapes/sphere.cpp.o: ../src/shapes/sphere.cpp
CMakeFiles/ray.dir/src/shapes/sphere.cpp.o: CMakeFiles/ray.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/ray.dir/src/shapes/sphere.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ray.dir/src/shapes/sphere.cpp.o -MF CMakeFiles/ray.dir/src/shapes/sphere.cpp.o.d -o CMakeFiles/ray.dir/src/shapes/sphere.cpp.o -c "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/shapes/sphere.cpp"

CMakeFiles/ray.dir/src/shapes/sphere.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ray.dir/src/shapes/sphere.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/shapes/sphere.cpp" > CMakeFiles/ray.dir/src/shapes/sphere.cpp.i

CMakeFiles/ray.dir/src/shapes/sphere.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ray.dir/src/shapes/sphere.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/shapes/sphere.cpp" -o CMakeFiles/ray.dir/src/shapes/sphere.cpp.s

CMakeFiles/ray.dir/src/triple.cpp.o: CMakeFiles/ray.dir/flags.make
CMakeFiles/ray.dir/src/triple.cpp.o: ../src/triple.cpp
CMakeFiles/ray.dir/src/triple.cpp.o: CMakeFiles/ray.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/ray.dir/src/triple.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ray.dir/src/triple.cpp.o -MF CMakeFiles/ray.dir/src/triple.cpp.o.d -o CMakeFiles/ray.dir/src/triple.cpp.o -c "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/triple.cpp"

CMakeFiles/ray.dir/src/triple.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ray.dir/src/triple.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/triple.cpp" > CMakeFiles/ray.dir/src/triple.cpp.i

CMakeFiles/ray.dir/src/triple.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ray.dir/src/triple.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/src/triple.cpp" -o CMakeFiles/ray.dir/src/triple.cpp.s

# Object files for target ray
ray_OBJECTS = \
"CMakeFiles/ray.dir/src/image.cpp.o" \
"CMakeFiles/ray.dir/src/lode/lodepng.cpp.o" \
"CMakeFiles/ray.dir/src/main.cpp.o" \
"CMakeFiles/ray.dir/src/objloader.cpp.o" \
"CMakeFiles/ray.dir/src/raytracer.cpp.o" \
"CMakeFiles/ray.dir/src/scene.cpp.o" \
"CMakeFiles/ray.dir/src/shapes/quad.cpp.o" \
"CMakeFiles/ray.dir/src/shapes/solvers.cpp.o" \
"CMakeFiles/ray.dir/src/shapes/sphere.cpp.o" \
"CMakeFiles/ray.dir/src/triple.cpp.o"

# External object files for target ray
ray_EXTERNAL_OBJECTS =

ray: CMakeFiles/ray.dir/src/image.cpp.o
ray: CMakeFiles/ray.dir/src/lode/lodepng.cpp.o
ray: CMakeFiles/ray.dir/src/main.cpp.o
ray: CMakeFiles/ray.dir/src/objloader.cpp.o
ray: CMakeFiles/ray.dir/src/raytracer.cpp.o
ray: CMakeFiles/ray.dir/src/scene.cpp.o
ray: CMakeFiles/ray.dir/src/shapes/quad.cpp.o
ray: CMakeFiles/ray.dir/src/shapes/solvers.cpp.o
ray: CMakeFiles/ray.dir/src/shapes/sphere.cpp.o
ray: CMakeFiles/ray.dir/src/triple.cpp.o
ray: CMakeFiles/ray.dir/build.make
ray: CMakeFiles/ray.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable ray"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ray.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ray.dir/build: ray
.PHONY : CMakeFiles/ray.dir/build

CMakeFiles/ray.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ray.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ray.dir/clean

CMakeFiles/ray.dir/depend:
	cd "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2" "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2" "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/build" "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/build" "/Users/cseas/Desktop/Groningen/Computer Graphics/Labs/computer_graphics/McNaughton_Seas_RT_2/build/CMakeFiles/ray.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/ray.dir/depend

