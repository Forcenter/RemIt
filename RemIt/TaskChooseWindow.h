#ifndef TASK_CHOOSE_WINDOW_
#define TASK_CHOOSE_WINDOW_

#include "Window.h"
#include "CollapseHorWindowField.h"
#include "StaticWindowField.h"
#include "Button.h"
#include "Event.h"
#include "FilterButton.h"
#include "TaskPlate.h"
#include "AddTaskMiniWindow.h"
#include "addButton.h"
#include <vector>

namespace RemIt {
	class TaskChooseWindow : public Window {
	private:
		static const int fieldAmount = 4;
		enum fieldPurposes {
			background = 0,
			leftBorder = 1,
			topBorder = 2,
			taskBar = 3
		};

		static const int buttonAmount = 4;
		enum buttonPurposes {
			newTask = 0,
			deleteTask = 1,
			searchTask = 2,
			hideTaskBar = 3
		};

		Button** buttons;
		FilterButton* filterButton;

		AddButton addButton;

		AddTaskMiniWindow miniWindowAddTask;

		void processInputs() override;

		void display() override;

		void processAnimations() override;

		WindowField* field[fieldAmount];

		std::vector<TaskPlate> neededToBeDonePlates;
		std::vector<TaskPlate> beingDonePlates;
		std::vector<TaskPlate> donePlates;

		sf::Vector2f taskPlateSize;
		sf::Vector2f taskPlateStartPos = {55, 60};

	public:
		TaskChooseWindow() = default;

		TaskChooseWindow(const TaskChooseWindow&) = delete;

		TaskChooseWindow(TaskChooseWindow && other) = delete;

		TaskChooseWindow& operator=(const TaskChooseWindow&) = delete;

		TaskChooseWindow& operator=(TaskChooseWindow&&) = delete;

		const WinEvent& processEvents() override;

		bool update(std::stack<WinEvent>&) override;

		void loadAsset(std::string assetFilePath) override;

		void createTaskPlates(Task* nTBD, Task* bD, Task* d, int one, int two, int three) override;

		bool isTaskCreated() override;
		const Task& getCreatedTask() override;
	};

	//const int TaskChooseWindow::rectangleAmount = 4;
}

#endif