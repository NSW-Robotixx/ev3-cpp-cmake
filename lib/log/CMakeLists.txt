find_package(log4cplus REQUIRED)

add_library(Logger  
    ${CMAKE_CURRENT_LIST_DIR}/src/Logger.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/FileLogger.cpp
    )

target_sources(Logger 
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/Logger.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/FileLogger.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include/Logger.hpp
        ${CMAKE_CURRENT_LIST_DIR}/include/FileLogger.hpp
)

target_include_directories(Logger
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Logger
    PUBLIC
        log4cplus::log4cplus
)

add_subdirectory(test)