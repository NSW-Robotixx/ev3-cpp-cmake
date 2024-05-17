add_library(gearboxEngine STATIC GearboxEngine.cpp)

target_sources(GearboxEngine
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/GearboxEngine.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/GearboxEngine.hpp
    )

target_include_directories(GearboxEngine PUBLIC ${CMAKE_SOURCE_DIR}/lib/)

target_link_libraries(GearboxEngine PUBLIC Logger)