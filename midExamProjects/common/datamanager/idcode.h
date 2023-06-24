#ifndef IDCODE_H
#define IDCODE_H

#include <QString>
#include <QObject>

class IDCode
{
public:
    IDCode();

    QString id;
    QString code;

    IDCode(const IDCode &other);
    IDCode &operator=(const IDCode &other);
    bool operator==(const IDCode &other) const;

};

inline size_t qHash(const IDCode &key, uint seed){
    return qHash(key.id + key.code, seed);
}

#endif // IDCODE_H
