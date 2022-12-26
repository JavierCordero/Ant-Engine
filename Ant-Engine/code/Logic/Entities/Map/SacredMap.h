#pragma once

#include "../../../EngineCore/LogicEngine/Map.h"

class SacredMap : public Map
{
public:
	SacredMap();
	virtual ~SacredMap() {};

	inline virtual void IntializeMap() { Map::InitializeMap(); };
};

