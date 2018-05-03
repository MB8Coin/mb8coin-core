#ifndef MB8TECHINIT_H
#define MB8TECHINIT_H

#include <QDialog>

namespace Ui {
class NavTechInit;
}

class NavTechInit : public QDialog
{
    Q_OBJECT

public:
    explicit NavTechInit(QWidget *parent = 0);
    ~NavTechInit();
    QString GetServers();
    void ShowMB8ServerIntro(bool exitAfter = true);

private:
    Ui::NavTechInit *ui;
};

#endif // MB8TECHINIT_H
