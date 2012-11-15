#ifndef __CXX_REGISTERPLUGIN_H__
#define __CXX_REGISTERPLUGIN_H__

namespace cocos2d { namespace plugin {

class IPlugin;

typedef IPlugin* (*PluginCreator)();

/**
	@brief RegisterPlugin class is only for associating plugin name with plugin creator.
	Plugin developers don't need to use this class directly.
	Using the macros 'PLUGIN_REGISTER_DECL' and 'PLUGIN_REGISTER_IMPL' instead.
*/
class RegisterPlugin
{
public:
    RegisterPlugin(const char* name, PluginCreator pfnCreator);
};

#define PLUGIN_REGISTER_DECL() \
    public: static IPlugin* createPlugin();

#define PLUGIN_REGISTER_IMPL(type, name) \
static RegisterPlugin s_registerPlugin(name, type::createPlugin); \
IPlugin* type::createPlugin() { \
    type* pRet = new type(); \
    if (pRet) { \
        if (!pRet->init()) { \
            delete pRet; pRet = NULL; \
        } \
    } \
    return pRet; \
}

}} //namespace cocos2d { namespace plugin {

#endif /* __CXX_REGISTERPLUGIN_H__ */
