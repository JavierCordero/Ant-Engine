#include "InputLib.h"
#include <iostream>
#ifdef _DEBUG
#include "checkML.h"
#endif // _DEBUG
void InputLib::Init() {
	std::cout << "Initializing Input lib..." << '\n';
}

void InputLib::HandleInput(unsigned char _key, int _x, int _y)
{
	switch (_key) {
	case 27:  // Escape key 
		std::cout << "Exit\n";
		EngineCore::ExitApplication();
		break;
	case '+':
		EngineCore::GetScene()->GetCamera()->scale(+0.01);   // zoom in  
		break;
	case '-':
		EngineCore::GetScene()->GetCamera()->scale(-0.01);   // zoom out
		break;
	case 'l':
		EngineCore::GetScene()->GetCamera()->set3D();
		break;
	case 'o':
		EngineCore::GetScene()->GetCamera()->setAZ();
		break;
	case 'a': //mov izda
		EngineCore::GetScene()->GetCamera()->moveLR(-15);
		break;
	case 'd': //mov dcha
		EngineCore::GetScene()->GetCamera()->moveLR(15);
		break;
	case 'x': //mov back
		EngineCore::GetScene()->GetCamera()->moveFB(15);
		break;
	case 'z': // mov fow
		EngineCore::GetScene()->GetCamera()->moveFB(-15);
		break;
	case 'w': //mov up
		EngineCore::GetScene()->GetCamera()->moveUD(15);
		break;
	case 's': // mov down
		EngineCore::GetScene()->GetCamera()->moveUD(-15);
		break;
	case 'p': //cambio entre orto y persp
		EngineCore::GetScene()->GetCamera()->setPrj();
		break;

	default:
		break;
	}
}