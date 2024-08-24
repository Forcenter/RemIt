#include "AddTaskMiniWindow.h"

void RemIt::AddTaskMiniWindow::setFont(const sf::Font* font){
  AddTaskMiniWindow::font = font;
}

void RemIt::AddTaskMiniWindow::init(const sf::Vector2f& size){
  this->font = font;
  background.setSize(size);
  textFieldBackground.setSize(sf::Vector2f(size.x * 0.9, size.y / 2));
  textField.setFont(*font);
  button.setRadius(size.y / 3);
  button.setOrigin(sf::Vector2f(size.y / 3, size.y / 3));
}

void RemIt::AddTaskMiniWindow::setPosition(const sf::Vector2f& vect){
  background.setPosition(vect);
  textFieldBackground.setPosition(sf::Vector2f(vect.x + textFieldBackground.getSize().x * 0.1, vect.y + textFieldBackground.getSize().y * 0.1));
  textField.setPosition(sf::Vector2f(vect.x + textFieldBackground.getSize().x * 0.1, vect.y + textFieldBackground.getSize().y * 0.1));
  button.setPosition(sf::Vector2f(vect.x * 0.8, vect.y * 0.6));
}

void RemIt::AddTaskMiniWindow::pressedKey(const sf::Keyboard::Key& key){
  std::string str = textField.getString();
  switch (key) {
  case sf::Keyboard::A:
    str.push_back('a');
    break;
  case sf::Keyboard::B:
    str.push_back('b');
    break;
  case sf::Keyboard::C:
    str.push_back('c');
    break;
  case sf::Keyboard::D:
    str.push_back('d');
    break;
  case sf::Keyboard::E:
    str.push_back('e');
    break;
  case sf::Keyboard::F:
    str.push_back('f');
    break;
  case sf::Keyboard::G:
    str.push_back('g');
    break;
  case sf::Keyboard::H:
    str.push_back('h');
    break;
  case sf::Keyboard::I:
    str.push_back('i');
    break;
  case sf::Keyboard::J:
    str.push_back('j');
    break;
  case sf::Keyboard::K:
    str.push_back('k');
    break;
  case sf::Keyboard::L:
    str.push_back('l');
    break;
  case sf::Keyboard::M:
    str.push_back('m');
    break;
  case sf::Keyboard::N:
    str.push_back('n');
    break;
  case sf::Keyboard::O:
    str.push_back('o');
    break;
  case sf::Keyboard::P:
    str.push_back('p');
    break;
  case sf::Keyboard::Q:
    str.push_back('q');
    break;
  case sf::Keyboard::R:
    str.push_back('r');
    break;
  case sf::Keyboard::S:
    str.push_back('s');
    break;
  case sf::Keyboard::T:
    str.push_back('t');
    break;
  case sf::Keyboard::U:
    str.push_back('u');
    break;
  case sf::Keyboard::V:
    str.push_back('v');
    break;
  case sf::Keyboard::W:
    str.push_back('w');
    break;
  case sf::Keyboard::X:
    str.push_back('x');
    break;
  case sf::Keyboard::Y:
    str.push_back('y');
    break;
  case sf::Keyboard::Z:
    str.push_back('z');
    break;
  }

  textField.setString(str);
}

bool RemIt::AddTaskMiniWindow::isInMiniWindow(const sf::Vector2f& pos){
  sf::Vector2f miniWindowPos = background.getPosition();
  sf::Vector2f miniWindowSize = background.getSize();
  return pos.x >= miniWindowPos.x && pos.x <= miniWindowPos.x + miniWindowSize.x && pos.y >= miniWindowPos.y && pos.y <= miniWindowPos.y + miniWindowSize.y;
}

bool RemIt::AddTaskMiniWindow::isInButton(const sf::Vector2f& pos){
  sf::Vector2f buttonPos = button.getPosition();
  float radius = button.getRadius();
  return (buttonPos.x - pos.x) * (buttonPos.x - pos.x) + (buttonPos.y - pos.y) * (buttonPos.y - pos.y) <= radius * radius;
}

void RemIt::AddTaskMiniWindow::pressButton(){
  button.setFillColor(sf::Color(242, 233, 228));
}

void RemIt::AddTaskMiniWindow::open(){
  opened = true;
}

void RemIt::AddTaskMiniWindow::display(sf::RenderWindow& window){
  window.draw(background);
  window.draw(textFieldBackground);
  window.draw(textField);
  window.draw(button);
}
