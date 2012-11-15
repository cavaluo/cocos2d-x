#include "PluginManager.h"
#include <map>
#include <string>

namespace cocos2d { namespace plugin {

typedef std::map<std::string, PluginCreator> PluginCreatorMap;
typedef std::pair<std::string, PluginCreator> PluginCreatorPair;

static PluginCreatorMap* s_pCreatorMap = NULL;

PluginManager::PluginManager(void)
{
}

PluginManager* PluginManager::getInstance()
{
    static PluginManager g_Instance;
    return &g_Instance;
}

IPlugin* PluginManager::getPlugin(const char* name)
{
    IPlugin* pRet = NULL;
    PluginCreatorMap::iterator it = s_pCreatorMap->find(name);
    if (it != s_pCreatorMap->end())
    {
        pRet = it->second();
    }
    return pRet;
}

bool PluginManager::registerPlugin(const char* name, PluginCreator pfnCreator)
{
    static PluginCreatorMap s_creatorMap;
    if (s_pCreatorMap == NULL) {
        s_pCreatorMap = &s_creatorMap;
    }
    s_pCreatorMap->insert(PluginCreatorPair(name, pfnCreator));
    return true;
}

}} //namespace cocos2d { namespace plugin {
