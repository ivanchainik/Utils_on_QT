#include "interface.h"

Interface::Interface(QObject *parent): QObject (parent){
    _model = new StateListModel(this);
    qRegisterMetaType<State>();
    qRegisterMetaType<StateListModel*>();
}

StateListModel* Interface::getModel(){
    return _model;
}

void Interface::addToModel(State *item){
    if(item == nullptr)
        item = new State(this);
    _model->insertRow(0, QModelIndex(), item);
}

void Interface::deleteFromModel(int row){
    _model->removeRow(row, QModelIndex());
}

bool Interface::writeToJson(QString name_file){
    QVariantMap sourceData = _model->toMap();
    QUrl url(name_file);
    QFile json_file(url.toLocalFile());

    if(json_file.open(QIODevice::WriteOnly)){
        json_file.write(QJsonDocument(QJsonObject::fromVariantMap(sourceData)).toJson());
        json_file.close();

        return true;
    }
    return false;
}

void Interface::readToJson(QString name_file){

    QUrl url(name_file);
    QFile json_file(url.toLocalFile());
    QByteArray unloaded_data_json;
    if(json_file.open(QIODevice::ReadOnly | QIODevice::Text)){
        unloaded_data_json = json_file.readAll();

        QJsonDocument loadDoc(QJsonDocument::fromJson(unloaded_data_json));
        QJsonObject config = loadDoc.object();
        QVariantMap unloaded_data_map = config.toVariantMap();

        json_file.close();

        for(int i = 0; i < unloaded_data_map.size(); i++)
        {
          addToModel();
        }

        _model->fromMap(unloaded_data_map);       
    }
}

bool Interface::validate(const QString status){
    int i = 0;

    for(auto item : _model->allItems()){

        if(status == item->getStatus())
            ++i;
    }

    if(i > 1)
        return false;

    return true;
}

void Interface::setStatus(int index, QString _status){
    _model->allItems().at(index)->setStatus(_status);
}


bool Interface::blinkCheck(){
    for(auto item : _model->allItems()){
        if(item->getBlinking() == true)
            return true;
    }
    return false;
}

QList <State *> Interface::checkOfRepeat(){
    QList <State *> repeat_elements;

    for(auto &item : _model->allItems()){

        for(auto &items : _model->allItems()){

            if(item == items)
                continue;

            if(item->getStatus() == items->getStatus()){
                repeat_elements.append(item);
                break;
            }
        }
    }

    return repeat_elements;
}

