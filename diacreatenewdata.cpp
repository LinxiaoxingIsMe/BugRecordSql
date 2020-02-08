#include "diacreatenewdata.h"
#include "ui_diacreatenewdata.h"
#include <QDebug>
DiaCreateNewData::DiaCreateNewData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiaCreateNewData)
{
    ui->setupUi(this);
}

DiaCreateNewData::~DiaCreateNewData()
{
    delete ui;
}

void DiaCreateNewData::setUpdateRecord(QSqlRecord &recData)
{
    mRecord = recData;

    setWindowTitle("编辑");

    ui->textDescribe->setText(recData.value("Describe").toString());
    ui->textRemarks->setText(recData.value("Remarks").toString());

    qDebug()<<recData.value("Finish").toInt();
    if(recData.value("Finish").toInt())
    {
        ui->checkFinish->setChecked(true);
    }
    switch (recData.value("Priority").toInt())
    {
    case 0:
        ui->radioLow->setChecked(true);
        break;
    case 1:
        ui->radioMiddle->setChecked(true);
        break;
    case 2:
        ui->radioHight->setChecked(true);
        break;
    }
}

QSqlRecord DiaCreateNewData::getRecordData()
{
    mRecord.setValue("Describe", ui->textDescribe->toPlainText());
    mRecord.setValue("Remarks", ui->textRemarks->toPlainText());
    int theFinish = 0;
    if(ui->checkFinish->isChecked())
    {
        theFinish = 1;
    }
    mRecord.setValue("Finish",theFinish);

    int thePriority = -1;
    if(ui->radioLow->isChecked())
    {
        thePriority = 0;
    }
    else
        if(ui->radioMiddle->isChecked())
        {
            thePriority = 1;
        }
        else
            if(ui->radioHight->isChecked())
            {
                thePriority = 2;
            }
    mRecord.setValue("Priority", thePriority);

    return mRecord;
}
