#ifndef LICENSEMODEL_H
#define LICENSEMODEL_H

#include <QObject>
#include <QDateTime>

enum RoleType {
    Trial = 0,
    Expiration = 1,
    Free = 2
};

class LicenseModel : public QObject
{
    Q_OBJECT
public:
    explicit LicenseModel(QObject *parent = nullptr);

    void setCustomMachineCode(const QString &newCustomMachineCode);

    const QString &customMachineCode() const;

    void setExpireTime(const QDateTime &newExpireTime);

    const QDateTime &expireTime() const;

    const QDateTime &lastUseTime() const;
    void setLastUseTime(const QDateTime &newLastUseTime);

    RoleType customRole() const;
    void setCustomRole(RoleType newCustomRole);

signals:
private:
    QString m_customMachineCode;
    QDateTime m_lastUseTime;
    QDateTime m_expireTime;
    RoleType m_customRole;
};

#endif // LICENSEMODEL_H
