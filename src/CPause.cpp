#include "CPause.h"

CPause CPause::control;

CPause::CPause() {
	reinit();
}

void CPause::reinit() {
	menu_kind = .......;
	pos = 0;
}

void CPause::OnEvent(SDL_Event* Event) {

}

bool CPause::OnRender() {
	return true;
}
