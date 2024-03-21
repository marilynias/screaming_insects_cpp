# cmake_minimum_required(VERSION 3.20)
# project(InsectSim)
# file(GLOB helloworld_SRC
#     #  "src/*.h"
#      "src/*.cpp"
# )
# find_package(SDL2 REQUIRED)
# include_directories(
#   ${CMAKE_SOURCE_DIR}/src
#   ${CMAKE_SOURCE_DIR}/include
#   ${SDL2_INCLUDE_DIRS}
# )
# add_executable(InsectSim ${helloworld_SRC})

# # target_include_directories(app PRIVATE src)
# # target_sources(app src/*.cpp)

cmake_minimum_required(VERSION 3.7)
project(SDL2Test)

file(GLOB helloworld_SRC
    #  "src/*.h"
     "src/*.cpp"
)


# include_directories(SDL2Test 
#     ${SDL2_INCLUDE_DIRS}
#     ${CMAKE_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME} ${helloworld_SRC})

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})
link_directories(${PROJECT_NAME} /src)