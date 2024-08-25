#include <string>
#include<QHostAddress>

#include "ClientSocket.h"

ClientSocket::ClientSocket(){
    socket=new QTcpSocket(this);

    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead_slot()));
    connect(socket,SIGNAL(connected()),this,SLOT(connected_slot()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected_slot()));
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),
        this,SLOT(error_slot(QAbstractSocket::SocketError)));
}

ClientSocket::~ClientSocket(){
    if(socket!=nullptr)
        delete socket;
}

ClientSocket& ClientSocket::getInstance(){
    static ClientSocket instance;
    return instance;
}

void ClientSocket::connectToIP(QString ip, int port){
    socket->connectToHost(QHostAddress(ip),port);
}

void ClientSocket::readyRead_slot(){
    buffer+=socket->readAll();
    int pre=buffer.indexOf(NetUtils::messagePrefix);
    if(pre>=0){
        buffer=buffer.mid(pre);
        int suff=buffer.indexOf(NetUtils::messageSuffix);
        if(suff>0){
            doCommand(
                        buffer.mid(
                            NetUtils::messagePrefix.length()
                            ,suff-NetUtils::messagePrefix.length()));
            buffer=buffer.mid(suff);
        }
    }
}

void ClientSocket::connected_slot(){
    qDebug("ClientSocket:Connected\n");
    emit connected();
}

void ClientSocket::disconnected_slot(){
    qDebug("ClientSocket:Disconnected\n");
    emit disconnected();
}

void ClientSocket::error_slot(QAbstractSocket::SocketError socketError){
    qDebug("ClientSocket:Error %d\n",socketError);
}

void ClientSocket::doCommand(QString command){
    qDebug("Client Taken:%s",command.toStdString().data());
    auto arr=command.split(NetUtils::messagePartition);
    if(command.startsWith("ping")){
        socket->write(NetUtils::wrapMessage("ping"));
    }else if(command.startsWith("login")){
        emit login_callback(arr[1].compare("true")==0);
    }else if(command.startsWith("pat")){
        //pat <id> <name> <nationalId> <sex> <birthday> <phoneNumber> <history>
        NetUtils::PatientData ret;
        ret.id=arr[1].toLong();
        ret.name=arr[2];
        ret.nationId=arr[3];
        ret.sex=arr[4].toInt();
        ret.birthday=arr[5];
        ret.phoneNumber=arr[6];
        ret.history=arr[7];
        emit patient_callback(ret);
    }else if(command.startsWith("doc")){
        //doc <id> <name> <nationalId> <sex> <birthday> <phoneNumber> <jobTitle> <organization> <section>
        NetUtils::DoctorData ret;
        ret.id=arr[1].toLong();
        ret.name=arr[2];
        ret.nationId=arr[3];
        ret.sex=arr[4].toInt();
        ret.birthday=arr[5];
        ret.phoneNumber=arr[6];
        ret.jobTitle=arr[7];
        ret.organization=arr[8];
        ret.section=arr[9];
        emit doctor_callback(ret);
    }else if(command.startsWith("app")){
        //app <patid> <docid> <date> <state>
        NetUtils::Appointment ret;
        ret.patientId=arr[1].toLong();
        ret.doctorId=arr[2].toLong();
        ret.time=arr[3];
        ret.state=arr[4].toUInt();
        emit appointment_callback(ret);
    }
}

//login <id> <passwd> <type>
void ClientSocket::loginC(QString id, QString passwd,int type){
    auto typestr=std::to_string(type);
    socket->write(NetUtils::wrapStrings({"login",id.toStdString(),passwd.toStdString(),typestr}));
}

//GPatId <id>
void ClientSocket::getPatientById(long id){
    socket->write(NetUtils::wrapStrings({"GPatId",std::to_string(id)}));
}

//GPatNm <id>
void ClientSocket::getPatientByNationalId(QString nationalId){
    socket->write(NetUtils::wrapStrings({"GPatNm",nationalId.toStdString()}));
}

//GDocId <id>
void ClientSocket::getDoctorDataById(long id){
    socket->write(NetUtils::wrapStrings({"GDocId",std::to_string(id)}));
}

//GDocNm <name>
void ClientSocket::getDoctorByNationalId(QString nationalId){
    socket->write(NetUtils::wrapStrings({"GDocNm",nationalId.toStdString()}));
}

//GDosSt <section>
void ClientSocket::getDoctorsBySection(QString section){
    socket->write(NetUtils::wrapStrings({"GDosSt",section.toStdString()}));
}

//GAppPat <id>
void ClientSocket::getAppointmentsByPatient(long id){
    socket->write(NetUtils::wrapStrings({"GAppPat",std::to_string(id)}));
}

//GAppDoc <id>
void ClientSocket::getAppointmentsByDoctor(long id){
    socket->write(NetUtils::wrapStrings({"GAppDoc",std::to_string(id)}));
}
