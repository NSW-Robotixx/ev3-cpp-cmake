find_package(Doxygen REQUIRED dot)

find_package(Doxygen REQUIRED dot)

# set(DOXYGEN_HTML_OUTPUT            ${PROJECT_BINARY_DIR}/docs/html)
set(DOXYGEN_JAVADOC_AUTOBRIEF      YES)
set(DOXYGEN_GENERATE_HTML          YES)
set(DOXYGEN_HAVE_DOT               YES)
set(DOXYGEN_EXCLUDE_PATTERNS       "*/build/*")
set(DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)  # requires a README.md in /myproject/

# other DOXYGEN_... options

doxygen_add_docs(docs_target
  ${PROJECT_SOURCE_DIR}
  ALL  # does not seem to work
  COMMENT "Generate HTML documentation"
)