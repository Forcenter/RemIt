#include "Event.h"
RemIt::SpaceEvent::SpaceEvent(WindowField* affectedRect, Action action): field(affectedRect), action(action){}

bool RemIt::SpaceEvent::activate(){
	if (action == Action::activateAnimation) {
		field->startAnimation();
		return 0;
	}
	if (action == Action::show) {
		field->rect.scale(sf::Vector2f(1, 1));
		return 0;
	}
	if (action == Action::hide) {
		field->rect.scale(sf::Vector2f(1, 1));
		return 0;
	}
}
