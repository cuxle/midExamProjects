#include "videowidget.h"
#include <QPainter>
#include <QPaintEvent>

VideoWidget::VideoWidget(QWidget *parent)
    : QWidget(parent)
{

}

void VideoWidget::paintEvent(QPaintEvent *event)
{
    if (m_pix.isNull())
        return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QSize pixSize = m_pix.size();
    pixSize.scale(event->rect().size(), Qt::IgnoreAspectRatio);

    QPixmap scaledPix = m_pix.scaled(pixSize,
                                   Qt::IgnoreAspectRatio,
                                   Qt::SmoothTransformation
                                   );

    painter.drawPixmap(QPoint(), scaledPix);

    QWidget::paintEvent(event);
}

const QPixmap* VideoWidget::pixmap() const {
    return &m_pix;
}

void VideoWidget::setPixmap (const QPixmap &pixmap){
    m_pix = pixmap;
    update();
}
