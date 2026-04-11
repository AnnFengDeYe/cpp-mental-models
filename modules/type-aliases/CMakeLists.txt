get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

foreach(CPP_FILE ${SOURCE_FILES})
    get_filename_component(BASENAME ${CPP_FILE} NAME_WE)

    set(TARGET_NAME "${MODULE_NAME}_${BASENAME}")
    
    add_executable(${TARGET_NAME} ${CPP_FILE})
endforeach()