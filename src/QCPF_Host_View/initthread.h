#ifndef INITTHREAD_H
#define INITTHREAD_H

#include <QObject>
#include <QThread>
#include "../QCPF_Model/qcpf_model.h"


class InitThread : public QThread
{
    Q_OBJECT
public:
    InitThread(QCPF_Model* core, QObject *parent = nullptr);

signals:

protected:
    virtual void run();

public:
    QCPF_Model* _core;
};

#endif // INITTHREAD_H
