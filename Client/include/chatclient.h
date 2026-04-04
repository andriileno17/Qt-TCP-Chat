#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>

class ChatClient: public QObject{
    Q_OBJECT
    
    public:
        explicit ChatClient(QObject *parent = nullptr);

        void connectToServer(const QString &ip, quint16 port);
        void sendMassage(const QByteArray &massage);
        void disconnectFromServer();

    signals:
        void connected();
        void disconnected();
        void massageRecieved(const QByteArray &massage);
        void errorOccurred(const QString &errorString);

    private slots:
        void onReadyRead();

    private:
        QTcpSocket *m_socket;
};

#endif