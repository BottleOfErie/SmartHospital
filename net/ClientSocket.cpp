#include <string>
#include<QHostAddress>
#include <QTime>
#include"h/usernow.h"
#include "ClientSocket.h"

ClientSocket::ClientSocket(){

    connect(this,SIGNAL(login_callback(long long)),this,SLOT(login_slot(long long)));
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
    socketIp=ip;
    socketPort=port;
    this->start();
}

void ClientSocket::socketSend(QByteArray data){
    sendBuffer+=data;
}

void ClientSocket::run(){
    socket=new QTcpSocket();

    connect(socket,SIGNAL(connected()),this,SLOT(connected_slot()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected_slot()));
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(error_slot(QAbstractSocket::SocketError)));

    socket->connectToHost(QHostAddress(socketIp),socketPort);
    while(true){
        if(sendBuffer.length()>0){
            socket->write(sendBuffer);
            //qDebug("Out TIme:%s %s",QTime::currentTime().toString("HH:mm:ss:zzz").toStdString().data(),sendBuffer.toStdString().data());
            sendBuffer.clear();
        }
        if(socket->waitForReadyRead(100)){
            buffer+=socket->readAll();
            //qDebug("In TIme:%s %s",QTime::currentTime().toString("HH:mm:ss:zzz").toStdString().data(),buffer.toStdString().data());
            int pre=buffer.indexOf(NetUtils::messagePrefix);
            while(pre>=0){
                buffer=buffer.mid(pre);
                int suff=buffer.indexOf(NetUtils::messageSuffix);
                if(suff>0){
                    doCommand(
                                buffer.mid(
                                    NetUtils::messagePrefix.length()
                                    ,suff-NetUtils::messagePrefix.length()));
                    buffer=buffer.mid(suff);
                }
                pre=buffer.indexOf(NetUtils::messagePrefix);
            }
        }
    }
}

void ClientSocket::login_slot(long long result){
    qDebug("ClientLogin:%s",result>0?"Success":"Failure");
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
    if(socketError!=5)
        qDebug("ClientSocket:Error %d",socketError);
}

void ClientSocket::doCommand(QString command){
    if(command.compare("ping")!=0)
        qDebug("[%s]Client:%s",QTime::currentTime().toString("HH:mm:ss:zzz").toStdString().data(),command.toStdString().data());
    auto arr=command.split(NetUtils::messagePartition);
    if(command.startsWith("ping")){
        socketSend(NetUtils::wrapMessage("ping"));
    }else if(command.startsWith("login")){
        emit login_callback(arr[1].toLongLong());
    }else if(command.startsWith("RPas")){
        emit resetPassword_callback(arr[1].compare("true")==0);
    }else if(command.startsWith("pat")){
        //pat <id> <name> <nationalId> <sex> <birthday> <phoneNumber> <history>
        NetUtils::PatientData ret;
        ret.id=arr[1].toLong();
        ret.name=arr[2];
        ret.nationId=arr[3];
        ret.gender=arr[4].toInt();
        ret.birthday=arr[5];
        ret.phoneNumber=arr[6];
        ret.history=arr[7];
        emit patient_callback(ret);
    }else if(command.startsWith("doc")){
        //doc <id> <name> <nationalId> <sex> <birthday> <phoneNumber> <jobTitle> <organization> <section> <workingId>
        NetUtils::DoctorData ret;
        ret.id=arr[1].toLong();
        ret.name=arr[2];
        ret.nationId=arr[3];
        ret.gender=arr[4].toInt();
        ret.birthday=arr[5];
        ret.phoneNumber=arr[6];
        ret.jobTitle=arr[7];
        ret.organization=arr[8];
        ret.section=arr[9];
        ret.workingId=arr[10];
        emit doctor_callback(ret);
    }else if(command.startsWith("app")){
        //app <patid> <docid> <date> <state>
        NetUtils::Appointment ret;
        ret.patientId=arr[1].toLong();
        ret.doctorId=arr[2].toLong();
        ret.time=arr[3];
        ret.state=arr[4].toInt();
        emit appointment_callback(ret);
    }else if(command.startsWith("mrc")){
        //mrc <patid> <docid> <time> <diag> <advc>
        NetUtils::MedicalRecord ret;
        ret.patientId=arr[1].toLong();
        ret.doctorId=arr[2].toLong();
        ret.date=arr[3];
        ret.diagnosis=arr[4];
        ret.advice=arr[5];
        emit medicalRecord_callback(ret);
    }else if(command.startsWith("pst")){
        //pst <patid> <docid> <date> <medid> <cnt> <advc>
        NetUtils::Prescription ret;
        ret.patientId=arr[1].toLong();
        ret.doctorId=arr[2].toLong();
        ret.date=arr[3];
        ret.medicineId=arr[4].toLong();
        ret.count=arr[5].toInt();
        ret.advice=arr[6];
        emit prescription_callback(ret);
    }else if(command.startsWith("trs")){
        //trs <patid> <date> <height> <weight> <HR> <hBP> <lBP> <VC>
        NetUtils::TestResult ret;
        ret.patientId=arr[1].toLong();
        ret.date=arr[2];
        ret.height=arr[3].toFloat();
        ret.weight=arr[4].toFloat();
        ret.heartRate=arr[5].toInt();
        ret.highBP=arr[6].toFloat();
        ret.lowBP=arr[7].toFloat();
        ret.vitalCapacity=arr[8].toInt();
        emit testResult_callback(ret);
    }else if(command.startsWith("msg")){
        //msg <patid> <docid> <time> <dir> <text> <read>
        NetUtils::Message ret;
        ret.patientId=arr[1].toLong();
        ret.doctorId=arr[2].toLong();
        ret.timeStamp=arr[3].toLongLong();
        ret.sendDirection=arr[4].toInt();
        ret.message=arr[5];
        ret.isRead=arr[6].compare("true")==0;
        emit message_callback(ret);
    }else if(command.startsWith("med")){
        //med <id> <name> <price> <cnt> <manu> <batch>
        NetUtils::Medicine ret;
        ret.medicineId = arr[1].toLong();
        ret.name=arr[2];
        ret.price=arr[3].toFloat();
        ret.count=arr[4].toLong();
        ret.manufactuer=arr[5];
        ret.batch=arr[6];
        emit medicine_callback(ret);
    }else if(command.startsWith("reg")){
        emit register_callback(arr[1].toLongLong());
    }
}

//RDoc
void ClientSocket::registerAsDoctor(QString nationalId, QString passwd){
    socketSend(NetUtils::wrapStrings({"RDoc",nationalId.toStdString(),passwd.toStdString()}));
}

//RPat
void ClientSocket::registerAsPatient(QString nationalId, QString passwd){
    socketSend(NetUtils::wrapStrings({"RPat",nationalId.toStdString(),passwd.toStdString()}));
}

//login <id> <passwd> <type>
void ClientSocket::loginC(QString id, QString passwd,int type){
    auto typestr=std::to_string(type);
    socketSend(NetUtils::wrapStrings({"login",id.toStdString(),passwd.toStdString(),typestr}));
}

//RP <id> <old> <new>
void ClientSocket::resetPassword(long id, QString oldpasswd, QString newpasswd){
    socketSend(NetUtils::wrapStrings({"RP",std::to_string(id),
        oldpasswd.toStdString(),newpasswd.toStdString()}));
}

//GPatId <id>
void ClientSocket::getPatientById(long id){
    socketSend(NetUtils::wrapStrings({"GPatId",std::to_string(id)}));
}

//GPatNm <id>
void ClientSocket::getPatientByNationalId(QString nationalId){
    socketSend(NetUtils::wrapStrings({"GPatNm",nationalId.toStdString()}));
}

//GDocId <id>
void ClientSocket::getDoctorDataById(long id){
    socketSend(NetUtils::wrapStrings({"GDocId",std::to_string(id)}));
}

//GDocNm <name>
void ClientSocket::getDoctorByNationalId(QString nationalId){
    socketSend(NetUtils::wrapStrings({"GDocNm",nationalId.toStdString()}));
}

//GDosSt <section>
void ClientSocket::getDoctorsBySection(QString section){
    socketSend(NetUtils::wrapStrings({"GDosSt",section.toStdString()}));
}

//GAppPat <id>
void ClientSocket::getAppointmentsByPatient(long id){
    socketSend(NetUtils::wrapStrings({"GAppPat",std::to_string(id)}));
}

//GAppDoc <id>
void ClientSocket::getAppointmentsByDoctor(long id){
    socketSend(NetUtils::wrapStrings({"GAppDoc",std::to_string(id)}));
}

//GMrcPat <id>
void ClientSocket::getMedicalRecordsByPatient(long id){
    socketSend(NetUtils::wrapStrings({"GMrcPat",std::to_string(id)}));
}

//GMrcDoc <id>
void ClientSocket::getMedicalRecordsByDoctor(long id){
    socketSend(NetUtils::wrapStrings({"GMrcDoc",std::to_string(id)}));
}

//GPstPat <id>
void ClientSocket::getPrescriptionsByPatient(long id){
    socketSend(NetUtils::wrapStrings({"GPstPat",std::to_string(id)}));
}

//GPstDoc <id>
void ClientSocket::getPrescriptionsByDoctor(long id){
    socketSend(NetUtils::wrapStrings({"GPstDoc",std::to_string(id)}));
}

//GTrs <id>
void ClientSocket::getTestResultsByPatient(long id){
    socketSend(NetUtils::wrapStrings({"GTrs",std::to_string(id)}));
}

//GMsgDoc <id>
void ClientSocket::getMessageAsDoctor(long id){
    socketSend(NetUtils::wrapStrings({"GMsgDoc",std::to_string(id)}));
}

//GMsgPat <id>
void ClientSocket::getMessageAsPatient(long id){
    socketSend(NetUtils::wrapStrings({"GMsgPat",std::to_string(id)}));
}

//GMedId <id>
void ClientSocket::getMedicineById(long id){
    socketSend(NetUtils::wrapStrings({"GMedId",std::to_string(id)}));
}

//GMedNm <name>
void ClientSocket::getMedicineByName(QString name){
    socketSend(NetUtils::wrapStrings({"GMedNm",name.toStdString()}));
}

//SPat <id> <name> <nationalId> <sex> <birthday> <phoneNumber> <history>
void ClientSocket::submitPatientData(NetUtils::PatientData data){
    socketSend(NetUtils::wrapStrings({"SPat",
        std::to_string(data.id),data.name.toStdString(),data.nationId.toStdString(),
        std::to_string(data.gender),data.birthday.toStdString(),
        data.phoneNumber.toStdString(),data.history.toStdString()
    }));
}

//SDoc <id> <name> <nationalId> <sex> <birthday> <phoneNumber> <jobTitle> <organization> <section> <workingId>
void ClientSocket::submitDoctorData(NetUtils::DoctorData data){
    socketSend(NetUtils::wrapStrings({"SDoc",
        std::to_string(data.id),data.name.toStdString(),data.nationId.toStdString(),
        std::to_string(data.gender),data.birthday.toStdString(),data.phoneNumber.toStdString(),
        data.jobTitle.toStdString(),data.organization.toStdString(),data.section.toStdString(),
        data.workingId.toStdString()
    }));
}

//SApp <patid> <docid> <date> <state>
void ClientSocket::submitAppointment(NetUtils::Appointment data){
    socketSend(NetUtils::wrapStrings({"SApp",
        std::to_string(data.patientId),std::to_string(data.doctorId),
        data.time.toStdString(),std::to_string(data.state)}));
}

//SMrc <patid> <docid> <time> <diag> <advc>
void ClientSocket::submitMedicalRecord(NetUtils::MedicalRecord data){
    socketSend(NetUtils::wrapStrings({"SMrc",
        std::to_string(data.patientId),std::to_string(data.doctorId),data.date.toStdString(),
        data.diagnosis.toStdString(),data.advice.toStdString()}));
}

//SPst <patid> <docid> <date> <medid> <cnt> <advc>
void ClientSocket::submitPrescription(NetUtils::Prescription data){
    socketSend(NetUtils::wrapStrings({"SPst",
        std::to_string(data.patientId),std::to_string(data.doctorId),data.date.toStdString(),
        std::to_string(data.medicineId),std::to_string(data.count),data.advice.toStdString()}));
}

//STrs <patid> <date> <height> <weight> <HR> <hBP> <lBP> <VC>
void ClientSocket::submitTestResult(NetUtils::TestResult data){
    socketSend(NetUtils::wrapStrings({"STrs",
        std::to_string(data.patientId),data.date.toStdString(),
        std::to_string(data.height),std::to_string(data.weight),
        std::to_string(data.heartRate),std::to_string(data.highBP),
        std::to_string(data.lowBP),std::to_string(data.vitalCapacity)}));
}

//SMsg <patid> <docid> <time> <dir> <text> <read>
void ClientSocket::submitMessage(NetUtils::Message data){
    socketSend(NetUtils::wrapStrings({"SMsg",
        std::to_string(data.patientId),std::to_string(data.doctorId),
        std::to_string(data.timeStamp),std::to_string(data.sendDirection),
        data.message.toStdString(),data.isRead?"true":"false"}));
}

//SMed <id> <name> <price> <cnt> <manu> <batch>
void ClientSocket::submitMedicine(NetUtils::Medicine data){
    socketSend(NetUtils::wrapStrings({"SMed",
        std::to_string(data.medicineId),data.name.toStdString(),
        std::to_string(data.price),std::to_string(data.count),
        data.manufactuer.toStdString(),data.batch.toStdString()}));
}
