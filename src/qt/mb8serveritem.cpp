#include "mb8serveritem.h"
#include "ui_mb8serveritem.h"

mb8serveritem::mb8serveritem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mb8serveritem),
    host(""),
    name("")
{
    ui->setupUi(this);
}

void mb8serveritem::setHost(QString hostStr)
{
    host = hostStr;
    ui->serverHostLabel->setText(hostStr);
}

void mb8serveritem::setName(QString nameStr)
{
    name = nameStr;
    ui->serverNameLabel->setText(nameStr);
}

mb8serveritem::~mb8serveritem()
{
    delete ui;
}
