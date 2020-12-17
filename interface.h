#ifndef INTERFACE_H
#define INTERFACE_H

#include <statelistmodel.h>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>


class Interface : public QObject
{
    Q_OBJECT

public:
    explicit Interface(QObject *parent = nullptr);

    Q_INVOKABLE StateListModel* getModel();

    //Добавление элемента в модель
    Q_INVOKABLE void addToModel(State *item = nullptr);

    //Удвление элемента из модели
    Q_INVOKABLE void deleteFromModel(int row = 0);

    //Запись в JSON файл
    Q_INVOKABLE bool writeToJson(QString name_file);

    //Чтение из JSON файла
    Q_INVOKABLE void readToJson(QString name_file);

    //Проверка на повтор состояния
    Q_INVOKABLE bool validate(const QString status);

    Q_INVOKABLE void setStatus(int index, QString _status);

    Q_INVOKABLE bool blinkCheck();

    Q_INVOKABLE QList <State *> checkOfRepeat();



private:
    StateListModel *_model;
};

#endif // INTERFACE_H
