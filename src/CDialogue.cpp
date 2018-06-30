#include "CDialogue.h"

CDialogue CDialogue::control;
std::vector<CPhrase> CDialogue::convo;

CDialogue::CDialogue() {

}

void CDialogue::OnEvent(SDL_Event* Event) {
  CEvent::OnEvent(Event);
}

void CDialogue::OnLoop() {

}

void CDialogue::OnRender() {

}
