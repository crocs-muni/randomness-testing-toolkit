find_package(Git)

function(detect_version FILE)
    if(GIT_FOUND)
        execute_process(
            COMMAND ${GIT_EXECUTABLE} log -1 --format=%H
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_COMMIT
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        execute_process(
            COMMAND ${GIT_EXECUTABLE} log -1 --format=%h
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_COMMIT_SHORT
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
    else()
        message(WARNING "Git not found")
        set(GIT_COMMIT n/a)
        set(GIT_COMMIT_SHORT n/a)
    endif()
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/${FILE}.in" "${CMAKE_CURRENT_SOURCE_DIR}/${FILE}" @ONLY)
    MESSAGE("Successfully updated commit information in ${FILE}.")
endfunction(detect_version)
