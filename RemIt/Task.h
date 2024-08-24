#ifndef TASK_
#define TASK_

#include <string>

namespace RemIt {
	class Task {
	private:
		std::wstring name;
		int state;

	public:
		void incState();

		void setName(const std::wstring&);

		inline const std::wstring& getName() { return name; }

		inline int getState() { return state; }

		bool operator<(const Task& other);
		bool operator>(const Task& other);
		bool operator==(const Task& other);
	};
}

#endif