#ifndef QSQLBUGMODEL_H
#define QSQLBUGMODEL_H

#include <QSqlTableModel>
class QSqlBugModel : public QSqlTableModel
{
    Q_OBJECT
public:
    QSqlBugModel(QObject * parent = nullptr, QSqlDatabase db = QSqlDatabase());

    bool setData( const QModelIndex &index, const QVariant &value, int role );
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
private:

};

#endif // QSQLBUGMODEL_H
