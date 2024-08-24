#include "App.h"
#include <windows.h>

int main() {
	setlocale(LC_ALL, "Russian");
	RemIt::App app("asset.txt");
	while (app.update()) {
		
	}
}