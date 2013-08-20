/*
 * Copyright (C) 2012 armite@126.com. All Rights Reserved.
 */


#include "config.h"
#include "PluginData.h"

#include "PluginDatabase.h"
#include "PluginMainThreadScheduler.h"
#include <runtime/JSLock.h>
#include "NotImplemented.h"

namespace WebCore {

void PluginData::initPlugins(const Page* page)
{
    PluginDatabase *db = PluginDatabase::installedPlugins();
    const Vector<PluginPackage*> plugins = db->plugins();

    m_plugins.resize(plugins.size());
    for (unsigned i = 0; i < plugins.size(); ++i) {
        PluginPackage* package = plugins[i];

        m_plugins[i].name = package->name();
        m_plugins[i].file = package->fileName();
        m_plugins[i].desc = package->description();

        const MIMEToDescriptionsMap& mimeToDescriptions = package->mimeToDescriptions();
        unsigned j=0;
        m_plugins[i].mimes.resize(mimeToDescriptions.size());
        MIMEToDescriptionsMap::const_iterator end = mimeToDescriptions.end();
        for (MIMEToDescriptionsMap::const_iterator it = mimeToDescriptions.begin(); it != end; ++it) {
            m_plugins[i].mimes[j].type = it->key;
            m_plugins[i].mimes[j].desc = it->value;
            m_plugins[i].mimes[j].extensions = package->mimeToExtensions().get(m_plugins[i].mimes[j].type);
            j++;
        }
    }
}

void PluginData::refresh()
{
    notImplemented();
}

}



