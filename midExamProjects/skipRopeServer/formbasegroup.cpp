#include "formbasegroup.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

FormBaseGroup::FormBaseGroup(QWidget *parent)
    : QGroupBox(parent)
{
    initUi();
}

void FormBaseGroup::initUi()
{
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_8;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_14;

    QSpacerItem *horizontalSpacer;

    QSpacerItem *verticalSpacer_7;
    QSpacerItem *verticalSpacer_18;
    QSpacerItem *verticalSpacer_19;

    verticalSpacer_18 = new QSpacerItem(20, 70, QSizePolicy::Minimum, QSizePolicy::Expanding);
    verticalSpacer_19 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(0);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    verticalLayout->addItem(verticalSpacer_18);

    m_lbItemNum = new QLabel(this);
    m_lbItemNum->setObjectName(QString::fromUtf8("label_4"));
    m_lbItemNum->setStyleSheet(QString::fromUtf8("color: rgb(135, 130, 164);background-color: rgb(42, 38, 66);border-radius:10px"));
    m_lbItemNum->setText("  1");

    verticalLayout->addWidget(m_lbItemNum);

    verticalLayout_5 = new QVBoxLayout();
    verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
    verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout_5->addItem(verticalSpacer_8);

    horizontalLayout_12 = new QHBoxLayout();
    horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
    horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_12->addItem(horizontalSpacer_14);

    m_lbItemIcon = new QLabel(this);
    m_lbItemIcon->setObjectName(QString::fromUtf8("label_5"));
    m_lbItemIcon->setMinimumSize(QSize(42, 66));
    m_lbItemIcon->setStyleSheet(QString::fromUtf8("background-color: rgb(42, 38, 66);border-image: url(:/resource/skipRopeOnline.png);"));

    horizontalLayout_12->addWidget(m_lbItemIcon);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_12->addItem(horizontalSpacer);


    verticalLayout_5->addLayout(horizontalLayout_12);

    m_lbItemStateText = new QLabel(this);
    m_lbItemStateText->setObjectName(QString::fromUtf8("label_53"));
    m_lbItemStateText->setStyleSheet(QString::fromUtf8("color: rgb(135, 130, 164);background-color: rgb(42, 38, 66);"));
    m_lbItemStateText->setAlignment(Qt::AlignCenter);
    m_lbItemStateText->setText("在线");

    verticalLayout_5->addItem(verticalSpacer_19);
    verticalLayout_5->addWidget(m_lbItemStateText);

    verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout_5->addItem(verticalSpacer_7);


    verticalLayout->addLayout(verticalLayout_5);
    this->setLayout(verticalLayout);
}

void FormBaseGroup::setItemId(int id)
{
    m_itemId = id;
    QString itemNum = "  " + QString::number(id);
    this->m_lbItemNum->setText(itemNum);
}

int FormBaseGroup::itemId() const
{
    return m_itemId;
}

void FormBaseGroup::setItemState(ClientState newState)
{
    m_state = newState;
    switch (m_state)
    {
    case ClientOnline:
        m_lbItemIcon->setStyleSheet(QString::fromUtf8("background-color: rgb(42, 38, 66);border-image: url(:/resource/skipRopeOnline.png);"));
        m_lbItemStateText->setText("在线");
        break;
    case ClientOffline:
        m_lbItemIcon->setStyleSheet(QString::fromUtf8("background-color: rgb(42, 38, 66);border-image: url(:/resource/skipRopeOffline.png);"));
        m_lbItemStateText->setText("离线");
        break;
    case ClientHasStudent:
        break;
    case ClientNoStudent:
        break;
    case ClientInvalid:
        break;
    default:
        break;
    }
}

ClientState FormBaseGroup::state() const
{
    return m_state;
}
