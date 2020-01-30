#include "bugrecordpage.h"
#include "ui_bugrecordpage.h"

BugRecordPage::BugRecordPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BugRecordPage)
{
    ui->setupUi(this);

    initForms();
    openTable();
}

BugRecordPage::~BugRecordPage()
{
    delete ui;
}

void BugRecordPage::initForms()
{
    ui->actSave->setEnabled(false);

    labelMessage = new QLabel;
    labelMessage->setMinimumWidth(150);
    ui->statusbar->addWidget(labelMessage);
}

void BugRecordPage::openTable()
{
    Db = QSqlDatabase::addDatabase("QSQLITE");
    Db.setDatabaseName("../data.db");
    if( !Db.open() )
    {
        QMessageBox::warning(this, "错误", "打开数据库失败", QMessageBox::Ok);
        return;
    }
    //打开数据库
    tabBugRecord = new QSqlTableModel(this, Db);
    tabBugRecord->setTable("bugRecordTable");
    tabBugRecord->setSort(tabBugRecord->fieldIndex("Id"), Qt::AscendingOrder);//按照id升序
    tabBugRecord->setEditStrategy(QSqlTableModel::OnManualSubmit);//手动保存
    if( !(tabBugRecord->select()) )
    {
        QMessageBox::critical(this, "错误", "打开数据表错误\n"+tabBugRecord->lastError().text(), QMessageBox::Ok);
        return;
    }

    labelMessage->setText("数据表打开成功");
    tabBugRecord->setHeaderData(tabBugRecord->fieldIndex("Id"), Qt::Horizontal, "ID");
    tabBugRecord->setHeaderData(tabBugRecord->fieldIndex("Describe"), Qt::Horizontal, "描述");
    tabBugRecord->setHeaderData(tabBugRecord->fieldIndex("Remarks"), Qt::Horizontal, "备注");
    tabBugRecord->setHeaderData(tabBugRecord->fieldIndex("Time"), Qt::Horizontal, "Time");
    tabBugRecord->setHeaderData(tabBugRecord->fieldIndex("Finish"), Qt::Horizontal, "是否完成");
    ui->tableBugRecord->setModel(tabBugRecord);

    theSelection = new QItemSelectionModel(tabBugRecord);
    connect(theSelection, &QItemSelectionModel::currentChanged, this, &BugRecordPage::tableCurrentChanged);
    //    connect(theSelection, &QItemSelectionModel::currentRowChanged, this, &BugRecordPage::tableCurrentRowChanged);

    ui->tableBugRecord->setSelectionModel(theSelection);
}

void BugRecordPage::tableCurrentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if(tabBugRecord->isDirty())
    {//有未保存的数据
        labelMessage->setText(QString("%1 行 %2 列 数据 修改").arg(previous.row()).arg(previous.column()));
        ui->actSave->setEnabled(tabBugRecord->isDirty());
    }

}

