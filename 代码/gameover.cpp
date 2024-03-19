#include "gameover.h"
#include "ui_gameover.h"
#include "startgame.h"
#include "mainscene.h"
#include <QTimer>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

int num = 1;

Gameover::Gameover(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Gameover)
{
    ui->setupUi(this);
    //ui->label_3->setText(QString::number(timer_count / num));
    ui->label_3->setText(QString::number(timer_count));
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
    QString sql = QString("insert into timer_test1 values(%1)").arg(timer_count);
    db.transaction();
    bool flag = query.exec(sql);
    if (flag){
        db.commit();
    }
    else{
        db.rollback();
    }
    db.close();
}

void Gameover::on_pushButton_clicked()
{
//    timer_count = 0;
    ++num;
    Startgame *s = new Startgame();
    this->close();
    s->show();
}

Gameover::~Gameover()
{
    delete ui;
}
