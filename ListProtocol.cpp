#include "ListProtocol.h"

ListProtocol::ListProtocol()
{

}
ListProtocol::ListProtocol(QString depict,QString name,QString type)
{
    this->depict = depict;
    this->name = name;
    this->type = type;
}
void ListProtocol::setDepict(QString depict){
    this->depict = depict;
}
void ListProtocol::setName(QString name){
    this->name = name;
}
void ListProtocol::setType(QString type){
    this->type = type;

}

QString ListProtocol::getDepict( ){
    return  this->depict;
}
QString ListProtocol::getName( ){
    return  this->name;
}
QString ListProtocol::getType( ){
    return  this->type;
}
