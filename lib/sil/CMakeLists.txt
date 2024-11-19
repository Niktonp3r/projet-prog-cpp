cmake_minimum_required(VERSION 3.20)
project(sil)

add_library(sil)
add_library(sil::sil ALIAS sil)
target_compile_features(sil PRIVATE cxx_std_17)

# ---Add source files---
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*)
target_sources(sil PRIVATE ${SOURCES})
target_include_directories(sil SYSTEM PUBLIC include)

# ---Pass the CMAKE_SOURCE_DIR to the code, so that we can make our paths relative to it---
target_compile_definitions(sil PRIVATE
    SIL_CMAKE_SOURCE_DIR=\"${CMAKE_SOURCE_DIR}\"
)

# ---Add libraries---
# ---glm---
add_subdirectory(lib/glm)
target_link_libraries(sil PUBLIC glm)

# ---img---
add_subdirectory(lib/img)
target_link_libraries(sil PRIVATE img::img)