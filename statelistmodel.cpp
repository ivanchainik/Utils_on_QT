#include "statelistmodel.h"

StateListModel::StateListModel(QObject *parent)
    : QAbstractListModel(parent){
}

int StateListModel::getCount(){
    return count;
}

StateListModel::StateListModel(const StateListModel &sts) : QAbstractListModel (sts.parent()){

}

QList<State*> StateListModel::allItems(){
    return items;
}

QHash<int, QByteArray> StateListModel::roleNames() const{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[PrimaryColor] = "primaryColor";
    roles[SecondaryColor] = "secondaryColor";
    roles[Blinking] = "blinking";
    roles[Status] = "status";
    return roles;
}

QVariant StateListModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid())
        return QVariant();

    switch(role){
    case PrimaryColor:
        return items.at(index.row())->getPrimaryColor();
    case SecondaryColor:
        return items.at(index.row())->getSecondaryColor();
    case Blinking:
        return items.at(index.row())->getBlinking();
    case Status:
        return items.at(index.row())->getStatus();
    default:
        return QVariant();
    }
}

bool StateListModel::insertRow(int row, const QModelIndex &parent, State *item){
    try {
        beginInsertRows(parent, row, row);
        items.append(item);
        endInsertRows();
        count = items.size();
        return true;
    } catch (std::exception ex) {
        return false;
    }

}

bool StateListModel::removeRow(int row, const QModelIndex &parent){
    try {
        beginRemoveRows(parent, row, row);
        items.removeAt(row);
        endRemoveRows();
        count = items.size();
        return true;
    } catch (std::exception ex) {
        return false;
    }
}

QVariantMap StateListModel::toMap(){
    QVariantMap FieldState;
    int i = 0;
    for(const auto& item: items){
        FieldState.insert(QString::number(i),item->toMap());
        ++i;
    }
    return FieldState;
}

void StateListModel::fromMap(const QVariantMap &ListFieldState){
    int i = 0;
    for(auto &item: items){
        item->fromMap(ListFieldState.value(QString::number(i)).toMap());
        ++i;
    }
}

int StateListModel::rowCount(const QModelIndex &parent) const{
    if(parent.isValid())
        return 0;
    return items.size();
}

bool StateListModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if (!index.isValid())
        return false;
    try {
        switch (role) {
        case PrimaryColor:
            items.at(index.row())->setPrimaryColor(value.toString());
            return true;
        case SecondaryColor:
            items.at(index.row())->setSecondaryColor(value.toString());
            return true;
        case Blinking:
            items.at(index.row())->setBlinking(value.toBool());
            return true;
        case Status:
            items.at(index.row())->setStatus(value.toString());
            return true;
        }
    } catch (std::exception ex) {
        return false;
    }
}

Qt::ItemFlags StateListModel::flags(const QModelIndex &index) const{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractListModel::flags(index) | Qt::ItemIsEnabled;
}

void StateListModel::deleteAll(){
    beginRemoveRows(QModelIndex(), 0, items.size());
    items.clear();
    endRemoveRows();
}
