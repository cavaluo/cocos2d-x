#ifndef __CCX_PLUGINMANAGER_H__
#define __CCX_PLUGINMANAGER_H__

#include "IPlugin.h"
#include "RegisterPlugin.h"

namespace cocos2d { namespace plugin {

class PluginManager
{
public:
    static PluginManager* getInstance();
    /** get the plugin by name */
    IPlugin* getPlugin(const char* name);
private:
	friend class RegisterPlugin;
	bool registerPlugin(const char* name, PluginCreator pfnCreator);
    PluginManager(void);
};

}} //namespace cocos2d { namespace plugin {

#endif /* __CCX_PLUGINMANAGER_H__ */
