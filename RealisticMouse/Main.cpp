#include "RunMouse.h"
#include <Windows.h>

int main(){

	RunMouse * Mouse = new RunMouse();

	while (true){
		//0x20 == spacebar
		if (GetAsyncKeyState(0x20)){
			Mouse -> MoveMouse(1825, 50);
		}

		//500ms delay between click
		Sleep(500);
	}

	delete Mouse;
}