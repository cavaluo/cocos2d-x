#ifndef __CCX_ANALYTICS_H__
#define __CCX_ANALYTICS_H__

#include <map>
#include <string>

namespace cocos2d { namespace plugin {

class AnalyticsProtocol
{
public:
	typedef std::pair< std::string, std::string >   EventParamPair;
	typedef std::map< std::string, std::string >    EventParamMap;

	virtual ~AnalyticsProtocol();
public:
	/** Begin a new session. */
	virtual void beginSession(const char* appKey);
	/** End a session. */
	virtual void endSession();
	/** Set the timeout for expiring a session. */
	virtual void setSessionContinueMillis(long millis);
	/** Whether to catch uncaught exceptions to server.*/
	virtual void setCaptureUncaughtException(bool isEnabled);
	/** Set whether needs to output logs to console.*/
	virtual void setDebugMode(bool isDebugMode);
	/** log an error */
	virtual void logError(const char* errorId, const char* message, const EventParamMap* pParams = NULL);
	/** log an event. */
	virtual void logEvent(const char* eventId, const EventParamMap* pParams = NULL);
	/** begin to log a timed event */
	virtual void logTimedEventBegin(const char* eventId, const EventParamMap* pParams = NULL);
	/** end a timed event */
	virtual void logTimedEventEnd(const char* eventId);

};

}} // namespace cocos2d { namespace plugin {


#endif /* __CCX_ANALYTICS_H__ */
