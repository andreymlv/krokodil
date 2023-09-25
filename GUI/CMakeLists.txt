project(KrokodilGUI VERSION 0.0.1 LANGUAGES CXX)

find_package(OpenGL REQUIRED)

set(SOURCES
  src/imgui.cpp
  src/imgui_demo.cpp
  src/imgui_draw.cpp
  src/imgui_impl_glfw.cpp
  src/imgui_impl_opengl3.cpp
  src/imgui_tables.cpp
  src/imgui_widgets.cpp
  src/main.cpp
)

include_directories(${OPENGL_INCLUDE_DIRS})

if(MSVC)
  SET(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
endif()

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC KrokodilLanguage ${OPENGL_LIBRARIES} glfw)
target_include_directories(${PROJECT_NAME} PUBLIC include/)
if(MSVC)
  if(${CMAKE_VERSION} VERSION_LESS "3.6.0")
    message("\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'GLFW-CMake-starter' as StartUp Project in Visual Studio.\n")
  else()
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
  endif()
endif()
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
