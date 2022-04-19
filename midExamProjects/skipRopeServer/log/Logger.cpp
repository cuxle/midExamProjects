#include "Logger.h"

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QHash>
#include <QObject>

QSharedPointer<QFile> Logger::logFile = Q_NULLPTR;
bool Logger::isInit = false;
QHash<QtMsgType, QString> Logger::contextNames = {
	{QtMsgType::QtDebugMsg,		" Debug  "},
	{QtMsgType::QtInfoMsg,		"  Info  "},
	{QtMsgType::QtWarningMsg,	"Warning "},
	{QtMsgType::QtCriticalMsg,	"Critical"},
	{QtMsgType::QtFatalMsg,		" Fatal  "}
};

void Logger::init() {
	if (isInit) {
        return;
	}
	
	// Create log file
    logFile = QSharedPointer<QFile>(new QFile);
    logFile->setFileName("./MyLog.log");

    if (logFile->open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << __func__ << __LINE__ << "open file success";
    } else {
        qDebug() << __func__ << __LINE__ << "open file success";
    }

	// Redirect logs to messageOutput
	qInstallMessageHandler(Logger::messageOutput);

	// Clear file contents
	logFile->resize(0);

	Logger::isInit = true;
}

void Logger::clean() {

}

void Logger::messageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg) {


    QString log = QObject::tr("%1 | %2 | %3 | %4 | %5 | %6\n").
        arg(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss")).
        arg(Logger::contextNames.value(type)).
        arg(context.line).
        arg(QString(context.file).
            section('\\', -1)).			// File name without file path
        arg(QString(context.function).
            section('(', -2, -2).		// Function name only
            section(' ', -1).
            section(':', -1)).
        arg(msg);


    if (!logFile.isNull() && logFile->isOpen()) {
        logFile->write(msg.toLocal8Bit());
        logFile->write("\n");
    }
}

void Logger::destroy()
{
    logFile->close();
    logFile->deleteLater();
}
