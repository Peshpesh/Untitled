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
${SRCDIR}/CApp_OnMotion.cpp
${SRCDIR}/CApp_OnRender.cpp
${SRCDIR}/CAnimation.cpp
${SRCDIR}/CArea.cpp
${SRCDIR}/CCamera.cpp
${SRCDIR}/CCinema.cpp
${SRCDIR}/CCinema_Debug.cpp
${SRCDIR}/CDialogue.cpp
${SRCDIR}/CEntity.cpp
${SRCDIR}/CEntityCol.cpp
${SRCDIR}/CEntityInfo.cpp
${SRCDIR}/CEntityMod.cpp
${SRCDIR}/CEntityRes.cpp
${SRCDIR}/CEvent.cpp
${SRCDIR}/CFPS.cpp
${SRCDIR}/CGamedata.cpp
${SRCDIR}/CHUD.cpp
${SRCDIR}/CInventory.cpp
${SRCDIR}/CItem.cpp
${SRCDIR}/CItemProcess.cpp
${SRCDIR}/CMap.cpp
${SRCDIR}/CMapEdit.cpp
${SRCDIR}/CME_ChTile.cpp
${SRCDIR}/CME_IO.cpp
${SRCDIR}/CME_NPC.cpp
${SRCDIR}/CME_OnCleanup.cpp
${SRCDIR}/CME_OnClick.cpp
${SRCDIR}/CME_OnEvent.cpp
${SRCDIR}/CME_OnLoop.cpp
${SRCDIR}/CME_OnMotion.cpp
${SRCDIR}/CME_OnRender.cpp
${SRCDIR}/CME_OnStart.cpp
${SRCDIR}/CME_Scenery.cpp
${SRCDIR}/CMenu.cpp
${SRCDIR}/CMEUI.cpp
${SRCDIR}/Config.cpp
${SRCDIR}/CPause.cpp
${SRCDIR}/CPlayer.cpp
${SRCDIR}/CScenery.cpp
${SRCDIR}/CSceneryMod.cpp
${SRCDIR}/CSound.cpp
${SRCDIR}/CSurface.cpp
${SRCDIR}/CTile.cpp
${SRCDIR}/CTitle.cpp
${SRCDIR}/CTransport.cpp
${SRCDIR}/EAcidball.cpp
${SRCDIR}/EBars.cpp
${SRCDIR}/EBloodspikes.cpp
${SRCDIR}/EBomb.cpp
${SRCDIR}/EBox.cpp
${SRCDIR}/EBullet.cpp
${SRCDIR}/EDoor.cpp
${SRCDIR}/EExplode.cpp
${SRCDIR}/EItems.cpp
${SRCDIR}/ESavepoint.cpp
${SRCDIR}/EShop.cpp
${SRCDIR}/ESign.cpp
${SRCDIR}/ESpikefall.cpp
${SRCDIR}/EYoshi_CPU.cpp
${SRCDIR}/Font.cpp
${SRCDIR}/IDebug.cpp
${SRCDIR}/NPCName.cpp
)

set(HEADER_FILES
${SRCDIR}/All_Entities.h
${SRCDIR}/CApp.h
${SRCDIR}/CAnimation.h
${SRCDIR}/CArea.h
${SRCDIR}/CCamera.h
${SRCDIR}/CCinema.h
${SRCDIR}/CCinema_Debug.h
${SRCDIR}/CDialogue.h
${SRCDIR}/CEntity.h
${SRCDIR}/CEntityMod.h
${SRCDIR}/CEntityRes.h
${SRCDIR}/CEvent.h
${SRCDIR}/CFPS.h
${SRCDIR}/CGamedata.h
${SRCDIR}/CHUD.h
${SRCDIR}/CInventory.h
${SRCDIR}/CItem.h
${SRCDIR}/CItemProcess.h
${SRCDIR}/CMap.h
${SRCDIR}/CMapEdit.h
${SRCDIR}/CME_ChTile.h
${SRCDIR}/CME_IO.h
${SRCDIR}/CME_NPC.h
${SRCDIR}/CME_Scenery.h
${SRCDIR}/CME_Resource.h
${SRCDIR}/CMenu.h
${SRCDIR}/CMEUI.h
${SRCDIR}/Config.h
${SRCDIR}/CPause.h
${SRCDIR}/CPlayer.h
${SRCDIR}/CScenery.h
${SRCDIR}/CSceneryMod.h
${SRCDIR}/CSound.h
${SRCDIR}/CSurface.h
${SRCDIR}/CTile.h
${SRCDIR}/CTitle.h
${SRCDIR}/CTransport.h
${SRCDIR}/Define.h
${SRCDIR}/Define_Items.h
${SRCDIR}/EAcidball.h
${SRCDIR}/EBars.h
${SRCDIR}/EBloodspikes.h
${SRCDIR}/EBomb.h
${SRCDIR}/EBox.h
${SRCDIR}/EBullet.h
${SRCDIR}/EDoor.h
${SRCDIR}/EExplode.h
${SRCDIR}/EItems.h
${SRCDIR}/ESavepoint.h
${SRCDIR}/EShop.h
${SRCDIR}/ESign.h
${SRCDIR}/ESpikefall.h
${SRCDIR}/EYoshi_CPU.h
${SRCDIR}/Font.h
${SRCDIR}/IDebug.h
${SRCDIR}/Notes.h
)

set(GCC_COVERAGE_LINK_FLAGS	"-mwindows")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_executable(Untitled ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(Untitled ${SDL2_MAIN} ${SDL2_LIBRARY} ${SDLIMG_LIBRARY} ${SDLMIX_LIBRARY})
