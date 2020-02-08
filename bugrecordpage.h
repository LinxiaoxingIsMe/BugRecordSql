#ifndef BUGRECORDPAGE_H
#define BUGRECORDPAGE_H
#if _MSC_VER >= 1600

#pragma execution_character_set("utf-8")

#endif


#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariantList>
#include <QSqlTableModel>
#include <QItemSelectionModel>
#include <QLabel>
#include "qsqlbugmodel.h"
QT_BEGIN_NAMESPACE
namespace Ui { class BugRecordPage; }
QT_END_NAMESPACE

class BugRecordPage : public QMainWindow
{
    Q_OBJECT

public:
    BugRecordPage(QWidget *parent = nullptr);
    ~BugRecordPage();

private:
    Ui::BugRecordPage *ui;

    QLabel *labelMessage;

//    QSqlTableModel *tabBugRecord;
    QSqlBugModel *tabBugRecord;
    QSqlDatabase Db;
    QItemSelectionModel *theSelection;

    void initForms();
    void openTable();

    void tableCurrentChanged(const QModelIndex &current, const QModelIndex &previous);
    void tableCurrentRowChanged(const QModelIndex &current, const QModelIndex &previous);

    void updateData(int curRecNo);
    void createNewData();
    void modifyData();
};
#endif // BUGRECORDPAGE_H
