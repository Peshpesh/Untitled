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
${SRCDIR}/CAnimation.cpp
${SRCDIR}/CApp.cpp
${SRCDIR}/CApp_ext.cpp
${SRCDIR}/CApp_OnCleanup.cpp
${SRCDIR}/CApp_OnEvent.cpp
${SRCDIR}/CApp_OnInit.cpp
${SRCDIR}/CApp_OnLoop.cpp
${SRCDIR}/CApp_OnRender.cpp
${SRCDIR}/CArea.cpp
${SRCDIR}/CAsset.cpp
${SRCDIR}/CAsset_Ext.cpp
${SRCDIR}/CCamera.cpp
${SRCDIR}/CConfig.cpp
${SRCDIR}/CControls.cpp
${SRCDIR}/CDialogue.cpp
${SRCDIR}/CDifficulty.cpp
${SRCDIR}/CEntity_Coll.cpp
${SRCDIR}/CEntity_Move.cpp
${SRCDIR}/CEntity.cpp
${SRCDIR}/CEntityCol.cpp
${SRCDIR}/CEntityData.cpp
${SRCDIR}/CEntityIO.cpp
${SRCDIR}/CEvent.cpp
${SRCDIR}/CFPS.cpp
${SRCDIR}/CGame.cpp
${SRCDIR}/CGame_Event.cpp
${SRCDIR}/CGame_Init.cpp
${SRCDIR}/CGame_Loop.cpp
${SRCDIR}/CGame_Render.cpp
${SRCDIR}/CGameinfo.cpp
${SRCDIR}/CGamedata.cpp
${SRCDIR}/CGameIO.cpp
${SRCDIR}/CGlobal.cpp
${SRCDIR}/CHero.cpp
${SRCDIR}/CHUD.cpp
${SRCDIR}/CInform.cpp
${SRCDIR}/CInterrupt.cpp
${SRCDIR}/CInventory.cpp
${SRCDIR}/CInventory_ext.cpp
${SRCDIR}/CInventory_list.cpp
${SRCDIR}/CLocation.cpp
${SRCDIR}/CMap.cpp
${SRCDIR}/CMapModel.cpp
${SRCDIR}/CMode.cpp
${SRCDIR}/CPause.cpp
${SRCDIR}/CPause_ext.cpp
${SRCDIR}/CScenery.cpp
${SRCDIR}/CSceneryData.cpp
${SRCDIR}/CSceneryIO.cpp
${SRCDIR}/CSound.cpp
${SRCDIR}/CSurface.cpp
${SRCDIR}/CTile.cpp
${SRCDIR}/CTitle.cpp
${SRCDIR}/CTitle_Event.cpp
${SRCDIR}/CTitle_ext.cpp
${SRCDIR}/CTitle_Render.cpp
${SRCDIR}/CTransition.cpp
${SRCDIR}/CType.cpp
${SRCDIR}/CType_def.cpp
${SRCDIR}/stage/CStage.cpp
${SRCDIR}/stage/CDebug.cpp
${SRCDIR}/stage/CYrai.cpp
)

set(HEADER_FILES
${SRCDIR}/CAnimation.h
${SRCDIR}/CApp.h
${SRCDIR}/CArea.h
${SRCDIR}/CAsset.h
${SRCDIR}/CCamera.h
${SRCDIR}/CConfig.h
${SRCDIR}/CControls.h
${SRCDIR}/CDialogue.h
${SRCDIR}/CDifficulty.h
${SRCDIR}/CEntity.h
${SRCDIR}/CEntityData.h
${SRCDIR}/CEntityIO.h
${SRCDIR}/CEvent.h
${SRCDIR}/CFPS.h
${SRCDIR}/CGame.h
${SRCDIR}/CGameinfo.h
${SRCDIR}/CGamedata.h
${SRCDIR}/CGameIO.h
${SRCDIR}/CGlobal.h
${SRCDIR}/CHero.h
${SRCDIR}/CHUD.h
${SRCDIR}/CInform.h
${SRCDIR}/CInterrupt.h
${SRCDIR}/CInventory.h
${SRCDIR}/CLocation.h
${SRCDIR}/CMap.h
${SRCDIR}/CMapModel.h
${SRCDIR}/CMode.h
${SRCDIR}/CPause.h
${SRCDIR}/CScenery.h
${SRCDIR}/CSceneryData.h
${SRCDIR}/CSceneryIO.h
${SRCDIR}/CSound.h
${SRCDIR}/CStages.h
${SRCDIR}/CSurface.h
${SRCDIR}/CTile.h
${SRCDIR}/CTitle.h
${SRCDIR}/CTransition.h
${SRCDIR}/CType.h
${SRCDIR}/Define.h
${SRCDIR}/stage/CStage.h
${SRCDIR}/stage/CDebug.h
${SRCDIR}/stage/CYrai.h
)

set(GCC_COVERAGE_LINK_FLAGS	"-mwindows")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_executable(Untitled ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(Untitled ${SDL2_MAIN} ${SDL2_LIBRARY} ${SDLIMG_LIBRARY} ${SDLMIX_LIBRARY})
