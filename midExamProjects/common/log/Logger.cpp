#include "Logger.h"

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QHash>
#include <QObject>
#include <QDateTime>
#include "log4qt/log4qt.h"
#include "log4qt/basicconfigurator.h"
#include "log4qt/rollingfileappender.h"
#include "log4qt/patternlayout.h"
#include "log4qt/propertyconfigurator.h"
#include <QApplication>

#include "log4qt/logger.h"

QHash<QtMsgType, QString> Logger::contextNames = {
	{QtMsgType::QtDebugMsg,		" Debug  "},
	{QtMsgType::QtInfoMsg,		"  Info  "},
	{QtMsgType::QtWarningMsg,	"Warning "},
	{QtMsgType::QtCriticalMsg,	"Critical"},
	{QtMsgType::QtFatalMsg,		" Fatal  "}
};

void Logger::init() {

    QString path = QApplication::applicationDirPath() + "/log4qt.properties";
    QFile file(path);
    qDebug() << "path dir:" << path << file.exists();
    Log4Qt::PropertyConfigurator::configure(path);

    installMessageOut();
}

void Logger::installMessageOut()
{
    qInstallMessageHandler(Logger::messageOutput);
    initStartTag();
}

void Logger::initStartTag()
{
    QString format = "yyyy-MM-dd hh:mm:ss.zzz";
    QString data = QDateTime::currentDateTime().toString(format);
    qInfo() << (QStringLiteral("################################################################"));
    qInfo() << (QStringLiteral("#                          START : ")) << data;
    qInfo() << (QStringLiteral("################################################################"));
}

void Logger::initStoptTag()
{
    QString format = "yyyy-MM-dd hh:mm:ss.zzz";
    QString data = QDateTime::currentDateTime().toString(format);
    qInfo() << (QStringLiteral("################################################################"));
    qInfo() << (QStringLiteral("#                          End : ")) << data;
    qInfo() << (QStringLiteral("################################################################"));
}

void Logger::messageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg) {

//	QString log = QObject::tr("%1 | %2 | %3 | %4 | %5 | %6\n").
//		arg(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss")).
//        arg(MyLogger::contextNames.value(type)).
//		arg(context.line).
//		arg(QString(context.file).
//			section('\\', -1)).			// File name without file path
//		arg(QString(context.function).
//			section('(', -2, -2).		// Function name only
//			section(' ', -1).
//			section(':', -1)).
//		arg(msg);
    QString log = QObject::tr("%1").arg(msg);
    auto logger = Log4Qt::Logger::rootLogger();

    // QtDebugMsg, QtWarningMsg, QtCriticalMsg, QtFatalMsg, QtInfoMsg, QtSystemMsg = QtCriticalMsg
    switch(type) {
    case QtDebugMsg:
        logger->debug(log);
        break;
    case QtWarningMsg:
        logger->warn(log);
        break;
    case QtFatalMsg:
        logger->fatal(log);
        break;
    case QtInfoMsg:
        logger->info(log);
        break;
    default:
        break;
    }
}
