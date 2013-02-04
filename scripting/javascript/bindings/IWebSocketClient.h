//
//  IWebSocketClient.h
//  HelloWebsocketJS
//
//  Created by James Chen on 2/4/13.
//
//

#ifndef HelloWebsocketJS_IWebSocketClient_h
#define HelloWebsocketJS_IWebSocketClient_h

#include <string>

class IWebSocketClient
{
public:
    virtual ~IWebSocketClient();
    
    class ICallback
    {
    public:
        virtual void onopen() = 0;
        virtual void onclose() = 0;
        virtual void onmessage(const std::string& msg) = 0;
        virtual void onerror() = 0;
    };
    
    virtual void send(const std::string& msg) = 0;
    virtual void close() = 0;
    
    void setCallback(ICallback* pfnCallback) { m_pWebSocketCallback = pfnCallback; };
    ICallback* getCallback() { return m_pWebSocketCallback; };
    
protected:
    IWebSocketClient()
    : m_pWebSocketCallback(NULL)
    {}
    
    ICallback* m_pWebSocketCallback;
};

extern IWebSocketClient* __createWebSocket(const std::string& strUrl);

#endif
