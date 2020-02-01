#ifndef DIACREATENEWDATA_H
#define DIACREATENEWDATA_H

#include <QDialog>

namespace Ui {
class DiaCreateNewData;
}

class DiaCreateNewData : public QDialog
{
    Q_OBJECT

public:
    explicit DiaCreateNewData(QWidget *parent = nullptr);
    ~DiaCreateNewData();

private:
    Ui::DiaCreateNewData *ui;
};

#endif // DIACREATENEWDATA_H
