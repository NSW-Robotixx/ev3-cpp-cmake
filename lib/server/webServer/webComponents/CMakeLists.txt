add_library(webComponents 
        WebComponentBase.cpp
        ComponentFullBody.cpp
        ComponentFactory.cpp
)

target_sources(webComponents
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/WebComponentBase.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ComponentFullBody.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ComponentFactory.cpp
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/WebComponentBase.hpp
        ${CMAKE_CURRENT_LIST_DIR}/ComponentFullBody.hpp
        ${CMAKE_CURRENT_LIST_DIR}/ComponentFactory.hpp
)

target_include_directories(webComponents
    PUBLIC
        ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(webComponents
    PUBLIC
        Logger
)
