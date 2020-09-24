#include "initthread.h"

InitThread::InitThread(QCPF_Model* core, QObject *parent) : QThread(parent)
{
    _core = core;
}


void InitThread::run()
{
    _core->slot_Initialize();
}
