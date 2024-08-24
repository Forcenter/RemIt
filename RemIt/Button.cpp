#include "Button.h"

RemIt::Button::Button(const wchar_t* textureFile, WindowField* field, sf::Vector2f pos, int radius): radius(radius) {
	std::ifstream fin;
	fin.open(textureFile);
	sprite.setFillColor(sf::Color(242, 233, 228));
	sprite.setOutlineColor(sf::Color(138, 133, 143));
	sprite.setOutlineThickness(0.6);
	sprite.setRadius(radius);
	sprite.setOrigin(sf::Vector2f(radius, radius));
	sprite.setPosition(pos);
	fieldEvent = new SpaceEvent(field, SpaceEvent::Action::activateAnimation);
	position2 = pos;
	fin >> pos.x >> pos.y;
	position1 = pos;
}

const RemIt::WinEvent& RemIt::Button::update(const sf::Vector2i mousePos) {
	sf::Vector2f pos = sprite.getPosition();
	if (isPointInButton(mousePos))
		makeHovered();
	else
		makeBasic();

	if (isMoving) {
		if (animationDelay < ANIMATION_DELAY)
			++animationDelay;
		else {
			setPosition(startingPoint + (targetPoint - startingPoint) * animationPhases[animationState]);
			++animationState;
			if (animationState == animationStateAmount)
				isMoving = false;
		}
	}

	if (pressed && !eventActivated) {
		eventActivated = true;
		if (position1 != position2) {
			isMoving = true;
			animationState = 0;
			animationDelay = 0;
			reverse = !reverse;
			startingPoint = sprite.getPosition();
			if (reverse)
				targetPoint = position2;
			else
				targetPoint = position1;
		}
		if (!isWinEvent)
			fieldEvent->activate();
		else
			return winEvent;
	}
	return WinEvent{ winNames::none, winWhatToDo::none };
}

bool RemIt::Button::press() {
	if (mouseHovered) {
		sprite.setFillColor(sf::Color(182, 173, 168));
		pressed = true;
		return true;
	}
	return false;
}

void RemIt::Button::unPress() {
	pressed = false;
	eventActivated = false;
	if (mouseHovered)
		sprite.setFillColor(sf::Color(212, 203, 198));
}

bool RemIt::Button::isPointInButton(const sf::Vector2i& point){
	sf::Vector2f pos = sprite.getPosition();
	return (pos.x - point.x) * (pos.x - point.x) + (pos.y - point.y) * (pos.y - point.y) <= radius * radius;
}

void RemIt::Button::makeHovered(){
	if (!mouseHovered) {
		sprite.setFillColor(sf::Color(212, 203, 198));
		mouseHovered = true;
	}
}

void RemIt::Button::makeBasic(){
	if (mouseHovered) {
		sprite.setFillColor(sf::Color(242, 233, 228));
		mouseHovered = false;
	}
}

void RemIt::Button::setPosition(const sf::Vector2f& vect){
	sprite.setPosition(vect);
}