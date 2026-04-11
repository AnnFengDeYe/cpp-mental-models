get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")


foreach(CPP_FILE ${SOURCE_FILES})
    get_filename_component(BASENAME ${CPP_FILE} NAME_WE)
    
    # MoveSemantic_main1
    set(TARGET_NAME "${MODULE_NAME}_${BASENAME}")

    add_executable(${TARGET_NAME} ${CPP_FILE})

    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${TARGET_NAME} PRIVATE -fno-elide-constructors)
    elseif(MSVC)
        target_compile_options(${TARGET_NAME} PRIVATE /Od)
    endif()
endforeach()