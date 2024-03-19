#ifndef STARTGAME_H
#define STARTGAME_H

#include <QWidget>

namespace Ui {
class Startgame;
}

class Startgame : public QWidget
{
    Q_OBJECT

public:
    explicit Startgame(QWidget *parent = nullptr);
    ~Startgame();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Startgame *ui;
};

#endif // STARTGAME_H
