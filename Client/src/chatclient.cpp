#include "chatclient.h"

ChatClient::ChatClient(QObject *parent) : QObject(parent), m_socket(new QTcpSocket(this)){
    connect(m_socket, &QTcpSocket::connected, this, &ChatClient::connected);
    connect(m_socket, &QTcpSocket::disconnected, this, &ChatClient::disconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &ChatClient::onReadyRead);

    connect(m_socket, &QTcpSocket::errorOccurred, this, [this]() {
        emit errorOccurred(m_socket->errorString());
    });
}

void ChatClient::connectToServer(const QString &ip, quint16 port){
    m_socket->connectToHost(ip, port);
}

void ChatClient::sendMessage(const QByteArray &massage){
    if(m_socket->state() == QAbstractSocket::ConnectedState){
        m_socket->write(massage);
        m_socket->flush();
    }
}

void ChatClient::disconnectFromServer(){
    m_socket->disconnectFromHost();
}

void ChatClient::onReadyRead(){
    QByteArray data = m_socket->readAll();
    emit messageReceived(data);
}