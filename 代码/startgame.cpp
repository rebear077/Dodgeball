#include "startgame.h"
#include "ui_startgame.h"
#include "startgame.h"
#include "mainscene.h"
#include "record.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <iostream>
using namespace std;

Startgame::Startgame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Startgame)
{
    ui->setupUi(this);
}

void Startgame::on_pushButton_clicked()
{
    MainScene *m = new MainScene();
    this->close();
    m->show();
}

void Startgame::on_pushButton_2_clicked()
{
    Record *r = new Record();
    r->show();
}

Startgame::~Startgame()
{
    delete ui;
}
