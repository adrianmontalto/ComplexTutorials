#pragma once
#include "BaseNPC.h"
#include "UtilityValue.h"
#include "UtilityScore.h"
#include <map>

using namespace UtilitySystem;

class UtilityNPC :public BaseNPC
{
public:
	UtilityNPC(World* pWorld);
	~UtilityNPC();
protected:
	void selectAction(float a_fdeltaTime)override;
private:
	UtilityValue m_waterValue;
	UtilityValue m_logValue;
	UtilityValue m_foodValue;
	UtilityValue m_restValue;
	UtilityValue m_houseValue;
	std::map<std::string, UtilityScore*>m_pUtilityScoreMap;
};

