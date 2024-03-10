#include "functionsforserver.h"

QByteArray parsing(const QString &data_from_client)
{
    QStringList data_from_client_list = data_from_client.split(QLatin1Char('&'));
    QString nameOfFunc = data_from_client_list.front();
    data_from_client_list.pop_front();
    if (nameOfFunc == "auth")
        return "you are authenticated\n";
    else if (nameOfFunc == "reg")
        return "you are registered\n";
    else
        return "";
}

//QByteArray auth(QString log, QString pass)
//{
    //DataBase::sendQuerry("xcdfv");
    //return "auth\n";
//}

//QByteArray reg(QString log, QString pass, QString mail)
//{
    //DataBase::sendQuerry("xcdfv");
    //return "auth\n";
//}
