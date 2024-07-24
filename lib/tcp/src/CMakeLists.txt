set(EV3_TCP_COMMUNICATION_SRC
    ${EV3_TCP_COMMUNICATION_SRC_DIR}/EV3_tcp_communication_client.cpp
    ${EV3_TCP_COMMUNICATION_SRC_DIR}/EV3_tcp_communication_server.cpp
    ${EV3_TCP_COMMUNICATION_SRC_DIR}/utils.cpp
)

set(EV3_TCP_COMMUNICATION_HDR
    ${EV3_TCP_COMMUNICATION_INCLUDE_DIR}/EV3_tcp_communication_client.hpp
    ${EV3_TCP_COMMUNICATION_INCLUDE_DIR}/EV3_tcp_communication_server.hpp
    ${EV3_TCP_COMMUNICATION_SRC_DIR}/utils.hpp
)

add_library(EV3_tcp_communication ${EV3_TCP_COMMUNICATION_SRC})



target_include_directories(EV3_tcp_communication PUBLIC ${EV3_TCP_COMMUNICATION_INCLUDE_DIR})
target_include_directories(EV3_tcp_communication PRIVATE ${EV3_TCP_COMMUNICATION_SRC_DIR})