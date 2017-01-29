#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QTcpSocket>
#include <QByteArray>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void up();
    void right();
    void left();
    void down();
    void stop();

protected:
    QTcpSocket *espSocket;
    bool eventFilter(QObject* obj, QEvent* event);
};

#endif // MAINWINDOW_H
