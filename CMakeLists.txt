cmake_minimum_required(VERSION 3.20)

# You can set the name of your project here
project(ImageEditor)
add_executable(${PROJECT_NAME})

# Choose your C++ version
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Prevents compiler-specific extensions to C++ because they might allow code to compile on your machine but not on other people's machine
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_EXTENSIONS OFF)

# Add all the source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/* lib/random.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src lib)

# Link the sil library into the project
add_subdirectory(lib/sil)
target_link_libraries(${PROJECT_NAME} PRIVATE sil)