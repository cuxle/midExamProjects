#include "license.h"

#include <QDebug>
#include <QProcess>
#include <QCryptographicHash>
#include <QFile>

bool License::verifyLicenseFromFile(const QString &fileName)
{
    if (fileName.isEmpty()) {
        return false;
    }
    QFile m_file;
    m_file.setFileName(fileName);
    if (!m_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << __func__ << __LINE__ << "open license file:" << fileName << "failed";
        return false;
    }
    QTextStream stream(&m_file);
    QString code;
    while(!stream.atEnd()) {
        code = stream.readLine();
    }
    qDebug() << __func__ << __LINE__ << code;
    return verifyLicenseFromCode(code);
}

bool License::verifyLicenseFromCode(const QString &code)
{
    QString machineCode = getMachineCode();
    QString str = "redDog";
    QByteArray ret = encodeByString(machineCode.toLatin1(), str.toLatin1());
    QString retStr;
    retStr.append(ret.toHex());

    QString str1 = "yellowDog";
    QByteArray ret1 = encodeByString(retStr.toLatin1(), str1.toLatin1());

    QString md5;
    QByteArray localCode;
    localCode = QCryptographicHash::hash(ret1, QCryptographicHash::Md5);
    md5.append(localCode.toHex());
    return md5 == code;
}

QString License::getId(const QString &idType)
{
    /*
     * idType can be
     * 1. cpu
     * 2. bios
     * 3. baseboard
    */
    QString param2 = "serialnumber";
    if (idType == "cpu") {
        param2 = "processorid";
    }
    QString cmd = QString("wmic %1 get %2").arg(idType).arg(param2);
    QProcess p(0);
    p.start(cmd);
    p.waitForFinished();
    QString ret = QString::fromLocal8Bit(p.readAllStandardOutput());
    ret = ret.remove(param2, Qt::CaseInsensitive).trimmed();
    return ret;
}

QString License::getMachineCode()
{
    QString cpuId = getId("cpu");
    QString biosId = getId("bios");
    QString baseBoard = getId("baseboard");
    QString machineId = cpuId + biosId + baseBoard;
    return machineId;

    qDebug() << "machine id" << machineId;
    QString str = "redDog";
    QByteArray ret = encodeByString(machineId.toLatin1(), str.toLatin1());
    QString retStr;
    retStr.append(ret.toHex());
    return retStr;
}

QByteArray License::encodeByString(QByteArray code, const QByteArray &by)
{
    qDebug() << __LINE__ << code.toHex(' ');
    qDebug() << __LINE__ << by.toHex(' ');
    QByteArray ret;
    for (auto item : by) {
        for (auto &mc : code) {
            mc = mc ^ item;
           // qDebug() << mc;
            ret.append(mc);
            //qDebug() << __LINE__ << ret.size();
        }
    }
    return ret;
}
