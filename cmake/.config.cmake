#FUNCTION                                                                      
# 显示配置信息
macro(SHOW_CONFIG)
    message(STATUS "SHOW VARS START >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
    message(STATUS "SHOW VARS START >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
    message(STATUS "SHOW VARS START >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")

    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "[${_variableName}] = [${${_variableName}}]")
    endforeach()
    message(STATUS "SHOW VARS END <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<")
    message(STATUS "SHOW VARS END <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<")
    message(STATUS "SHOW VARS END <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<")
endmacro(SHOW_CONFIG)

# 显示变量 
function(SHOW _var)
    message(STATUS "${_var}=${${_var}}")
endfunction(SHOW)


#显示变量
function(SHOW_LIST _list)
    message(STATUS "SHOW LIST START >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        #index of list
        set(count 0)
        foreach(item ${_list})
            message(STATUS "${_list}[count] : ${item}")
            #index++
            math(EXPR count "${count}+1")
        endforeach()
    message(STATUS "SHOW LIST END <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<")
endfunction()

# 显示列表

if(QT)
    set(CMAKE_PREFIX_PATH "")
    if(LINUX)
	    list(APPEND CMAKE_PREFIX_PATH :"$ENV{HOME}/Qt/6.2.4/macos/lib/cmake/Qt6;$ENV{HOME}/Qt")
    elseif(APPLE)
    elseif(WIN32)
    endif()
endif()


macro(LINESTART)
    message(STATUS "--------------------------------------------------------------------------------lineStart>>")
endmacro()

macro(LINEEND)
    message(STATUS "------------------------------------------------------------------------------------lineEnd<<")
endmacro()



# VARIABLES
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#私有变量
set(HOME $ENV{HOME})   
#设置缓存不对,不知道为啥
#set(CMAKE_INSTALL_PREFIX "${HOME}/app" CACHE PATH "好像不对") 这样不对
set(CMAKE_INSTALL_PREFIX "${HOME}/app")
set(GEN10 1 CACHE BOOL "gen10")

LINESTART()
message(STATUS ".config.cmake be included")
message(STATUS "CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}")
LINEEND()


#PRIVATE INCLUDE
#include(${CMAKE_CURRENT_LIST_DIR}/privateVariable.cmake)

#SHOW_CONFIG()   
