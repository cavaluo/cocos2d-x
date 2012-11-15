#ifndef __CXX_IPLUGIN_H__
#define __CXX_IPLUGIN_H__

#include "RegisterPlugin.h"

namespace cocos2d { namespace plugin {

/**
	The super class for all plugins.
*/

class IPlugin
{
public:
    virtual ~IPlugin() {}
    virtual bool init() { return true; }
protected:
    IPlugin() {}
};

}} //namespace cocos2d { namespace plugin {

#endif /* __CXX_IPLUGIN_H__ */
