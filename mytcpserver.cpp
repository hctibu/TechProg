#include "mytcpserver.h"
#include "functionsforserver.h"
#include <QDebug>
#include <QCoreApplication>
#include<QString>

MyTcpServer::~MyTcpServer()
{

    mTcpServer->close();
    //server_status=0;
}

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent){
    mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 12345)){
        qDebug() << "server is not started";
    } else {
        //server_status=1;
        qDebug() << "server is started";
    }
}

void MyTcpServer::slotNewConnection()
{
    QTcpSocket *newSocket = mTcpServer->nextPendingConnection();
    mTcpSockets.append(newSocket);

    newSocket->write("Hello, World!!! I am echo server!\r\n");

    connect(newSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
    connect(newSocket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);
}


void MyTcpServer::slotServerRead()
{
    for (QTcpSocket *socket : mTcpSockets)
    {
        if (socket->bytesAvailable() <= 0)
        {
            continue;
        }

        QByteArray response = socket->readAll();
        QString message = QString::fromUtf8(response).trimmed();
        qDebug() << "Received message: " << message;

        if (message == "Hello")
        {
            socket->write("Hello, client!\r\n");
        }
        else if (message == "How are you?")
        {
            socket->write("I'm fine, thank you!\r\n");
        }
        else
        {
            QByteArray parsedResponse = parsing(message);
            socket->write(parsedResponse);
        }
    }
}

void MyTcpServer::slotClientDisconnected()
{
    QTcpSocket *disconnectedSocket = qobject_cast<QTcpSocket*>(sender());
    if (disconnectedSocket)
    {
        mTcpSockets.removeOne(disconnectedSocket);
        disconnectedSocket->deleteLater();
    }
}

