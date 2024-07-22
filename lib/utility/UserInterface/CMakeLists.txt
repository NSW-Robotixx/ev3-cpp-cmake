add_library(UserInterface UserInterface.cpp)

target_sources(UserInterface
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/UserInterface.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/UserInterface.hpp
)

target_include_directories(UserInterface
    PUBLIC
        ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(UserInterface
    PUBLIC
        Window
        WindowManager
)