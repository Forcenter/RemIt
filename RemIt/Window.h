#ifndef WINDOW_
#define WINDOW_

#include "Constants.h"
#include "Task.h"
#include "Event.h"
#include "SFML/Graphics.hpp"
#include <fstream>
#include <string>
#include <stack>

namespace RemIt {
	class Window {
	protected:
		sf::RenderWindow window;

		int openedTime = 0; //Cannot be bigger than TIMER_MAX_VALUE in order not to get out of int values; + 1 each update

		bool active = false;
		bool lockedOnMouse = false;

		sf::Vector2i lastMousePosition = {};

		virtual void processInputs() = 0;

		void loadWindowAsset(std::wifstream& stream);

		virtual void display() = 0;

		virtual void processAnimations() = 0;

	public:

		Window() = default;

		Window(const Window&) = delete;

		Window(Window&& other) = delete;

		Window& operator=(const Window&) = delete;

		Window& operator=(Window&&) = delete;

		inline bool isActive() { return active; };

		virtual bool update(std::stack<WinEvent>&) = 0;

		void makeActive(sf::Vector2i pos);

		void makeInactive();

		const sf::Vector2i& getPosition();

		virtual const WinEvent& processEvents() = 0;

		virtual void loadAsset(std::string assetFilePath) = 0;

		virtual void createTaskPlates(Task* nTBD, Task* bD, Task* d, int one, int two, int three) = 0;

		virtual inline bool isTaskCreated() = 0;
		virtual const Task& getCreatedTask() = 0;

		virtual ~Window() = default;
	};
}

#endif

