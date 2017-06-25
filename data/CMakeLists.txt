find_package(Boost COMPONENTS system filesystem)
if(Boost_FOUND)
    set(DATA_FILES data.cpp grafGen.cpp)

    add_executable(generarData ${DATA_FILES})
    target_link_libraries (generarData algo3-tp3-base)
    target_link_libraries(generarData ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
endif()