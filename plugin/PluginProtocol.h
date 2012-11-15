#ifndef __CXX_IPLUGIN_H__
#define __CXX_IPLUGIN_H__

#include "RegisterPlugin.h"

namespace cocos2d { namespace plugin {

/**
	The super class for all plugins.
*/

class PluginProtocol
{
public:
    virtual ~PluginProtocol() {}
    virtual bool init() { return true; }
protected:
    PluginProtocol() {}
};

}} //namespace cocos2d { namespace plugin {

#endif /* __CXX_IPLUGIN_H__ */
