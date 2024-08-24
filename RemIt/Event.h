#ifndef EVENT_
#define EVENT_

#include "Constants.h"
#include "windowField.h"
#include "SFML/Graphics.hpp"

namespace RemIt {
	class Event {
	public:
		virtual bool activate() = 0;
	};

	class SpaceEvent : public Event {
	public:
		enum class Action {
			show,
			hide,
			activateAnimation
		};

		SpaceEvent(WindowField* affectedRectangle, Action action);

		bool activate() override;

	private:
		WindowField* field;
		Action action;
	};
}

#endif