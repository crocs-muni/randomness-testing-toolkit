cmake_minimum_required(VERSION 3.0.2)


function(remove_cxx_flags FLAGS)
    list(LENGTH ${FLAGS} LEN)
    if(${LEN} EQUAL 0)
        return()
    endif()

    string(REGEX MATCHALL "-[^\ ]+" ALL_FLAGS ${CMAKE_CXX_FLAGS})
    string(REGEX MATCHALL "-[^\ ]+" TO_REMOVE ${SUPRESS_LIBS_WARNINGS})

    list (REMOVE_ITEM ALL_FLAGS ${TO_REMOVE})

    foreach(FLAG ${ALL_FLAGS})
        string(CONCAT FLAG " " ${FLAG})
        string(CONCAT RESULT ${RESULT} ${FLAG})
    endforeach(FLAG)

    set(CMAKE_CXX_FLAGS ${RESULT} PARENT_SCOPE)
endfunction(remove_cxx_flags)