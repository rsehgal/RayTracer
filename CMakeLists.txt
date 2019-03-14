cmake_minimum_required (VERSION 2.6)

project (RayTracer)

include_directories(..)
include_directories(include)
add_executable(RayTracer RayTracer.cpp)
add_executable(UsingRay test/UsingRay.cpp)
target_link_libraries(UsingRay raytracer)

file(GLOB sources ${sources} src/*.cpp)
add_library(raytracer SHARED ${sources})

add_executable(ShapeWithRayTracer test/ShapeWithRayTracer.cpp)
target_link_libraries(ShapeWithRayTracer raytracer vecgeom)

add_executable(ShapeRayTracingIncludingNormal test/ShapeRayTracingIncludingNormal.cpp)
target_link_libraries(ShapeRayTracingIncludingNormal raytracer vecgeom)

add_executable(ShapeRayTracingMultipleObjectIncludingNormal test/ShapeRayTracingMultipleObjectIncludingNormal.cpp)
target_link_libraries(ShapeRayTracingMultipleObjectIncludingNormal raytracer vecgeom)

add_executable(RayTracingWithPointsFromWorld test/RayTracingWithPointsFromWorld.cpp)
target_link_libraries(RayTracingWithPointsFromWorld raytracer vecgeom)

