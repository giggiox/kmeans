cmake_minimum_required(VERSION 3.16)
project(ompkmeans)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
add_executable(kmeans main.cpp
        KMeans.cpp
        KMeans.h
        point.h
        centroid.h
        utils.h
        utils.cpp
        cuda/utils.h)
