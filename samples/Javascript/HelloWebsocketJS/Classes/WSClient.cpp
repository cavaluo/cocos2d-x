//
//  WSClient.cpp
//  HelloWebsocketJS
//
//  Created by James Chen on 2/4/13.
//
//

#include "WSClient.h"
#include "curl/curl.h"
#include <string>
#include <sstream>
#include <vector>
#include "uri.h"

using namespace std;

namespace socketio {
    
size_t writeData(void *ptr, size_t size, size_t nmemb, void *stream)
{
    std::vector<char> *recvBuffer = (std::vector<char>*)stream;
    size_t sizes = size * nmemb;
    
    recvBuffer->insert(recvBuffer->end(), (char*)ptr, (char*)ptr+sizes);
    
    return sizes;
}

static int
callback_socketio(struct libwebsocket_context *_this,
                  struct libwebsocket *wsi,
                  enum libwebsocket_callback_reasons reason,
                  void *user, void *in, size_t len)
{
    switch (reason) {
        case LWS_CALLBACK_CLOSED:
            fprintf(stderr, "closed \n");
            break;
        case LWS_CALLBACK_CLIENT_ESTABLISHED:
            libwebsocket_callback_on_writable(_this, wsi);
            fprintf(stderr, "client established\n");
            break;
        case LWS_CALLBACK_CLIENT_RECEIVE:
            fprintf(stderr, "rx %d '%s' \n", (int)len, (char *)in);
            break;
        default:
            break;
    }
    
    return 0;
}

static struct libwebsocket_protocols protocols[] = {
    {
        "socketio-protocol",
        callback_socketio,
        0,
    },
    {
        NULL,
        NULL,
        0,
    }
};

IWebSocketClient* __createWebSocket(const std::string& strUrl)
{
    WSClient* pRet =  new WSClient();
    pRet->connect(strUrl);
    
    return pRet;
}
    
WSClient::WSClient()
{
    
}

void WSClient::connect(const std::string& strUrl)
{
    m_context = libwebsocket_create_context(CONTEXT_PORT_NO_LISTEN,
                                            NULL,
                                            protocols,
                                            libwebsocket_internal_extensions,
                                            NULL, NULL, NULL,
                                            -1, -1, 0, NULL);
    
    char path[1024];
    sprintf(path, "%s/%d/%s/%s", m_resource.c_str(),
            m_version, m_transport.c_str(),
            m_sessionid.c_str());
    
    m_socket = libwebsocket_client_connect(m_context,
                                           m_host.c_str(),
                                           m_port, false, path,
                                           m_host.c_str(), m_host.c_str()
                                           , protocols[0].name, -1);
}

void WSClient::read()
{
    libwebsocket_service(m_context, 0);
}

void WSClient::send(message_type type,
                     int msgId /* =0 */,
                     std::string endpoint /* ="" */,
                     std::string msgData /* ="" */)
{
    stringstream rawStream;
    if (msgId == 0)
    {
        rawStream << type << ":" << "" << ":" << endpoint;
    }
    else
    {
        rawStream << type << ":" << msgId << ":" << endpoint;
    }
    if (msgData != "")
    {
        rawStream << ":" << msgData;
    }
    
    string rawMessage = rawStream.str();
    const char *rawChar = rawMessage.c_str();
    
    // TODO:: is 1024 big enough???
    char buf1[1024] = {0};
    char buf2[1024] = {0};
    
    memset(buf1, 0, sizeof(buf1));
    memset(buf2, 0, sizeof(buf2));
    
    snprintf(buf2, sizeof(buf2), rawChar);
    strcpy(&buf1[LWS_SEND_BUFFER_PRE_PADDING], buf2);
    
    LOG("send : '" << buf2 << "'");
    
    libwebsocket_write(m_socket,
                       (unsigned char*)&buf1[LWS_SEND_BUFFER_PRE_PADDING],
                       strlen(buf1+LWS_SEND_BUFFER_PRE_PADDING),
                       LWS_WRITE_TEXT);
}

void WSClient::sendDisconnect(string endpoint /*=""*/)
{
    send(MESSAGE_DISCONNECT, 0, endpoint);
}

void WSClient::sendConnect(string endpoint, string query)
{
    stringstream ss;
    ss << endpoint;
    if (query != "")
    {
        ss << "?" << query;
    }
    
    send(MESSAGE_CONNECT, 0, ss.str());
}

void WSClient::sendHeartBeat()
{
    send(MESSAGE_HEARTBEAT);
}

void WSClient::sendMessage( string msgData,int msgId /* =0 */, string endpoint /* = "" */)
{
    send(MESSAGE_MESSAGE, msgId, endpoint, msgData);
}

void WSClient::send(const std::string& msg)
{
    sendMessage(msg);
}

void WSClient::close()
{
    sendDisconnect();
}
    
} //namespace socketio {
