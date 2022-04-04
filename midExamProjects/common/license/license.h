#ifndef LICENSE_H
#define LICENSE_H

#include <QObject>

class License {
public:
    static bool verifyLicenseFromFile(const QString &fileName);
    static bool verifyLicenseFromCode(const QString &code);
    static QString getId(const QString &idType);
    static QString getMachineCode();
    static QByteArray encodeByString(QByteArray code, const QByteArray &by);
};


#endif // APPCONFIG_H
