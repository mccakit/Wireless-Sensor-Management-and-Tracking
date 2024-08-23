cmake_minimum_required(VERSION 3.28)
project(Database_GUI)
set(CMAKE_CXX_STANDARD 23)
add_executable(${PROJECT_NAME} main.cpp
        ez_cpp.h
        ez_imgui.h
        ez_serialport.h
        ez_sqlite.h
        ez_time.h
        efes_sensor_gui.h)
include(FetchContent)

FetchContent_Declare(
        GLFW
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG 3.4
)
FetchContent_MakeAvailable(GLFW)
find_package(OpenGL REQUIRED)
target_link_libraries(glfw PRIVATE OpenGL::GL)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

FetchContent_Declare(
        IMGUI
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG v1.91.0
)
FetchContent_MakeAvailable(IMGUI)
set(IMGUI_SOURCE_DIR ${CMAKE_BINARY_DIR}/_deps/imgui-src)
add_library(imgui STATIC
        ${IMGUI_SOURCE_DIR}/imgui.cpp
        ${IMGUI_SOURCE_DIR}/imgui_demo.cpp
        ${IMGUI_SOURCE_DIR}/imgui_draw.cpp
        ${IMGUI_SOURCE_DIR}/imgui_tables.cpp
        ${IMGUI_SOURCE_DIR}/imgui_widgets.cpp
        ${IMGUI_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC
        ${IMGUI_SOURCE_DIR}
        ${IMGUI_SOURCE_DIR}/backends
)
target_link_libraries(imgui PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui)

FetchContent_Declare(
        IMPLOT
        GIT_REPOSITORY https://github.com/epezent/implot
        GIT_TAG v0.16
)
FetchContent_MakeAvailable(IMPLOT)
set(IMPLOT_SOURCE_DIR ${CMAKE_BINARY_DIR}/_deps/implot-src)
add_library(implot STATIC
        ${IMPLOT_SOURCE_DIR}/implot.cpp
        ${IMPLOT_SOURCE_DIR}/implot_demo.cpp
        ${IMPLOT_SOURCE_DIR}/implot_items.cpp
)
target_include_directories(implot PUBLIC ${IMPLOT_SOURCE_DIR})
target_link_libraries(implot PRIVATE imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE implot)

FetchContent_Declare(
        SQLITE_CPP
        GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
        GIT_TAG 3.3.1
)
FetchContent_MakeAvailable(SQLITE_CPP)
target_link_libraries(${PROJECT_NAME} PRIVATE SQLiteCpp)

FetchContent_Declare(
        JSON
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(JSON)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json)