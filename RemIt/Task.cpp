#include "Task.h"

void RemIt::Task::incState(){
  ++state;
  if (state == 3)
    state = 0;
}

void RemIt::Task::setName(const std::wstring& name) {
  this->name = name;
}

bool RemIt::Task::operator<(const Task& other){
  return name < other.name;
}

bool RemIt::Task::operator>(const Task& other){
  return name > other.name;
}

bool RemIt::Task::operator==(const Task& other){
  return name == other.name;
}
