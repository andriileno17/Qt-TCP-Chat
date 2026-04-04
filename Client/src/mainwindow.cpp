#include "mainwindow.h"
#include <QMessageBox>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_client(new ChatClient(this))
{
    // 1. СТВОРЮЄМО БАЗУ ВІКНА
    // У QMainWindow обов'язково має бути "центральний віджет", на який ми все складемо
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    setWindowTitle("Mini chat (Client)");
    resize(400, 500); // Стартовий розмір вікна

    // 2. СТВОРЮЄМО ВІДЖЕТИ
    chatDisplay = new QTextEdit(this);
    chatDisplay->setReadOnly(true); // Забороняємо друкувати прямо у вікні історії

    messageLineEdit = new QLineEdit(this);
    messageLineEdit->setPlaceholderText("Enter massage ... ");

    connectButton = new QPushButton("Connect to server", this);
    sendButton = new QPushButton("Send", this);

    // 3. РОЗМІЩУЄМО ВІДЖЕТИ (Layouts)
    // Головний вертикальний компонувальник (зверху вниз)
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    
    // Горизонтальний компонувальник для поля вводу і кнопки "Відправити" (зліва направо)
    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(messageLineEdit);
    bottomLayout->addWidget(sendButton);

    // Складаємо все в головний Layout
    mainLayout->addWidget(chatDisplay);
    mainLayout->addLayout(bottomLayout); // Вкладаємо горизонтальний у вертикальний
    mainLayout->addWidget(connectButton);

    // 4. ПІДКЛЮЧАЄМО КНОПКИ (СИГНАЛИ -> СЛОТИ)
    // Це професійний синтаксис підключення (Pointer to Member Function)
    connect(connectButton, &QPushButton::clicked, this, &MainWindow::onConnectClicked);
    connect(sendButton, &QPushButton::clicked, this, &MainWindow::onSendClicked);
    
    // Щоб можна було відправляти повідомлення клавішею Enter
    connect(messageLineEdit, &QLineEdit::returnPressed, this, &MainWindow::onSendClicked);

    // 5. ПІДКЛЮЧАЄМО МЕРЕЖЕВУ ЛОГІКУ
    connect(m_client, &ChatClient::connected, this, &MainWindow::onClientConnected);
    connect(m_client, &ChatClient::disconnected, this, &MainWindow::onClientDisconnected);
    connect(m_client, &ChatClient::messageReceived, this, &MainWindow::onMessageReceived);
    connect(m_client, &ChatClient::errorOccurred, this, &MainWindow::onError);
}

MainWindow::~MainWindow() {
    // Нам не треба видаляти віджети вручну, бо всі вони створені з parent (this)
    // Qt очистить пам'ять автоматично при закритті вікна
}

void MainWindow::on_connectButton_clicked(){
    m_client->connectToServer("127.0.0.1", 1234);
}

void MainWindow::on_sendButton_clicked(){
    QString text = ui->messageLineEdit->text();
    if (!text.isEmpty()){
        m_client->sendMassage(text.toUtf8());
        ui->messageLineEdit->clear();
    }
}

void MainWindow::onClientConnected(){
    ui->chatDisplay->append("=== Connected to server ===");
}

void MainWindow::onClientDisconnected() {
    ui->chatDisplay->append("=== Disconnected from server ===");
}

void MainWindow::onMessageReceived(const QByteArray &message) {
    ui->chatDisplay->append("Someone: " + QString::fromUtf8(message));
}

void MainWindow::onError(const QString &error) {
    QMessageBox::critical(this, "Net error ", error);
}