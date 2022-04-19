#include "licensemodel.h"

LicenseModel::LicenseModel(QObject *parent)
    : QObject(parent)
{

}

void LicenseModel::setCustomMachineCode(const QString &newCustomMachineCode)
{
    m_customMachineCode = newCustomMachineCode;
}

const QString &LicenseModel::customMachineCode() const
{
    return m_customMachineCode;
}

void LicenseModel::setExpireTime(const QDateTime &newExpireTime)
{
    m_expireTime = newExpireTime;
}

const QDateTime &LicenseModel::expireTime() const
{
    return m_expireTime;
}

const QDateTime &LicenseModel::lastUseTime() const
{
    return m_lastUseTime;
}

void LicenseModel::setLastUseTime(const QDateTime &newLastUseTime)
{
    m_lastUseTime = newLastUseTime;
}

RoleType LicenseModel::customRole() const
{
    return m_customRole;
}

void LicenseModel::setCustomRole(RoleType newCustomRole)
{
    m_customRole = newCustomRole;
}
