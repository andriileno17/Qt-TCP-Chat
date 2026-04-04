#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>

class ChatClient : public QObject {
    Q_OBJECT

public:
    explicit ChatClient(QObject *parent = nullptr);
    
    void connectToServer(const QString &ip, quint16 port);
    void sendMessage(const QByteArray &message);
    void disconnectFromServer();

signals:
    void connected();
    void disconnected();
    void messageReceived(const QByteArray &message);
    void errorOccurred(const QString &errorString);

private slots:
    void onReadyRead();

private:
    QTcpSocket *m_socket;
};

#endif