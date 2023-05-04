#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include <QPixmap>

class VideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = nullptr);
    const QPixmap* pixmap() const;
    void setPixmap (const QPixmap &pixmap);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QPixmap m_pix;
};

#endif // VIDEOWIDGET_H
