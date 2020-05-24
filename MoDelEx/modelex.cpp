#include "modelex.h"

ModelEx::ModelEx(QObject *parent)
        : QAbstractTableModel(parent)
{
    armyMap[1] = "空军";
    armyMap[2] = "海军";
    armyMap[3] = "陆军";
    armyMap[4] = "海军陆战队";

    weaponTypeMap[1] = "轰炸机";
    weaponTypeMap[2] = "战斗机";
    weaponTypeMap[3] = "航空母舰";
    weaponTypeMap[4] = "驱逐舰";
    weaponTypeMap[5] = "直升机";
    weaponTypeMap[6] = "坦克";
    weaponTypeMap[7] = "两栖攻击舰";
    weaponTypeMap[8] = "两栖战车";

    populateModel();
}

void ModelEx::populateModel()
{
    header << "军种" << "种类" << "武器";
    army   << 1 << 2 << 3 << 4 << 2 << 4 << 3 << 1;
    weaponType << 1 << 3 << 5 << 7 << 4 << 8 << 6 << 2;
    weapon << "B-2" << "尼米呲级" << "阿帕奇" << "黄蜂级"
           << "阿利伯克级" << "AAAV" << "M1A1" << "F-22";
}

int ModelEx::columnCount(const QModelIndex &parent) const
{
    return 3;
}

int ModelEx::rowCount(const QModelIndex &parent) const
{
    return army.size();
}

QVariant ModelEx::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole)
    {
        switch (index.column())
        {
        case 0:
            return armyMap[army[index.row()]];
            break;
        case 1:
            return weaponTypeMap[weaponType[index.row()]];
            break;
        case 2:
            return weapon[index.row()];
        default:
            return QVariant();
        }
    }
    return QVariant();
}

QVariant ModelEx::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
        return header[section];
    if(orientation == Qt::Vertical)
        return QVariant();

    return QAbstractItemModel::headerData(section,orientation,role);
}


