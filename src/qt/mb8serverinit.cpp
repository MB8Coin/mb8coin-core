#include "mb8serverinit.h"
#include "ui_mb8serverinit.h"
#include "net.h"
#include "util.h"
#include "skinize.h"

#include <string>
#include <iostream>

#include <QStringList>
#include <QUrl>

MB8ServerInit::MB8ServerInit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MB8ServerInit)
{
    ui->setupUi(this);
}

MB8ServerInit::~MB8ServerInit()
{
    delete ui;
}

void MB8ServerInit::ShowMB8ServerIntro(bool exitAfter)
{
    MB8ServerInit mb8serverinit;
    mb8serverinit.setWindowIcon(QIcon(":icons/mb8coin"));
    mb8serverinit.setStyleSheet(Skinize());

    if(!mb8serverinit.exec())
    {
        if(exitAfter)
            exit(0);
        else
            return;
    }

    QString ServersToAdd = mb8serverinit.GetServers();
    QStringList ss = ServersToAdd.split('\n');

    for (int i = 0; i < ss.size(); ++i){
        QString Server = ss.at(i);
        QString strippedServer = Server.remove(' ');
        if(strippedServer != "")
        {
            WriteConfigFile("addnode",strippedServer.toStdString());
        }
    }
}

QString MB8ServerInit::GetServers()
{
    return ui->plainTextEdit->toPlainText();
}
