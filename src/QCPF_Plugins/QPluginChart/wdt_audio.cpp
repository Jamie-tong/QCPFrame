#include "wdt_audio.h"
#include "ui_wdt_audio.h"

#include "widget.h"
#include <QtWidgets/QMessageBox>
#include <QtMultimedia/QAudioDeviceInfo>

wdt_Audio::wdt_Audio(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wdt_Audio)
{
    ui->setupUi(this);

    const QAudioDeviceInfo inputDevice = QAudioDeviceInfo::defaultInputDevice();
    if (inputDevice.isNull()) {
        QMessageBox::warning(nullptr, "audio",
                             "There is no audio input device available.");
        return;
    }

    Widget* w = new Widget(inputDevice);

    ui->gridLayout->addWidget(w);
}

wdt_Audio::~wdt_Audio()
{
    delete ui;
}
