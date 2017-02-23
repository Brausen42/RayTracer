# CMake expects a few commands, like the version required. We'll only require an older one
# since we aren't doing anything fancy.
cmake_minimum_required(VERSION 2.6)

# We can set C++ flags (like optimizations) here. We'll compile with c++11 since it
# has a lot of classes that will be useful.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# We also have to assign a project name and set the language used. In this case, we're
# calling it "example" and will be using C and C++:
project(raytracer C CXX)

# Here, we make a variable that is actually a big list of all our source files.
# Note that the file also contains the directory w/ respect to this CMakeLists.txt.
# Every time we add a new source file, remember to add it to this list before
# you compile! Doing so manually is better than recursively (i.e. with file(GLOB_RECURSE ...))
# because that can lead to frustrating build errors if you're not careful.
set(MY_SOURCES
	src/main.cpp
	src/Vec3.cpp
	src/Vec3.hpp
	src/Object.cpp
	src/Object.hpp
	src/Color.cpp
	src/Color.hpp
	src/Sphere.cpp
	src/Sphere.hpp
	src/Ray.cpp
	src/Ray.hpp
	src/Ellipsoid.cpp
	src/Ellipsoid.hpp
	src/MtlColor.cpp
	src/MtlColor.hpp
	src/Light.cpp
	src/Light.hpp
	src/Triangle.cpp
	src/Triangle.hpp
	src/RayPayload.cpp
	src/RayPayload.hpp
	src/Scene.cpp
	src/Scene.hpp
)

# Now we can add an executable, and we're done!
add_executable(raytracer ${MY_SOURCES})
