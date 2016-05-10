#include "UtilityNPC.h"

UtilityNPC::UtilityNPC(World* pWorld):BaseNPC(pWorld)
{
	//increases value as water gets lower
	m_waterValue.setNormalizationType(UtilityValue::INVERSE_LINEAR);
	m_waterValue.setMinMaxValues(0, 20);
	m_waterValue.setValue((float)getWaterValue());

	m_foodValue.setNormalizationType(UtilityValue::INVERSE_LINEAR);
	m_foodValue.setMinMaxValues(0, 18);
	m_foodValue.setValue((float)getFoodValue());

	m_restValue.setNormalizationType(UtilityValue::INVERSE_LINEAR);
	m_restValue.setMinMaxValues(0,9);
	m_restValue.setValue((float)getRestValue());

	m_logValue.setNormalizationType(UtilityValue::INVERSE_LINEAR);
	m_logValue.setMinMaxValues(0,12);
	m_logValue.setValue((float)getNumberOfLogs());

	UtilityScore* pWaterScore = new UtilityScore();
	pWaterScore->addUtilityValue(&m_waterValue,1.0f);
	m_pUtilityScoreMap["collectWater"] = pWaterScore;

	UtilityScore* pFoodScore = new UtilityScore();
	pFoodScore->addUtilityValue(&m_foodValue,1.0f);
	m_pUtilityScoreMap["collectFood"] = pFoodScore;

	UtilityScore* pRestScore = new UtilityScore();
	pRestScore->addUtilityValue(&m_restValue,1.0f);
	m_pUtilityScoreMap["rest"] = pRestScore;

	UtilityScore* pLogScore = new UtilityScore();
	pLogScore->addUtilityValue(&m_logValue,1.0f);
	m_pUtilityScoreMap["collect log"] = pLogScore;
}

UtilityNPC::~UtilityNPC()
{
}

void UtilityNPC::selectAction(float a_fdeltaTime)
{
	m_waterValue.setValue((float)getWaterValue());
	m_foodValue.setValue((float)getFoodValue());
	m_logValue.setValue((float)getNumberOfLogs());
	m_restValue.setValue((float)getRestValue());

	float fBestScore = 0.0f;
	std::string strBestAction;
	for (auto score : m_pUtilityScoreMap)
	{
		float fThisScore = score.second->getUtilityScore();
		if (fThisScore > fBestScore)
		{
			fBestScore = fThisScore;
			strBestAction = score.first;
		}
	}

	if (strBestAction == "collectWater")
	{
		collectWater(a_fdeltaTime);
	}

	else if (strBestAction == "collectFood")
	{
		collectFood(a_fdeltaTime);
	}

	else if (strBestAction == "rest")
	{
		rest(a_fdeltaTime);
	}

	else if (strBestAction == "collect log")
	{
		chopTree(a_fdeltaTime);
	}
	else
	{
		buildHouse(a_fdeltaTime);
	}
}