function(setup_kcov_coverage)

execute_process(COMMAND find /home -type f -name kcov OUTPUT_VARIABLE KCOV_PATH)

# take the first line
string(REGEX MATCH "([^\n]+)" KCOV_PATH "${KCOV_PATH}")

message(STATUS "Kcov found: ${KCOV_PATH}")


endfunction()