#include <QApplication>
#include <QFile>
#include <QMetaType>
#include <h/mainwindow.h>

#include "net/QwenClient.h"
#include "net/ServerThread.h"
#include "net/ClientSocket.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //RegisterMetaType
    qRegisterMetaType<NetUtils::PatientData>("NetUtils::PatientData");
    qRegisterMetaType<NetUtils::DoctorData>("NetUtils::DoctorData");
    qRegisterMetaType<NetUtils::Appointment>("NetUtils::Appointment");
    qRegisterMetaType<NetUtils::MedicalRecord>("NetUtils::MedicalRecord");
    qRegisterMetaType<NetUtils::Prescription>("NetUtils::Prescription");
    qRegisterMetaType<NetUtils::TestResult>("NetUtils::TestResult");
    qRegisterMetaType<NetUtils::Message>("NetUtils::Message");
    qRegisterMetaType<NetUtils::Medicine>("NetUtils::Medicine");
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");

    QFile file(":/stylesheet.qss");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString styleSheet = QString::fromUtf8(file.readAll());
        qApp->setStyleSheet(styleSheet);
    }

    bool debug = true;

    if(!debug){
        bool isClient=true;
        for(int i=0;i<argc;i++){
            auto arg=QString(argv[i]);
            if(arg.compare("-ai")==0){
                QwenClient::getInstance().setAPI_KEY(argv[i+1]);
                qDebug("Taken Ai ApiKey:%s",argv[i+1]);
                i++;
            }else if(arg.compare("-server")==0){
                isClient=false;
                auto server = new ServerThread(34569);
            }
        }
        if(isClient){
            ClientSocket::getInstance().connectToIP("127.0.0.1",34569);
            w.show();
        }
    }else{
        auto server = new ServerThread(34569);
        ClientSocket::getInstance().connectToIP("127.0.0.1",34569);
        w.show();
    }
    /*ClientSocket::getInstance().submitAppointment((NetUtils::Appointment){
1,2,"2004-04-06",0});*/
    QwenClient::getInstance().ask("我有点腰疼，弯腰的时候腰很酸。我现在正在医院门诊挂号，请你简短地告诉我应该挂什么科室？");

    return a.exec();

}
