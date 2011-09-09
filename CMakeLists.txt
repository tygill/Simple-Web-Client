cmake_minimum_required (VERSION 2.8)
project(SimpleWebClient)

# include_directories("$(SOME_VAR_NAME)/directory")
include_directories("${PROJECT_SOURCE_DIR}") #CMAKE_CURRENT_SOURCE_DIR
#link_directories("${PROJECT_BINARY_DIR}") #CMAKE_CURRENT_BINARY_DIR

#file(GLOB webclient_cpp
#    "*.cpp"
#    "http/*.cpp"
#)

set(webclient_cpp
    "download.cpp"
    "http/HttpTokenizer.cpp"
    "http/HttpResponse.cpp"
)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")

add_executable(download ${webclient_cpp})

# install (TARGETS download DESTINATION bin)
