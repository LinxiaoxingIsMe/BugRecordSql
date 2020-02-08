#include "bugrecordpage.h"
#include "ui_bugrecordpage.h"
#include "diacreatenewdata.h"
#include <QSqlRecord>
BugRecordPage::BugRecordPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BugRecordPage)
{
    ui->setupUi(this);

    labelMessage = new QLabel;
    labelMessage->setMinimumWidth(150);
    ui->statusbar->addWidget(labelMessage);

    openTable();
    initForms();
}

BugRecordPage::~BugRecordPage()
{
    delete ui;
}

void BugRecordPage::initForms()
{
    ui->actSave->setEnabled(false);
    ui->actDel->setEnabled(false);
    ui->actModify->setEnabled(false);
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
    tabBugRecord = new QSqlBugModel(this, Db);
    tabBugRecord->setTable("bugRecordTable");
    tabBugRecord->setEditStrategy(QSqlTableModel::OnManualSubmit);//手动保存
    if( !(tabBugRecord->select()) )
    {
        QMessageBox::critical(this, "错误", "打开数据表错误\n"+tabBugRecord->lastError().text(), QMessageBox::Ok);
        return;
    }

    tabBugRecord->setHeaderData(tabBugRecord->fieldIndex("Id"), Qt::Horizontal, "ID");
    tabBugRecord->setHeaderData(tabBugRecord->fieldIndex("Describe"), Qt::Horizontal, "描述");
    tabBugRecord->setHeaderData(tabBugRecord->fieldIndex("Remarks"), Qt::Horizontal, "备注");
    tabBugRecord->setHeaderData(tabBugRecord->fieldIndex("Time"), Qt::Horizontal, "时间");
    tabBugRecord->setHeaderData(tabBugRecord->fieldIndex("Finish"), Qt::Horizontal, "是否完成");
    tabBugRecord->setHeaderData(tabBugRecord->fieldIndex("Priority"), Qt::Horizontal, "优先级");
    ui->tableBugRecord->setModel(tabBugRecord);

    theSelection = new QItemSelectionModel(tabBugRecord);
    connect(theSelection, &QItemSelectionModel::currentChanged, this, &BugRecordPage::tableCurrentChanged);
    connect(theSelection, &QItemSelectionModel::currentRowChanged, this, &BugRecordPage::tableCurrentRowChanged);

    ui->tableBugRecord->setSelectionModel(theSelection);
    ui->tableBugRecord->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableBugRecord->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableBugRecord->setColumnHidden(tabBugRecord->fieldIndex("Id"), true);

    connect(ui->actNew, &QAction::triggered, this, &BugRecordPage::createNewData);
    connect(ui->actModify, &QAction::triggered, this, &BugRecordPage::modifyData);
}

void BugRecordPage::tableCurrentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous)
    if(current.isValid())
    {
        labelMessage->setText(QString("%1 行 %2 列").arg(current.row()).arg(current.column()));
    }
    ui->actSave->setEnabled(tabBugRecord->isDirty());

}

void BugRecordPage::tableCurrentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous)

    ui->actDel->setEnabled(current.isValid());
    ui->actModify->setEnabled(current.isValid());
}

void BugRecordPage::updateData(int curRecNo)
{
    QSqlRecord curRec = tabBugRecord->record(curRecNo);
    DiaCreateNewData *dataDialog = new DiaCreateNewData(this);
    Qt::WindowFlags flags = dataDialog->windowFlags();
    dataDialog->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);

    dataDialog->setUpdateRecord(curRec);
    int ret = dataDialog->exec();
    if(ret == QDialog::Accepted)
    {
        QSqlRecord recData = dataDialog->getRecordData();
        QSqlQuery query;
//        query.prepare("update bugRecordTable set Describe=:Describe, Remarks=:Remarks,")
    }
    delete dataDialog;
}

void BugRecordPage::createNewData()
{

}

void BugRecordPage::modifyData()
{
    int curRecNo = theSelection->currentIndex().row();
    updateData(curRecNo);

}

