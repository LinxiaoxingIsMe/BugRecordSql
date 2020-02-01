#include "diacreatenewdata.h"
#include "ui_diacreatenewdata.h"

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
