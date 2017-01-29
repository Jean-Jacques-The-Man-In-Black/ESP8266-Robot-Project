#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    installEventFilter(this);
    espSocket = new QTcpSocket();
    espSocket->connectToHost("192.168.0.13", 1000);
    espSocket->waitForConnected();
}

MainWindow::~MainWindow()
{
    espSocket->disconnect();
    espSocket->close();
    espSocket->deleteLater();
}


bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type()==QEvent::KeyPress)
    {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        switch(key->key())
        {
        case (Qt::Key_Up):
            up();
            break;
        case (Qt::Key_Right):
            right();
            break;
        case (Qt::Key_Left):
            left();
            break;
        case (Qt::Key_Down):
            down();
            break;
        case (Qt::Key_Space):
            stop();
            break;
        case (Qt::Key_Q):
            close();
            break;
        default:
            return QObject::eventFilter(obj, event);
        }
        return true;
    }
    else
    {
        return QObject::eventFilter(obj, event);
    }
    return false;
}

void MainWindow::up()
{
    QByteArray data;
    unsigned char command = 0x80;
    data.append(command | 0x05);
    data.append(0x03);
    data.append(1);
    data.append(100);
    data.append(1);
    data.append(100);
    espSocket->write(data);
}

void MainWindow::right()
{
    QByteArray data;
    unsigned char command = 0x80;
    data.append(command | 0x05);
    data.append(0x03);
    data.append(1);
    data.append(100);
    data.append((char)0);
    data.append(100);
    espSocket->write(data);
}

void MainWindow::left()
{
    QByteArray data;
    unsigned char command = 0x80;
    data.append(command | 0x05);
    data.append(0x03);
    data.append((char)0);
    data.append(100);
    data.append(1);
    data.append(100);
    espSocket->write(data);
}

void MainWindow::down()
{
    QByteArray data;
    unsigned char command = 0x80;
    data.append(command | 0x05);
    data.append(0x03);
    data.append((char)0);
    data.append(100);
    data.append((char)0);
    data.append(100);
    espSocket->write(data);
}

void MainWindow::stop()
{
    QByteArray data;
    unsigned char command = 0x80;
    data.append(command | 0x05);
    data.append(0x03);
    data.append((char)0);
    data.append((char)0);
    data.append((char)0);
    data.append((char)0);
    espSocket->write(data);
}
