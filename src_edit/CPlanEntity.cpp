#include "CPlanEntity.h"

CPlanEntity CPlanEntity::control;

CPlanEntity::CPlanEntity() {

}

bool CPlanEntity::OnInit() {
  return true;
}

void CPlanEntity::setK(const int& k) {
  this->k = k;
}

void CPlanEntity::getK(int& k) {
  k = this->k;
}

void CPlanEntity::OnTerminate() {

}
