#include "qsqlbugmodel.h"
#include <QDebug>
#include <QSqlRecord>
#include <QColor>
#include <QMap>
static QMap<int, Qt::CheckState> check_state_map;
static int checkColumn = 4;

QSqlBugModel::QSqlBugModel(QObject * parent, QSqlDatabase db )
{

}

bool QSqlBugModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
        return false;

    if (role == Qt::CheckStateRole && index.column() == checkColumn)
    {
        check_state_map[index.row()] = (value == Qt::Checked ? Qt::Checked : Qt::Unchecked);

        return true;
    }
    else
        return QSqlTableModel::setData(index, value,role);
}

QVariant QSqlBugModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.column() != checkColumn )
    {
        return QSqlTableModel::data(index, role);
    }

    Qt::CheckState findCheck = Qt::Unchecked;
    QString test = QSqlTableModel::data(index, role).toString();

    if( !test.isEmpty() )
    {
        if(test.toInt())
        {
            findCheck = Qt::Checked;
        }
        else
        {
            findCheck = Qt::Unchecked;
        }
        check_state_map.insert(index.row(), findCheck);
    }


    switch(role)
    {
    case Qt::TextColorRole:
        return QColor(Qt::red);
    case Qt::TextAlignmentRole:
        return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
    case Qt::CheckStateRole:
        if(index.column() == checkColumn)
        {
            if (check_state_map.contains(index.row()))
            {
                return check_state_map[index.row()] == Qt::Checked ? Qt::Checked : Qt::Unchecked;
            }
            return findCheck;
        }
    }
    return QVariant();
}

Qt::ItemFlags QSqlBugModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;
    if (index.column() == checkColumn)
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
    else
        return QSqlTableModel::flags(index);
    return  Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
