get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

if(APPLE)
    set(CMAKE_BUILD_RPATH "@loader_path")
    set(CMAKE_INSTALL_RPATH "@loader_path")
elseif(UNIX AND NOT APPLE)
    set(CMAKE_BUILD_RPATH "$ORIGIN")
    set(CMAKE_INSTALL_RPATH "$ORIGIN")
endif()

set(LIB_V1_TARGET "${MODULE_NAME}_MyLib_v1")
set(APP_V1_TARGET "${MODULE_NAME}_app_v1")

add_library(${LIB_V1_TARGET} SHARED lib_v1/my_math.cpp)
target_include_directories(${LIB_V1_TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib_v1)

add_executable(${APP_V1_TARGET} app_v1/main.cpp)
target_link_libraries(${APP_V1_TARGET} PRIVATE ${LIB_V1_TARGET})

set(LIB_V2_TARGET "${MODULE_NAME}_MyLib_v2")
set(APP_V2_TARGET "${MODULE_NAME}_app_v2")

add_library(${LIB_V2_TARGET} SHARED lib_v2/my_math.cpp)
target_include_directories(${LIB_V2_TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib_v2)

add_executable(${APP_V2_TARGET} app_v2/main.cpp)
target_link_libraries(${APP_V2_TARGET} PRIVATE ${LIB_V2_TARGET})

file(GLOB MAIN_FILES "${CMAKE_CURRENT_SOURCE_DIR}/main*.cpp")

foreach(CPP_FILE ${MAIN_FILES})
    get_filename_component(BASENAME ${CPP_FILE} NAME_WE)

    set(TARGET_NAME "${MODULE_NAME}_${BASENAME}")
    
    add_executable(${TARGET_NAME} ${CPP_FILE})
endforeach()