#include "StepUp.h"
#include <QDebug>

StepUp::StepUp()
{

}

void StepUp::run()
{
    int i = 0;

    while(i<50)
    {
        i++;
        qDebug()<<tr("Plugin Thread, StepUp end = ")<<i;
        msleep(100);
    }
}

void StepUp::uper()
{
    int i = 0;

    while(i<10)
    {
        i++;
        qDebug()<<i;
    }
}
