#include "Window.h"

void RemIt::Window::loadWindowAsset(std::wifstream& stream) {
	int width = 0;
	int height = 0;
	int style = 7;
	std::wstring name;
	stream >> name;
	stream >> width;
	stream >> height;
	stream >> style;
	window.create(sf::VideoMode(width, height), name, style);
	window.setFramerateLimit(FRAMERATE);
	window.setVisible(false);
}

void RemIt::Window::makeActive(sf::Vector2i pos) {
	//pos.x -= window.getSize().x;
	window.setPosition(pos);
	window.setVisible(true);
}

void RemIt::Window::makeInactive() {
	window.setVisible(false);
}

const sf::Vector2i& RemIt::Window::getPosition(){
	return window.getPosition();
}