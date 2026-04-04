#include "mainwindow.h"
#include <QMessageBox>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_client(new ChatClient(this))
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    setWindowTitle("Міні Чат (Клієнт)");
    resize(400, 500);

    chatDisplay = new QTextEdit(this);
    chatDisplay->setReadOnly(true);

    nicknameLineEdit = new QLineEdit(this);
    nicknameLineEdit->setPlaceholderText("Нік...");
    nicknameLineEdit->setFixedWidth(100);

    messageLineEdit = new QLineEdit(this);
    messageLineEdit->setPlaceholderText("Введіть повідомлення...");

    connectButton = new QPushButton("Підключитися", this);
    sendButton = new QPushButton("Відправити", this);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout *bottomLayout = new QHBoxLayout();
    
    bottomLayout->addWidget(nicknameLineEdit);
    bottomLayout->addWidget(messageLineEdit);
    bottomLayout->addWidget(sendButton);

    mainLayout->addWidget(chatDisplay);
    mainLayout->addLayout(bottomLayout);
    mainLayout->addWidget(connectButton);

    connect(connectButton, &QPushButton::clicked, this, &MainWindow::onConnectClicked);
    connect(sendButton, &QPushButton::clicked, this, &MainWindow::onSendClicked);
    connect(messageLineEdit, &QLineEdit::returnPressed, this, &MainWindow::onSendClicked);

    connect(m_client, &ChatClient::connected, this, &MainWindow::onClientConnected);
    connect(m_client, &ChatClient::disconnected, this, &MainWindow::onClientDisconnected);
    connect(m_client, &ChatClient::messageReceived, this, &MainWindow::onMessageReceived);
    connect(m_client, &ChatClient::errorOccurred, this, &MainWindow::onError);
}

MainWindow::~MainWindow() {}

void MainWindow::onConnectClicked() {
    m_client->connectToServer("127.0.0.1", 1234);
    connectButton->setEnabled(false);
}

void MainWindow::onSendClicked() {
    QString text = messageLineEdit->text();
    QString nickname = nicknameLineEdit->text();

    if (nickname.isEmpty()) {
        nickname = "Анонім";
    }

if (!text.isEmpty()) {
        QString fullMessage = nickname + ": " + text;
        
        m_client->sendMessage(fullMessage.toUtf8());
        
        messageLineEdit->clear();
    }
}

void MainWindow::onClientConnected() {
    chatDisplay->append("=== Підключено до сервера ===");
}

void MainWindow::onClientDisconnected() {
    chatDisplay->append("=== Відключено від сервера ===");
    connectButton->setEnabled(true);
}

void MainWindow::onMessageReceived(const QByteArray &message) {
    chatDisplay->append(QString::fromUtf8(message));
}

void MainWindow::onError(const QString &error) {
    QMessageBox::critical(this, "Помилка мережі", error);
    connectButton->setEnabled(true);
}