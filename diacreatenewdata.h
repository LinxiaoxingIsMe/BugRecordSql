#ifndef DIACREATENEWDATA_H
#define DIACREATENEWDATA_H

#include <QDialog>
#include <QSqlRecord>
namespace Ui {
class DiaCreateNewData;
}

class DiaCreateNewData : public QDialog
{
    Q_OBJECT

public:
    explicit DiaCreateNewData(QWidget *parent = nullptr);
    ~DiaCreateNewData();

    void setUpdateRecord(QSqlRecord &recData);
    void setInsertRecord(QSqlRecord &recData);
    QSqlRecord getRecordData();

private:
    Ui::DiaCreateNewData *ui;

    QSqlRecord mRecord; //保存一条数据
};

#endif // DIACREATENEWDATA_H
