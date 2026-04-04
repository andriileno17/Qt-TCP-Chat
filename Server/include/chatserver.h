#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

class ChatServer: public QTcpServer{
    Q_OBJECT
    public:
        explicit ChatServer(QObject *parent = nullptr);
        bool startServer(quint16 port);
    
    protected:
        void incomingConnection(qintptr socketDescriptior) override;

    private slots:
        void onReadyRead();
        void onDisconnected();

    private:
        QList<QTcpSocket*> m_clients;
};

#endif