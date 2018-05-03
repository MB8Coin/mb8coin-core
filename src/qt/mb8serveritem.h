#ifndef MB8TECHITEM_H
#define MB8TECHITEM_H

#include <QWidget>

namespace Ui {
class mb8serveritem;
}

class mb8serveritem : public QWidget
{
    Q_OBJECT

public:
    explicit mb8serveritem(QWidget *parent = 0);
    ~mb8serveritem();
    void setHost(QString hostStr);
    void setName(QString nameStr);

private:
    Ui::mb8serveritem *ui;
    QString host;
    QString name;
};

#endif // MB8TECHITEM_H
