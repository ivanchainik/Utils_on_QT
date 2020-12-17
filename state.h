#ifndef STATE_H
#define STATE_H

#include <QObject>
#include <QString>
#include <QVariant>
#include <QMap>

class State : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString primaryColor READ getPrimaryColor WRITE setPrimaryColor)
    Q_PROPERTY(QString secondaryColor READ getSecondaryColor WRITE setSecondaryColor)
    Q_PROPERTY(bool blinking READ getBlinking WRITE setBlinking)
    Q_PROPERTY(QString status READ getStatus WRITE setStatus)
public:
    explicit State(QObject *parent = nullptr);
    ~State(){}
    State(const State &st);

    QString const getPrimaryColor();
    void setPrimaryColor(const QString &_primaryColor);

    QString const getSecondaryColor();
    void setSecondaryColor(const QString &_secondaryColor);

    bool getBlinking();
    void setBlinking(const bool &_blinking);

    QString getStatus();
    void setStatus(const QString &_status);

    QVariantMap toMap(); //Метод возвращающий поля класса в QVariantMap
    void fromMap(const QVariantMap &item); //Метод записывающий в поля класса из item

private:
    QString primaryColor;
    QString secondaryColor;
    bool blinking;
    QString status;
};

Q_DECLARE_METATYPE(State)
#endif // STATE_H
