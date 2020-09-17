#ifndef STEPDOWN_H
#define STEPDOWN_H

#include "PluginIO.h"
#include <QThread>

class StepDown : public QThread
{
public:
    StepDown();

protected:
    void run();
};

#endif // STEPDOWN_H
