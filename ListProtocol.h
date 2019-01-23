#ifndef LISTPROTOCOL_H
#define LISTPROTOCOL_H

#include <QObject>

class ListProtocol
{
private:
    QString depict;
    QString name;
    QString type;
public:
    ListProtocol();
    ListProtocol(QString,QString,QString);

public:
    void setDepict(QString depict);
    void setName(QString name);
    void setType(QString type);

    QString getDepict( );
    QString getName( );
    QString getType( );
};

#endif // LISTPROTOCOL_H
