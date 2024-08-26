#include <QApplication>
#include <h/mainwindow.h>

#include "net/ServerThread.h"
#include "net/ClientSocket.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    qDebug("Started\n");

    auto server = new ServerThread(34569);
    ClientSocket::getInstance().connectToIP("127.0.0.1",34569);

    ClientSocket::getInstance().getTestResultsByPatient(111);

    return a.exec();

}
