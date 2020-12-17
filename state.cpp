#include "state.h"

State::State(QObject *parent) : QObject(parent) {
    primaryColor = "White";
    secondaryColor = "White";
    blinking = false;
    status = "";
}

State::State(const State &st) : QObject(st.parent()){

}

QString const State::getPrimaryColor(){
    return primaryColor;
}

QString const State::getSecondaryColor(){
    return secondaryColor;
}

bool State::getBlinking(){
    return blinking;
}

void State::setPrimaryColor(const QString &_primaryColor){
    primaryColor = _primaryColor;
}

void State::setSecondaryColor(const QString &_secondaryColor){
    secondaryColor = _secondaryColor;
}

void State::setBlinking(const bool &_blinking){
    blinking = _blinking;
}

QString State::getStatus(){
    return status;
}

void State::setStatus(const QString &_status){
    status = _status;
}

QVariantMap State::toMap(){
    QVariantMap data;
    data.insert("primaryColor", primaryColor);
    data.insert("secondaryColor", secondaryColor);
    data.insert("blinking", blinking);
    data.insert("status", status);
    return data;
}

void State::fromMap(const QVariantMap &item){
    primaryColor = item.value("primaryColor").toString();
    secondaryColor = item.value("secondaryColor").toString();
    blinking = item.value("blinking").toBool();
    status = item.value("status").toString();
}
