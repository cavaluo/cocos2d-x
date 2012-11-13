#include "GameAnalytics.h"

#if (TARGET_ANALYTICS == ANALYTICS_UMENG)
static AnalyticsUmeng* s_pGameAnalytics = NULL;

AnalyticsUmeng* GameAnalytics::getAnalytics()
{
	if (s_pGameAnalytics == NULL) {
		s_pGameAnalytics = new AnalyticsUmeng();
	}
	return s_pGameAnalytics;
}
#elif (TARGET_ANALYTICS == ANALYTICS_FLURRY)

static AnalyticsFlurry* s_pGameAnalytics = NULL;

AnalyticsFlurry* GameAnalytics::getAnalytics()
{
	if (s_pGameAnalytics == NULL) {
		s_pGameAnalytics = new AnalyticsFlurry();
	}
	return s_pGameAnalytics;
}
#endif

void GameAnalytics::destory()
{
	if (s_pGameAnalytics != NULL) {
		delete s_pGameAnalytics;
		s_pGameAnalytics = NULL;
	}
}