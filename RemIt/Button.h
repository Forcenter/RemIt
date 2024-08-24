#ifndef BUTTON_
#define BUTTON_

#include "Constants.h"
#include "Event.h"
#include <fstream>
#include "SFML/Graphics.hpp"
#include "WindowField.h"

namespace RemIt {
	class Button {
	private:
		sf::Texture texture;
		//sf::Sprite sprite;
		sf::CircleShape sprite;
		int radius;
		bool isWinEvent = false;

		bool mouseHovered = false;
		bool pressed = false;
		bool eventActivated = false;

		bool isMoving = false;
		bool reverse = true;
		sf::Vector2f position1;
		sf::Vector2f position2;
		sf::Vector2f startingPoint;
		sf::Vector2f targetPoint;
		int animationState = 0;
		int animationDelay = 0;

		Event* fieldEvent;
		WinEvent winEvent = {static_cast<winNames>(4), static_cast<winWhatToDo>(0) };

		void makeHovered();
		void makeBasic();

	public:
		Button(const wchar_t* textureFile, WindowField* field, sf::Vector2f pos, int radius);

		Button(const Button&) = delete;

		Button(Button&&) = delete;

		Button& operator=(const Button&) = delete;

		Button& operator=(Button&&) = delete;

		const WinEvent& update(const sf::Vector2i mousePos);

		const sf::CircleShape& display() { return sprite; }

		bool isPointInButton(const sf::Vector2i&);

		bool press();

		void unPress();

		inline bool isHovered() {
			return mouseHovered;
		}

		inline bool isPressed() { return pressed; }

		inline bool isAnimationReversed() { return reverse; };

		void setPosition(const sf::Vector2f&);
	};
}
#endif

