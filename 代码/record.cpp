#include "record.h"
#include "ui_record.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QLabel>
#include <iostream>
using namespace std;

Record::Record(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Record)
{
    ui->setupUi(this);
    //addDatabase() 创建一个连接，调用这个函数时，我们可以传递我们要访问哪种类型的数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");     //驱动
    QStringList list = QSqlDatabase::drivers();
    qDebug() << list;
    db.setHostName("localhost");          // 数据库地址，一般都是本地，填localhost就可以(或者填写127.0.0.1)
    db.setDatabaseName("student_grades");         // 数据库名，根据你Mysql里面的数据库名称来填写，比如我的Mysql里面有个数据库叫school
    db.setUserName("root");               // 登录用户名，一般是本地用户，填root就可以
    db.setPassword("123456");				  // 登录密码，填写你自己Mysql登陆密码
    db.setPort(3306);                     // 端口，默认是3306

    // 打开数据库
    if (!db.open()) {	// 数据库打开失败
        qDebug() << "失败原因" << db.lastError().text();
    } else {
        qDebug() << "连接成功!!!!";
    }
    QSqlQuery query;
    QString sql;
    sql = "select * from timer_test1";
    query.exec(sql);
    vector<int> ans;
    while(query.next()){
        qDebug() << query.value(0).toInt();
        ans.push_back(query.value(0).toInt());
    }
    db.close();
    for (int i = 0; i < 6; ++i){
        ans.push_back(0);
    }
    sort(ans.begin(),ans.end());
    reverse(ans.begin(),ans.end());
    ui->label->setText(QString::number(ans[0]));
    ui->label_2->setText(QString::number(ans[1]));
    ui->label_3->setText(QString::number(ans[2]));
    ui->label_4->setText(QString::number(ans[3]));
    ui->label_5->setText(QString::number(ans[4]));
    ui->label_6->setText(QString::number(ans[5]));
//    if (ans.size() == 0){
//        ui->label->setText(QString::number(0));
//        ui->label_2->setText(QString::number(0));
//        ui->label_3->setText(QString::number(0));
//        ui->label_4->setText(QString::number(0));
//        ui->label_5->setText(QString::number(0));
//        ui->label_6->setText(QString::number(0));
//    }
//    else if (ans.size() == 1){
//        ui->label->setText(QString::number(ans[0]));
//        ui->label_2->setText(QString::number(0));
//        ui->label_3->setText(QString::number(0));
//        ui->label_4->setText(QString::number(0));
//        ui->label_5->setText(QString::number(0));
//        ui->label_6->setText(QString::number(0));
//    }
//    else if (ans.size() == 2){
//        ui->label->setText(QString::number(ans[0]));
//        ui->label_2->setText(QString::number(ans[1]));
//        ui->label_3->setText(QString::number(0));
//        ui->label_4->setText(QString::number(0));
//        ui->label_5->setText(QString::number(0));
//        ui->label_6->setText(QString::number(0));
//    }
//    else if (ans.size() == 3){
//        ui->label->setText(QString::number(ans[0]));
//        ui->label_2->setText(QString::number(ans[1]));
//        ui->label_3->setText(QString::number(ans[2]));
//        ui->label_4->setText(QString::number(0));
//        ui->label_5->setText(QString::number(0));
//        ui->label_6->setText(QString::number(0));
//    }
//    else if (ans.size() == 4){
//        ui->label->setText(QString::number(ans[0]));
//        ui->label_2->setText(QString::number(ans[1]));
//        ui->label_3->setText(QString::number(ans[2]));
//        ui->label_4->setText(QString::number(ans[3]));
//        ui->label_5->setText(QString::number(0));
//        ui->label_6->setText(QString::number(0));
//    }
//    else if (ans.size() == 5){
//        ui->label->setText(QString::number(ans[0]));
//        ui->label_2->setText(QString::number(ans[1]));
//        ui->label_3->setText(QString::number(ans[2]));
//        ui->label_4->setText(QString::number(ans[3]));
//        ui->label_5->setText(QString::number(ans[4]));
//        ui->label_6->setText(QString::number(0));
//    }
//    else{
//        ui->label->setText(QString::number(ans[0]));
//        ui->label_2->setText(QString::number(ans[1]));
//        ui->label_3->setText(QString::number(ans[2]));
//        ui->label_4->setText(QString::number(ans[3]));
//        ui->label_5->setText(QString::number(ans[4]));
//        ui->label_6->setText(QString::number(ans[5]));
//    }
}


Record::~Record()
{
    delete ui;
}
