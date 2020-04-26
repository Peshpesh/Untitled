cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

SET(TITLE Editor)
project(devProj)

set(SDL2_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../inc)
set(SDL2_LIBRARY ${PROJECT_SOURCE_DIR}/../lib/SDL2.lib)
set(SDL2_MAIN ${PROJECT_SOURCE_DIR}/../lib/SDL2main.lib)
set(SDLIMG_LIBRARY ${PROJECT_SOURCE_DIR}/../lib/SDL2_image.lib)
set(SDLMIX_LIBRARY ${PROJECT_SOURCE_DIR}/../lib/SDL2_mixer.lib)

include_directories(${SDL2_INCLUDE_DIR})

set(SRCDIR ${PROJECT_SOURCE_DIR})

set(SOURCE_FILES
${SRCDIR}/CAnchorScenery.cpp
${SRCDIR}/CAnimation.cpp
${SRCDIR}/CApp.cpp
${SRCDIR}/CApp_Event.cpp
${SRCDIR}/CApp_Ext.cpp
${SRCDIR}/CApp_Init.cpp
${SRCDIR}/CApp_Loop.cpp
${SRCDIR}/CApp_Motion.cpp
${SRCDIR}/CApp_Render.cpp
${SRCDIR}/CApp_Terminate.cpp
${SRCDIR}/CArea.cpp
${SRCDIR}/CAsset.cpp
${SRCDIR}/CAsset_Ext.cpp
${SRCDIR}/CButton.cpp
${SRCDIR}/CCamera.cpp
${SRCDIR}/CChangeEntity.cpp
${SRCDIR}/CChangeScenery.cpp
${SRCDIR}/CChangeTile.cpp
${SRCDIR}/CEditMap.cpp
${SRCDIR}/CEditMap_Event.cpp
${SRCDIR}/CEditMap_Ext.cpp
${SRCDIR}/CEditMap_Render.cpp
${SRCDIR}/CEntity.cpp
${SRCDIR}/CEntityData.cpp
${SRCDIR}/CEntityEditor.cpp
${SRCDIR}/CEntityEditor_Event.cpp
${SRCDIR}/CEntityEditor_Ext.cpp
${SRCDIR}/CEntityEditor_Render.cpp
${SRCDIR}/CError.cpp
${SRCDIR}/CEvent.cpp
${SRCDIR}/CFileIO.cpp
${SRCDIR}/CFont.cpp
${SRCDIR}/CFont_Def.cpp
${SRCDIR}/CFPS.cpp
${SRCDIR}/CHitboxEditor.cpp
${SRCDIR}/CInform.cpp
${SRCDIR}/CInterrupt.cpp
${SRCDIR}/CLayerEditor.cpp
${SRCDIR}/CMap.cpp
${SRCDIR}/CMeter.cpp
${SRCDIR}/CModel.cpp
${SRCDIR}/CModule.cpp
${SRCDIR}/COptions.cpp
${SRCDIR}/COptions_Ext.cpp
${SRCDIR}/CPlanArea.cpp
${SRCDIR}/CPlanEditor.cpp
${SRCDIR}/CPlanEditor_Event.cpp
${SRCDIR}/CPlanEditor_Ext.cpp
${SRCDIR}/CPlanEditor_Render.cpp
${SRCDIR}/CPlanMap.cpp
${SRCDIR}/CScenery.cpp
${SRCDIR}/CSceneryData.cpp
${SRCDIR}/CSceneryEditor.cpp
${SRCDIR}/CSceneryEditor_Event.cpp
${SRCDIR}/CSceneryEditor_Ext.cpp
${SRCDIR}/CSceneryEditor_Render.cpp
${SRCDIR}/CSimEntity.cpp
${SRCDIR}/CSimEntity_Coll.cpp
${SRCDIR}/CSimEntity_Move.cpp
${SRCDIR}/CSimulate.cpp
${SRCDIR}/CSimulate_Ext.cpp
${SRCDIR}/CSimulate_Event.cpp
${SRCDIR}/CSimulate_Loop.cpp
${SRCDIR}/CSimulate_Render.cpp
${SRCDIR}/CSound.cpp
${SRCDIR}/CStage.cpp
${SRCDIR}/CSurface.cpp
${SRCDIR}/CTerminate.cpp
${SRCDIR}/CTile.cpp
${SRCDIR}/CTileset.cpp
${SRCDIR}/CUtil.cpp
)

set(HEADER_FILES
${SRCDIR}/CAnchorScenery.h
${SRCDIR}/CAnimation.h
${SRCDIR}/CApp.h
${SRCDIR}/CArea.h
${SRCDIR}/CAsset.h
${SRCDIR}/CButton.h
${SRCDIR}/CCamera.h
${SRCDIR}/CChangeEntity.h
${SRCDIR}/CChangeScenery.h
${SRCDIR}/CChangeTile.h
${SRCDIR}/CEditMap.h
${SRCDIR}/CEntity.h
${SRCDIR}/CEntityData.h
${SRCDIR}/CEntityEditor.h
${SRCDIR}/CError.h
${SRCDIR}/CEvent.h
${SRCDIR}/CFileIO.h
${SRCDIR}/CFont.h
${SRCDIR}/CFPS.h
${SRCDIR}/CHitboxEditor.h
${SRCDIR}/CInform.h
${SRCDIR}/CInterrupt.h
${SRCDIR}/CLayerEditor.h
${SRCDIR}/CMap.h
${SRCDIR}/CMeter.h
${SRCDIR}/CModel.h
${SRCDIR}/CModule.h
${SRCDIR}/COptions.h
${SRCDIR}/CPlanArea.h
${SRCDIR}/CPlanEditor.h
${SRCDIR}/CPlanMap.h
${SRCDIR}/CScenery.h
${SRCDIR}/CSceneryData.h
${SRCDIR}/CSceneryEditor.h
${SRCDIR}/CSimEntity.h
${SRCDIR}/CSimulate.h
${SRCDIR}/CSound.h
${SRCDIR}/CStage.h
${SRCDIR}/CSurface.h
${SRCDIR}/CTerminate.h
${SRCDIR}/CTile.h
${SRCDIR}/CTileset.h
${SRCDIR}/CUtil.h
${SRCDIR}/Define.h
)

set(GCC_COVERAGE_LINK_FLAGS	"-mwindows")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_executable(${TITLE} ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(${TITLE} ${SDL2_MAIN} ${SDL2_LIBRARY} ${SDLIMG_LIBRARY} ${SDLMIX_LIBRARY})
