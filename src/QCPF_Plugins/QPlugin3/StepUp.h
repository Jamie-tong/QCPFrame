#ifndef QPLUGIN3_H
#define QPLUGIN3_H

#include <QThread>

class StepUp : public QThread
{
    Q_OBJECT
public:
    StepUp();
protected:
    void run() override;
public slots:
        void uper();
};

#endif // QPLUGIN3_H
