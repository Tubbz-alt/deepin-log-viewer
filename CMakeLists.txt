cmake_minimum_required(VERSION 3.7)

if (NOT DEFINED VERSION)
    set(VERSION 1.2.2)
endif ()
#这里项目名称绝对不能和编译出的target名称一样
project(deepin_log_viewer)
option(DMAN_RELEAE OFF "Install dman resources to system or not")
add_subdirectory(application)
add_subdirectory(logViewerAuth)
add_subdirectory(logViewerTruncate)
option(USE_TEST ON "UT" )
if (USE_TEST)
add_subdirectory(tests)
endif(USE_TEST)


option(PERF_ON "open the info of benchmark" ON)
