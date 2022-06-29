file(GLOB source_files src/*.cpp include/*.h)
add_library(estruturas ${source_files})
target_include_directories(estruturas PUBLIC ${PROJECT_SOURCE_DIR}/include)