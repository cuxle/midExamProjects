#include "formbaseitem.h"
#include "ui_formbaseitem.h"

#include <QPainter>
#include <QPaintEvent>


FormBaseItem::FormBaseItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormBaseItem)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);
}

FormBaseItem::~FormBaseItem()
{
    delete ui;
}


void FormBaseItem::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // smooth borders
    painter.setBrush(QBrush(Qt::darkGray)); // visible color of background
    painter.setPen(Qt::transparent); // thin border color

    // Change border radius
    QRect rect = this->rect();
    rect.setWidth(rect.width()-1);
    rect.setHeight(rect.height()-1);
    painter.drawRoundedRect (rect, 15, 15);

    QWidget::paintEvent(event);
}
