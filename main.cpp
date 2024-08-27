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

    /*ClientSocket::getInstance().submitAppointment((NetUtils::Appointment){
1,2,"2004-04-06",0
                                                  });*/

    return a.exec();

}
