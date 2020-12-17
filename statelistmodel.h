#ifndef STATELISTMODEL_H
#define STATELISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QQmlEngine>
#include <state.h>

class StateListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles{
        PrimaryColor = Qt::UserRole + 1,
        SecondaryColor,
        Blinking,
        Status
    };

    explicit StateListModel(QObject *parent = nullptr);
    ~StateListModel(){}
    StateListModel(const StateListModel &sts);

    QList<State*> allItems();//Возвращает список элементов

    bool insertRow(int row, const QModelIndex &parent = QModelIndex(), State *item = new State());//Добавление элемента
    virtual bool removeRow(int row, const QModelIndex &parent = QModelIndex());//Удаление элемента

    virtual QHash<int, QByteArray> roleNames() const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    virtual int rowCount(const QModelIndex &parent) const;

    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    QVariantMap toMap(); //Записывает поля элементов списка в QVariantMap
    void fromMap(const QVariantMap &ListFieldState); //Записывает в поля элементов списка данные из ListFieldState

    Q_INVOKABLE int getCount();
    Q_INVOKABLE void deleteAll();

private:
    QList <State*> items;
    int count = items.size();
};

Q_DECLARE_METATYPE(StateListModel)

#endif // STATELISTMODEL_H
