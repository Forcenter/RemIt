#include "FilterButton.h"

RemIt::FilterButton::FilterButton(const sf::Vector2f& pos, int radius):radius(radius){
	sprite.setRadius(radius);
	sprite.setFillColor(sf::Color(255, 255, 255));
	sprite.setOutlineColor(sf::Color(162, 162, 157));
	sprite.setOutlineThickness(0.6);
	sprite.setOrigin(sf::Vector2f(radius, radius));
	sprite.setPosition(pos);
}

void RemIt::FilterButton::incState() {
  ++state;
	if (state > maxState)
		state = 0;
	switch (state){
	case 0:
		sprite.setFillColor(sf::Color(255, 255, 255));
		sprite.setOutlineColor(sf::Color(162, 162, 157));
		break;
	case 1:
		sprite.setFillColor(sf::Color(242, 185, 116));
		sprite.setOutlineColor(sf::Color(138, 109, 87));
		break;
	case 2:
		sprite.setFillColor(sf::Color(242, 124, 124));
		sprite.setOutlineColor(sf::Color(138, 79, 91));
		break;
	case 3:
		sprite.setFillColor(sf::Color(158, 242, 141));
		sprite.setOutlineColor(sf::Color(96, 138, 100));
		break;
	}
}

bool RemIt::FilterButton::isPointInButton(const sf::Vector2i& point){
	sf::Vector2f pos = sprite.getPosition();
	return (pos.x - point.x) * (pos.x - point.x) + (pos.y - point.y) * (pos.y - point.y) <= radius * radius;
}

void RemIt::FilterButton::startFading() {
	reverse = !reverse;
	if (reverse)
		fadingState = animationStateAmount - 1;
	else
		fadingState = 0;
}

sf::CircleShape& RemIt::FilterButton::display() {
	if (fadingState != -1 && fadingState != animationStateAmount) {
		sf::Color outline = sprite.getOutlineColor();
		sf::Color color = sprite.getFillColor();
		sf::Color faded(color.r, color.g, color.b, fadePhases[fadingState]);
		sf::Color fadedOutline(outline.r, outline.g, outline.b, fadePhases[fadingState]);
		sprite.setFillColor(faded);
		sprite.setOutlineColor(fadedOutline);
		if (reverse)
			--fadingState;
		else
			++fadingState;
	}
	return sprite;
}
