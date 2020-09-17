#include "stepdown.h"
#include <QDebug>

StepDown::StepDown()
{

}

void StepDown::run()
{
    int i = 100;

    while(i>0)
    {
        i--;
        qDebug()<<tr("Plugin Thread, StepDown end = ")<<i;
        msleep(100);
    }
}
