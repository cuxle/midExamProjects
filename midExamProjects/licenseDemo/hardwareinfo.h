#ifndef HARDWAREINFO_H
#define HARDWAREINFO_H

#include <QObject>

class HardWareInfo : public QObject
{
    Q_OBJECT
public:
    explicit HardWareInfo(QObject *parent = nullptr);
    QString getMyMachineCode();

signals:
private:
    QString m_myMachineCode;

};

#endif // HARDWAREINFO_H
