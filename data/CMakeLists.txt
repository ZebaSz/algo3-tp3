set(DATA_FILES data.cpp grafGen.cpp)

add_executable(generarData ${DATA_FILES})
target_link_libraries (generarData algo3-tp3-base)
