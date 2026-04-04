#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "chatclient.h"

class MainWindow: public: QMainWindow{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void onConnectClicked();
        void onSendClicked();

        void onClientConnected();
        void onClientDisconnected();
        void onMessageReceived(const QByteArray &message);
        void onError(const QString &error);

    private:
        ChatClient *m_client;

        QTextEdit *chatDisplay;
        QLineEdit *messageLineEdit;
        QPushButton *connectButton;
        QPushButton *sendButton;
};

#endif