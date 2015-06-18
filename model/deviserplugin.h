#ifndef DEVISERPLUGIN_H
#define DEVISERPLUGIN_H

#include <model/deviserbase.h>

class DeviserPlugin : public DeviserBase
{
public:
    DeviserPlugin();
    DeviserPlugin(const DeviserPlugin& other) {}

        virtual void initializeFrom(const QDomElement& element) {}
};

#endif // DEVISERPLUGIN_H
