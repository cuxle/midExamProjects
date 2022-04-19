#ifndef FORMBASEITEM_H
#define FORMBASEITEM_H

#include <QWidget>

namespace Ui {
class FormBaseItem;
}

class FormBaseItem : public QWidget
{
    Q_OBJECT

public:
    explicit FormBaseItem(QWidget *parent = nullptr);
    ~FormBaseItem();

private:
    Ui::FormBaseItem *ui;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // FORMBASEITEM_H
