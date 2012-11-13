#ifndef __CCX_ANALYTICS_PROTOCOL_H__
#define __CCX_ANALYTICS_PROTOCOL_H__

#include <map>
#include <string>

namespace cocos2d { namespace plugin {

typedef std::pair< std::string, std::string >   LogEventParamPair;
typedef std::map< std::string, std::string >    LogEventParamMap;

class AnalyticsProtocol
{
public:
	/** Start a new session. */
	virtual void startSession(const char* appKey);
	/** Stop a session. */
	virtual void stopSession();
	/** Set the timeout for expiring a session. */
	virtual void setSessionContinueMillis(long millis);
	/** Whether to catch uncaught exceptions to server.*/
	virtual void setCaptureUncaughtException(bool isEnabled);
	/** Set whether needs to output logs to console.*/
	virtual void setDebugMode(bool isDebugMode);
	/** log an error */
	virtual void logError(const char* errorId, const char* message, const LogEventParamMap* pParams = NULL);
	/** log an event. */
	virtual void logEvent(const char* eventId, const LogEventParamMap* pParams = NULL);
	/** begin to log a timed event */
	virtual void logTimedEventBegin(const char* eventId);
	/** end a timed event */
	virtual void logTimedEventEnd(const char* eventId);

protected:
	AnalyticsProtocol();
public:
	virtual ~AnalyticsProtocol();
};

}} // namespace cocos2d { namespace plugin {


#endif /* __CCX_ANALYTICS_PROTOCOL_H__ */
