#ifndef MB8TECHINIT_H
#define MB8TECHINIT_H

#include <QDialog>

namespace Ui {
class MB8ServerInit;
}

class MB8ServerInit : public QDialog
{
    Q_OBJECT

public:
    explicit MB8ServerInit(QWidget *parent = 0);
    ~MB8ServerInit();
    QString GetServers();
    void ShowMB8ServerIntro(bool exitAfter = true);

private:
    Ui::MB8ServerInit *ui;
};

#endif // MB8TECHINIT_H
