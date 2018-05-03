#include "mb8serverinit.h"
#include "ui_mb8serverinit.h"
#include "net.h"
#include "util.h"
#include "skinize.h"

#include <string>
#include <iostream>

#include <QStringList>
#include <QUrl>

NavTechInit::NavTechInit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NavTechInit)
{
    ui->setupUi(this);
}

NavTechInit::~NavTechInit()
{
    delete ui;
}

void NavTechInit::ShowMB8ServerIntro(bool exitAfter)
{
    NavTechInit mb8serverinit;
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
            WriteConfigFile("addanonserver",strippedServer.toStdString());
        }
    }
}

QString NavTechInit::GetServers()
{
    return ui->plainTextEdit->toPlainText();
}
