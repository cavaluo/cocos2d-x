//
//  WSClient.h
//  HelloWebsocketJS
//
//  Created by James Chen on 2/4/13.
//
//

#ifndef __HelloWebsocketJS__WSClient__
#define __HelloWebsocketJS__WSClient__

#include <string>
#include <iostream>
#include "libwebsockets.h"
#include "IWebSocketClient.h"

using std::string;

#define LOG(str) std::cout << str << std::endl;

namespace socketio {
    enum socketio_handshake_result {
        SOCKETIO_HANDSHAKE_401_UNAUTHORIZED = 401,
        SOCKETIO_HANDSHAKE_503_SERVICE_UNAVAILABLE = 503,
        SOCKETIO_HANDSHAKE_200_OK = 200,
    };
    
    enum socketio_protocol_version {
        SOCKETIO_PROTOCOL_VERSION_1 = 1,
    };
    
    enum message_type {
        MESSAGE_DISCONNECT = 0,
        MESSAGE_CONNECT,
        MESSAGE_HEARTBEAT,
        MESSAGE_MESSAGE,
        MESSAGE_JSON,
        MESSAGE_EVENT,
        MESSAGE_ACK,
        MESSAGE_ERROR,
        MESSAGE_NOOP,
    };
    
    class WSClient : public IWebSocketClient
    {
    public:
        
        void connect(const std::string& strUrl);
        void read();
        
        
        void send(message_type type, int msgId = 0, std::string endpoint = "", std::string msgData = "");
        //MESSAGE_DISCONNECT
        void sendDisconnect(string endpoint = "");
        //MESSAGE_CONNECT
        void sendConnect(string endpoint, string query = "");
        //MESSAGE_HEARTBEAT
        void sendHeartBeat();
        //MESSAGE_MESSAGE
        void sendMessage(string msgData, int msgId = 0, string endpoint = "");
        //MESSAGE_JSON
        //void sendJSON(Document &json, int msgId = 0, string endpoint = "");
        //MESSAGE_EVENT
        //void sendEvent(std::string name, Document &args, int msgId = 0, std::string endpoint = "");
        void emit(std::string event, std::string arg0, std::string endpoint = "", std::string callback = NULL);
        //void emit(std::string event, Document &args, std::string endpoint = "", std::string callback = NULL);
        //MESSAGE_ACK
        void sendACK(int msgId, std::string data = "");
        //MESSAGE_ERROR
        void sendError(std::string endpoint = "", std::string reason = "", std::string advice = "");
        //MESSAGE_NOOP
        void sendNoop();
        
        // To implement the interface of IWebSocketClient.
        virtual void send(const std::string& msg);
        virtual void close();
        
    private:
        WSClient();
        
    private:
        std::string m_sessionid;
        unsigned int m_heartbeatTimeout;
        unsigned int m_disconnectTimeout;
        std::string m_resource;
        socketio_protocol_version m_version;
        std::string m_socketIoUri;
        std::string m_transport;
        
        bool m_connected;
        
        std::string m_host;
        int m_port;
        
        struct libwebsocket_context *m_context;
        struct libwebsocket *m_socket;
    };
}


#endif /* defined(__HelloWebsocketJS__WSClient__) */
