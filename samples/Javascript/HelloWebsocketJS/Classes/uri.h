//
//  uri.h
//  socketiocpp
//
//  Created by Young Peter on 1/18/13.
//  Copyright (c) 2013 Young Peter. All rights reserved.
//

#ifndef __socketiocpp__uri__
#define __socketiocpp__uri__

#include <iostream>
#include "socketioclient.h"
#include <assert.h>

namespace socketio {
    class uri
    {
    public:
        uri(std::string &str)
        {            
            LOG("parsing uri:" << str);
            
            std::string::size_type strSize = str.size();
            std::string::size_type start = 0;
            
            if (str.substr(start, 2) == "ws")
            {
                m_protocol = "ws";
                start = 2;
            }
            else if(str.substr(start, 5) == "https")
            {
                m_protocol = "https";
                start = 5;
            }
            else if(str.substr(start, 4) == "http")
            {
                m_protocol = "http";
                start = 4;
            }
            else
            {
                assert(0);//unsupport uri
            }
            
            start += 3;
            
            std::string::size_type pos = str.find("/", start);
            pos = (pos > strSize) ? strSize : pos;
            std::string site = str.substr(start, pos-start);
            
            std::string::size_type siteSize = site.size();
            std::string::size_type siteSplitPos = site.find(":");
            siteSplitPos = (siteSplitPos > siteSize) ? siteSize : siteSplitPos;
            m_host = site.substr(0, siteSplitPos);
            
            if (siteSplitPos == siteSize)
            {
                m_port = (m_protocol == "http") ? 80 : 443;
            }
            else
            {
                m_port = atoi(site.substr(siteSplitPos+1, siteSize).c_str());
            }
            
            LOG("protocol:" << m_protocol);
            LOG("domain:" << m_host);
            LOG("port:" << m_port);
        }
        
        std::string getHost()
        {
            return m_host;
        }
        
        int getPort()
        {
            return m_port;
        }
        
    private:
        std::string m_protocol;
        std::string m_host;
        int m_port;
        std::string m_resource;
    };
}

#endif /* defined(__socketiocpp__uri__) */
