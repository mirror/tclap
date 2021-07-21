function(add_file path)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${path} ${CMAKE_CURRENT_BINARY_DIR}/${path})
endfunction()

add_file(upload.sh)
add_file(style.css)
add_file(README)
add_file(manual.xml)
add_file(index.html)
add_file(build.html)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else ()
  message("Doxygen need to be installed to generate the doxygen documentation")
endif ()

set(DOCBOOK_XSL /usr/share/xml/docbook/stylesheet/docbook-xsl/html/docbook.xsl)

if (EXISTS ${DOCBOOK_XSL})
find_package(LibXslt)
if (LIBXSLT_XSLTPROC_EXECUTABLE)
add_custom_target( doc_manual ALL
  COMMAND ${LIBXSLT_XSLTPROC_EXECUTABLE} -o manual.html --stringparam html.stylesheet style.css ${DOCBOOK_XSL}  manual.xml
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Processing manual.xml to HTML"
  VERBATIM)
endif ()
endif ()
