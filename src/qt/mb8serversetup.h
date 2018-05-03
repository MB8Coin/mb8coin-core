#ifndef MB8TECHSETUP_H
#define MB8TECHSETUP_H

#include "wallet/mb8server.h"

#include <QDialog>
#include <QVBoxLayout>

namespace Ui {
class mb8serversetup;
}

class mb8serversetup : public QDialog
{
    Q_OBJECT

public:
    explicit mb8serversetup(QWidget *parent = 0);
    ~mb8serversetup();

private:
    Ui::mb8serversetup *ui;

public Q_SLOTS:
    void reloadMB8Servers();
    void addMB8ServerServer();
    void removeMB8ServerServer();
    void getinfoMB8ServerServer();
    void showButtons(bool show=true);
    void showMB8ServerIntro();

};

#endif // MB8TECHSETUP_H
