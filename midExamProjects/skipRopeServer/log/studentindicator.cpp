#include "studentindicator.h"

ClientIndicator::ClientIndicator(QObject *parent)
    : QObject(parent)
{

}

void ClientIndicator::setLabel(QLabel *newLabel)
{
    m_label = newLabel;
}

void ClientIndicator::setId(int newId)
{
    m_id = newId;
}

void ClientIndicator::setState(ClinetState newState)
{
    m_state = newState;
}
