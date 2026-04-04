#include "chatserver.h"
#include <QDebug>

ChatServer::ChatServer(QObject *parent): QTcpServer(parent){}

bool ChatServer::startServer(quint16 port){
    if(listen(QHostAddress::Any, port)){
        qDebug() << "Server is started in port: " << port;
        return true;
    }
    qDebug() << "error starting server: " << errorString();
    return false;
}

void ChatServer::incomingConnection(qintptr socketDescriptor){
    QTcpSocket *clientSocket = new QTcpSocket(this);

    if(clientSocket->setSocketDescriptor(socketDescriptor)){
        connect(clientSocket, &QTcpSocket::readyRead, this, &ChatServer::onReadyRead);
        connect(clientSocket, &QTcpSocket::disconnected, this, &ChatServer::onDisconnected);

        m_clients.append(clientSocket);
        qDebug() << "New client connected! " << m_clients.size() << " clients in total.";
    } else {
        delete clientSocket;
    }
}

void ChatServer::onReadyRead(){
    QTcpSocket *senderSocket = qobject_cast<QTcpSocket*>(sender());
    if (!senderSocket) return;

    QByteArray data  = senderSocket->readAll();

    for(QTcpSocket *client : m_clients){
        if(client->state() == QAbstractSocket::ConnectedState){
            client->write(data);
            client->flush();
        }
    }
}

void ChatServer::onDisconnected(){
    QTcpSocket *senderSocket = qobject_cast<QTcpSocket*>(sender());
    if(!senderSocket) return;

    m_clients.removeAll(senderSocket);
    qDebug() << "Client disconnected! " << m_clients.size() << "clients in total.";

    senderSocket->deleteLater();
}