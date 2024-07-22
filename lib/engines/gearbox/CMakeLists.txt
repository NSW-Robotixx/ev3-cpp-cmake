add_library(gearboxEngine GearboxEngine.cpp)

target_sources(gearboxEngine
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/GearboxEngine.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/GearboxEngine.hpp
    )

target_include_directories(gearboxEngine PUBLIC ${CMAKE_SOURCE_DIR}/lib/)

target_link_libraries(gearboxEngine PUBLIC Logger)