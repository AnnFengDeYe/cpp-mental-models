get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

file(GLOB ROOT_SOURCE_FILES
        LIST_DIRECTORIES false
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

foreach(CPP_FILE ${ROOT_SOURCE_FILES})
    get_filename_component(BASENAME ${CPP_FILE} NAME_WE)

    set(TARGET_NAME "${MODULE_NAME}_${BASENAME}")
    add_executable(${TARGET_NAME} ${CPP_FILE})
endforeach()

file(GLOB DEMO_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/StaticDemo_*")

foreach(DEMO_DIR ${DEMO_DIRS})
    get_filename_component(DEMO_NAME ${DEMO_DIR} NAME)

    set(LIB_TARGET "${MODULE_NAME}_${DEMO_NAME}_lib")
    set(EXE_TARGET "${MODULE_NAME}_${DEMO_NAME}_main")

    file(GLOB DEMO_ALL_SOURCES "${DEMO_DIR}/*.cpp")
    set(EXE_SOURCE "${DEMO_DIR}/main.cpp")
    set(LIB_SOURCES ${DEMO_ALL_SOURCES})
    list(REMOVE_ITEM LIB_SOURCES ${EXE_SOURCE})

    add_library(${LIB_TARGET} STATIC ${LIB_SOURCES})
    target_include_directories(${LIB_TARGET} PUBLIC ${DEMO_DIR})

    add_executable(${EXE_TARGET} ${EXE_SOURCE})
    target_link_libraries(${EXE_TARGET} ${LIB_TARGET})
endforeach()

file(GLOB DYNAMIC_DEMO_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/DynamicDemo_*")

foreach(DEMO_DIR ${DYNAMIC_DEMO_DIRS})
    get_filename_component(DEMO_NAME ${DEMO_DIR} NAME)

    set(LIB_TARGET "${MODULE_NAME}_${DEMO_NAME}_lib")
    set(EXE_TARGET "${MODULE_NAME}_${DEMO_NAME}_main")

    file(GLOB DEMO_ALL_SOURCES "${DEMO_DIR}/*.cpp")
    set(EXE_SOURCE "${DEMO_DIR}/main.cpp")
    set(LIB_SOURCES ${DEMO_ALL_SOURCES})
    list(REMOVE_ITEM LIB_SOURCES ${EXE_SOURCE})

    add_library(${LIB_TARGET} SHARED ${LIB_SOURCES})
    target_include_directories(${LIB_TARGET} PUBLIC ${DEMO_DIR})

    add_executable(${EXE_TARGET} ${EXE_SOURCE})
    target_link_libraries(${EXE_TARGET} ${LIB_TARGET})
endforeach()