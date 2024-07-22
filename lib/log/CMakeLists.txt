add_library(Logger  
        Logger.cpp
        FileLogger.cpp
    )

target_sources(Logger 
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Logger.cpp
        ${CMAKE_CURRENT_LIST_DIR}/FileLogger.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Logger.hpp
        ${CMAKE_CURRENT_LIST_DIR}/FileLogger.hpp
)

target_include_directories(Logger
    PUBLIC
        ${CMAKE_SOURCE_DIR}/lib
        ${CMAKE_CURRENT_LIST_DIR}/
)