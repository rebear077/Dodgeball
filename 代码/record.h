#ifndef RECORD_H
#define RECORD_H

#include <QWidget>

namespace Ui {
class Record;
}

class Record : public QWidget
{
    Q_OBJECT

public:
    explicit Record(QWidget *parent = nullptr);
    ~Record();
    bool comp(int &a, int &b);

private:
    Ui::Record *ui;
};

#endif // RECORD_H
