#include "InputLib.h"
#include <iostream>

#ifdef _DEBUG
#include "..\checkML.h"
#endif // _DEBUG

void InputLib::Init() {
	std::cout << "	|-Initializing Input lib..." << '\n';
}

void InputLib::HandleInput(unsigned char _key, int _x, int _y)
{
	switch (_key) {
	case 27:  // Escape key 
		std::cout << "Exit application.\n";
		EngineCore::ExitApplication();
		break;
	default:
		break;
	}

	EngineCore::GetScene()->HandleInput(_key);
}