#include "EngineCore/EngineCore.h"

//TO REMOVE
#include "Logic/Scenes/SacredWorldScene.h"
//TO REMOVE
#include <iostream>

#ifdef _DEBUG
#include "EngineCore/checkML.h"
#endif // _DEBUG

using namespace std;

int main(int argc, char* argv[])
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(187);
#endif // _DEBUG

	cout << "Starting Sacred Project..." << '\n';

	//Inicializa los sistemas principales del engine
	EngineCore::InitEngine(argc, argv);

	//Arranca el engine con una escena concreta
	EngineCore::StartEngine(new SacredWorldScene());

	//Cierra el engine y libera toda la memoria
	EngineCore::StopEngine();

	return 0;
}
