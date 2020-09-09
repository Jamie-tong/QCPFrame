#include "childediter.h"
#include "ui_childediter.h"
#include <QTimer>

ChildEditer::ChildEditer(QCFModel* model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChildEditer)
{
    ui->setupUi(this);

    _core = model;
    this->setParent(parent);

    //去掉问号按钮
    setWindowFlags(Qt::Dialog
                   | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint);

    //禁止调整大小
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(hasHeightForWidth());
    setSizePolicy(sizePolicy);
    setMinimumSize(QSize(949, 620));
    setMaximumSize(QSize(949, 620));
    setSizeGripEnabled(false);

    //注册面板显示后的信号槽
    _timer = new QTimer(this);
    _timer->setSingleShot(true);
    connect(_timer, SIGNAL(timeout()), this, SLOT(slot_OnULoaded()));
}

ChildEditer::~ChildEditer()
{
    delete ui;
}

void ChildEditer::slot_OnULoaded()
{
    foreach(PluginInterface* pi,  _core->I_SysPlugins)
    {

    }
}

