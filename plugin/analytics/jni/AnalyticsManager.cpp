#include "AnalyticsManager.h"

namespace cocos2d { namespace plugin {

static AnalyticsUmeng* s_pAnalyticsUmeng = NULL;
static AnalyticsFlurry* s_pAnalyticsFlurry = NULL;
static AnalyticsType s_eAnalytics = kAnalyticsType_Umeng;

void AnalyticsManager::setAnalyticsType(AnalyticsType type)
{
	s_eAnalytics = type;
}

AnalyticsType AnalyticsManager::getAnalyticsType()
{
	return s_eAnalytics;
}

AnalyticsProtocol* AnalyticsManager::getAnalytics()
{
	AnalyticsProtocol* pRet = NULL;
	if (s_eAnalytics == kAnalyticsType_Umeng)
	{
		if (s_pAnalyticsUmeng == NULL) {
			s_pAnalyticsUmeng = new AnalyticsUmeng();
		}
		pRet = s_pAnalyticsUmeng;
	}
	else if(s_eAnalytics == kAnalyticsType_Flurry)
	{
		if (s_pAnalyticsFlurry == NULL) {
			s_pAnalyticsFlurry = new AnalyticsFlurry();
		}
		pRet = s_pAnalyticsFlurry;
	}
	return pRet;
}

void AnalyticsManager::destory()
{
	if (s_pAnalyticsUmeng != NULL) {
		delete s_pAnalyticsUmeng;
		s_pAnalyticsUmeng = NULL;
	}

	if (s_pAnalyticsFlurry != NULL) {
		delete s_pAnalyticsFlurry;
		s_pAnalyticsFlurry = NULL;
	}
}

}} //namespace cocos2d { namespace plugin {
