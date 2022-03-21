#ifndef SINGLETON_H
#define SINGLETON_H

//TODO: if appsingle has no problem, this file should deleted
#include <QSharedPointer>
#include <QMutex>
#include <QMutexLocker>

template<typename T>
class Singleton
{
private:
    static QSharedPointer<T> m_instance;
    static QMutex m_mutex;

public:
    static T& GetInstance()
    {
        if (m_instance.isNull()) {
            QMutexLocker mutexLocker(&m_mutex);
            if (m_instance.isNull()) {
                m_instance = QSharedPointer<T>(new T);
            }
        }

        return *m_instance;
    }

    Singleton(T&&) = delete;
    Singleton(const T&) = delete;
    void operator= (const T&) = delete;

protected:
    Singleton() = default;
    virtual ~Singleton() = default;
};

template<typename T>
QSharedPointer<T> Singleton<T>::m_instance;

template<typename T>
QMutex Singleton<T>::m_mutex;

#endif // SINGLETON_H
