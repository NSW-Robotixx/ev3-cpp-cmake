# execute_process(COMMAND find ${CONAN_HOME} -type f -name doxygen OUTPUT_VARIABLE DOXYGEN_PATH)
# find_program(DOXYGEN_PATH doxygen)
find_file(DOXYGEN_PATH doxygen HINTS /home/niklas/.conan2/)

execute_process(COMMAND find /home -type f -name doxygen OUTPUT_VARIABLE DOXYGEN_PATH)

# take the first line
string(REGEX MATCH "([^\n]+)" DOXYGEN_PATH "${DOXYGEN_PATH}")

message(STATUS "Doxygen found: ${DOXYGEN_PATH}")
add_custom_target(docs
  COMMAND ${DOXYGEN_PATH}
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  COMMENT "Generating API documentation with Doxygen"
  VERBATIM
)

# file(READ ${CMAKE_BINARY_DIR}/conan/build/Debug/generators/conanbuild.sh CONAN_ENV)
# message(STATUS "Conan environment variables: ${CONAN_ENV}")

# # remove everything what is not char or /
# STRING(REGEX REPLACE "[^ a-zA-Z\\/_0-9-]" "" CONAN_ENV "${CONAN_ENV}")

# message(STATUS "Conan environment variables: ${CONAN_ENV}")

# # STRING(REGEX MATCH "/build/conan.+.sh$" "" CONAN_ENV_PATH "${CONAN_ENV}")

# message(STATUS "Conan environment variables: ${CONAN_ENV_PATH}")

# # cut the last part of the path
# STRING(REGEX REPLACE "conan.+.sh$" "" CONAN_ENV_PATH "${CONAN_ENV}")

# message(STATUS "Conan environment variables: ${CONAN_ENV}")

# STRING(REPLACE ${CONAN_ENV} "" CONAN_ENV_PATHp "${CONAN_ENV_PATH}")

# file(READ ${CONAN_ENV_PATH} CONAN_ENV_PATH)

# message(STATUS "Conan environment variables: ${CONAN_ENV_PATH}")

# add_custom_target(envVariables
#   COMMAND chmod +x ${CMAKE_BINARY_DIR}/conan/build/Debug/generators/conanbuild.sh
#   COMMAND . ${CMAKE_BINARY_DIR}/conan/build/Debug/generators/conanbuild.sh
#   COMMAND doxygen version
#   WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
#   COMMENT "Setting environment variables"
#   VERBATIM
# )

# add_dependencies(docs envVariables)