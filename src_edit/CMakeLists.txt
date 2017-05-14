cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

SET(TITLE TDME)
project(devProj)

set(SDL2_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../inc)
set(SDL2_LIBRARY ${PROJECT_SOURCE_DIR}/../lib/SDL2.lib)
set(SDL2_MAIN ${PROJECT_SOURCE_DIR}/../lib/SDL2main.lib)
set(SDLIMG_LIBRARY ${PROJECT_SOURCE_DIR}/../lib/SDL2_image.lib)
set(SDLMIX_LIBRARY ${PROJECT_SOURCE_DIR}/../lib/SDL2_mixer.lib)

include_directories(${SDL2_INCLUDE_DIR})

set(SRCDIR ${PROJECT_SOURCE_DIR})

set(SOURCE_FILES
${SRCDIR}/CAnimation.cpp
${SRCDIR}/CApp.cpp
${SRCDIR}/CApp_OnClick.cpp
${SRCDIR}/CApp_OnEvent.cpp
${SRCDIR}/CApp_OnInit.cpp
${SRCDIR}/CApp_OnLoop.cpp
${SRCDIR}/CApp_OnMotion.cpp
${SRCDIR}/CApp_OnRender.cpp
${SRCDIR}/CApp_OnTerminate.cpp
${SRCDIR}/CArea.cpp
${SRCDIR}/CCamera.cpp
${SRCDIR}/CChangeTile.cpp
${SRCDIR}/CConfig.cpp
${SRCDIR}/CEntity.cpp
${SRCDIR}/CEntityCol.cpp
${SRCDIR}/CEntityEdit.cpp
${SRCDIR}/CEntityInfo.cpp
${SRCDIR}/CEntityRes.cpp
${SRCDIR}/CEvent.cpp
${SRCDIR}/CFPS.cpp
${SRCDIR}/CIO.cpp
${SRCDIR}/CMap.cpp
${SRCDIR}/CMenu.cpp
${SRCDIR}/CScenery.cpp
${SRCDIR}/CSceneryEdit.cpp
${SRCDIR}/CSceneryMod.cpp
${SRCDIR}/CSound.cpp
${SRCDIR}/CSurface.cpp
${SRCDIR}/CTile.cpp
${SRCDIR}/CUI.cpp
${SRCDIR}/Font.cpp
)

set(HEADER_FILES
${SRCDIR}/CAnimation.h
${SRCDIR}/CApp.h
${SRCDIR}/CArea.h
${SRCDIR}/CCamera.h
${SRCDIR}/CChangeTile.h
${SRCDIR}/CConfig.h
${SRCDIR}/CEntity.h
${SRCDIR}/CEntityEdit.h
${SRCDIR}/CEntityRes.h
${SRCDIR}/CEvent.h
${SRCDIR}/CFPS.h
${SRCDIR}/CIO.h
${SRCDIR}/CMap.h
${SRCDIR}/CMenu.h
${SRCDIR}/CScenery.h
${SRCDIR}/CSceneryEdit.h
${SRCDIR}/CSceneryMod.h
${SRCDIR}/CSound.h
${SRCDIR}/CSurface.h
${SRCDIR}/CTile.h
${SRCDIR}/CUI.h
${SRCDIR}/Define.h
${SRCDIR}/Font.h
)

set(GCC_COVERAGE_LINK_FLAGS	"-mwindows")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_executable(${TITLE} ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(${TITLE} ${SDL2_MAIN} ${SDL2_LIBRARY} ${SDLIMG_LIBRARY} ${SDLMIX_LIBRARY})
