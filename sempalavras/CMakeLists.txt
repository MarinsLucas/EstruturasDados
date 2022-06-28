
file(GLOB source_files src/*.cpp include/*.h)
add_library(sempalavras ${source_files})
target_include_directories(sempalavras PUBLIC ${PROJECT_SOURCE_DIR}/include)