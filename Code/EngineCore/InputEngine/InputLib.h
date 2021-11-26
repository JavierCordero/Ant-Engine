#pragma once
#include "EngineCore.h"

static class InputLib
{
public:

	static void Init();
	static void HandleInput(unsigned char _key, int _x, int _y);
};

