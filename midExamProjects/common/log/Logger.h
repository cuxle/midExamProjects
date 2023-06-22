#pragma once

#include <QDebug>
#include <QFile>
#include <QHash>

class Logger {
private:
	/// @brief The different type of contexts.
	static QHash<QtMsgType, QString> contextNames;
public:
	/// @brief Initializes the logger.
	static void init();

    static void initStartTag();

    static void initStoptTag();

    static void installMessageOut();

	/// @brief The function which handles the logging of text.
	static void messageOutput(QtMsgType type, const QMessageLogContext& context,
		const QString& msg);
};
