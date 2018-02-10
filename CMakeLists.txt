cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

SET(title Untitled)
project(devProj)

set(SDL2_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/inc)
set(SDL2_LIBRARY ${PROJECT_SOURCE_DIR}/lib/SDL2.lib)
set(SDL2_MAIN ${PROJECT_SOURCE_DIR}/lib/SDL2main.lib)
set(SDLIMG_LIBRARY ${PROJECT_SOURCE_DIR}/lib/SDL2_image.lib)
set(SDLMIX_LIBRARY ${PROJECT_SOURCE_DIR}/lib/SDL2_mixer.lib)

include_directories(${SDL2_INCLUDE_DIR})

set(SRCDIR ${PROJECT_SOURCE_DIR}/src)

set(SOURCE_FILES
${SRCDIR}/CApp.cpp
${SRCDIR}/CApp_OnCleanup.cpp
${SRCDIR}/CApp_OnEvent.cpp
${SRCDIR}/CApp_OnInit.cpp
${SRCDIR}/CApp_OnLoop.cpp
${SRCDIR}/CApp_OnRender.cpp
${SRCDIR}/CAsset.cpp
${SRCDIR}/CAsset_Ext.cpp
${SRCDIR}/CCamera.cpp
${SRCDIR}/CEvent.cpp
${SRCDIR}/CFPS.cpp
${SRCDIR}/CMode.cpp
${SRCDIR}/CSound.cpp
${SRCDIR}/CSurface.cpp
)

set(HEADER_FILES
${SRCDIR}/CApp.h
${SRCDIR}/CAsset.h
${SRCDIR}/CCamera.h
${SRCDIR}/CEvent.h
${SRCDIR}/CFPS.h
${SRCDIR}/CMode.h
${SRCDIR}/CSound.h
${SRCDIR}/CSurface.h
${SRCDIR}/Define.h
)

set(GCC_COVERAGE_LINK_FLAGS	"-mwindows")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_executable(Untitled ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(Untitled ${SDL2_MAIN} ${SDL2_LIBRARY} ${SDLIMG_LIBRARY} ${SDLMIX_LIBRARY})
