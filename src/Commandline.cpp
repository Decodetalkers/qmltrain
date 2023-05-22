#include "Commandline.h"

#include <QDebug>
#include <QProcess>

CommandLineGet::CommandLineGet(QObject *parent)
  : QObject(parent)
{
}

void
CommandLineGet::getOutput()
{
    QProcess *process = new QProcess(this);
    connect(process, &QProcess::finished, this, [this, process](int, QProcess::ExitStatus) {
        auto output     = process->readAllStandardOutput();
        QString message = QString::fromLocal8Bit(output);
        Q_EMIT outPuts(message);
    });
    process->start("ls", {"-la", "/"});
    qDebug() << "Output get";
}
