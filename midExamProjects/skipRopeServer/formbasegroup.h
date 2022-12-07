#ifndef FORMBASEGROUP_H
#define FORMBASEGROUP_H

#include <QGroupBox>
#include <QWidget>

class QLabel;

enum ClientState{
    ClientOnline,
    ClientOffline,
    ClientHasStudent,
    ClientNoStudent,
    ClientStartTest,
    ClientStopTest,
    ClientInvalid
};


class FormBaseGroup : public QGroupBox
{
public:

    FormBaseGroup(QWidget *parent = nullptr);

    void initUi();

    void setItemId(int id);
    int itemId() const;
    void setItemState(ClientState state);

    ClientState state() const;

private:
    QLabel *m_lbItemNum;
    QLabel *m_lbItemIcon;
    QLabel *m_lbItemStateText;
    int m_itemId = -1;
    ClientState m_state = ClientInvalid;
};

#endif // FORMBASEGROUP_H
