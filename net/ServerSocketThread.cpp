#include <cstdio>

#include "ServerSocketThread.h"
#include "NetUtils.h"

ServerSocketThread::ServerSocketThread(qintptr descriptor){
    socketDescripter=descriptor;
    buffer = QString();
    alive=true;

    socket=new QTcpSocket();
    socket->setSocketDescriptor(socketDescripter);
    qDebug("ServerSocket connected from:%s",socket->peerAddress().toString().toStdString().data());
    socket->write(NetUtils::wrapMessage("ping"));

    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead_slot()));
    connect(this,SIGNAL(toDoPing()),this,SLOT(doPing_slot()));
    connect(this,SIGNAL(toDoDisconnect()),this,SLOT(doDisconnect_slot()));
}

ServerSocketThread::~ServerSocketThread(){
    socket->close();
    delete socket;
}

void ServerSocketThread::run(){
    while (true) {
        emit toDoPing();
        msleep(NetUtils::waitTime/2);
        emit toDoPing();
        msleep(NetUtils::waitTime/2);
        if(!hasReply){
            qDebug("Client No-reply For more than %ld ms,disconnected!",NetUtils::waitTime);
            emit toDoDisconnect();
            alive=false;
            return;
        }
        hasReply=false;
    }
}

void ServerSocketThread::doPing_slot(){
    socket->write(NetUtils::wrapMessage("ping"));
}

void ServerSocketThread::doDisconnect_slot(){
    socket->disconnectFromHost();
}

void ServerSocketThread::readyRead_slot(){
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

void ServerSocketThread::doCommand(QString str){
    hasReply=true;
    qDebug("Server Taken:%s",str.toStdString().data());
    auto arr=str.split(NetUtils::messagePartition);
    if(str.startsWith("login")){
        loginCMD(arr[1],arr[2],arr[3].toInt());
    }else if(str.startsWith("GPatId")){
        getPatientDataById(arr[1].toLong());
    }else if(str.startsWith("GPatNm")){
        getPatientDataByNationalId(arr[1]);
    }
    else if(str.startsWith("GDocId")){
        getDoctorDataById(arr[1].toLong());
    }else if(str.startsWith("GDocNm")){
        getDoctorDataByNationalId(arr[1]);
    }else if(str.startsWith("GDosSt")){
        getDoctorDatasBySection(arr[1]);
    }
    else if(str.startsWith("GAppPat")){
        getAppointmentsByPatientId(arr[1].toLong());
    }else if(str.startsWith("GAppDoc")){
        getAppointmentsByDoctorId(arr[1].toLong());
    }
    else if(str.startsWith("GMrcPat")){
        getMedicalRecordsByPatientId(arr[1].toLong());
    }else if(str.startsWith("GMrcDoc")){
        getMedicalRecordsByDoctorId(arr[1].toLong());
    }
    else if(str.startsWith("GPstPat")){
        getPrescriptionsByPatient(arr[1].toLong());
    }else if(str.startsWith("GPstDoc")){
        getPrescriptionsByDoctor(arr[1].toLong());
    }
    else if(str.startsWith("GTrs")){
        getTestResultsByPatient(arr[1].toLong());
    }

    else if(!str.startsWith("ping")){
        qDebug("Unknown Command:%s",str.toStdString().data());
    }
}

//login <true|false>
void ServerSocketThread::loginCMD(QString id,QString passwd,int type){
    qDebug("Trying Login:Id[%s],Pass[%s]Type[%d]",id.toStdString().data(),
           passwd.toStdString().data(),type);
    //Connect DB
    bool result=true;
    socket->write(NetUtils::wrapStrings({"login",result?"true":"false"}));
}

//pat <id> <name> <nationalId> <sex> <birthday> <phoneNumber> <history>
void ServerSocketThread::getPatientDataById(long id){
    //Connect DB
    NetUtils::PatientData result={114,"Firefly","514",1,"114","514","1919810"};
    socket->write(NetUtils::wrapStrings({"pat",
        std::to_string(result.id),result.name.toStdString(),result.nationId.toStdString(),
        std::to_string(result.sex),result.birthday.toStdString(),
        result.phoneNumber.toStdString(),result.history.toStdString()
    }));
}
void ServerSocketThread::getPatientDataByNationalId(QString name){
    //Connect DB
    NetUtils::PatientData result={114,"Firefly","514",1,"114","514","1919810"};
    socket->write(NetUtils::wrapStrings({"pat",
        std::to_string(result.id),result.name.toStdString(),result.nationId.toStdString(),
        std::to_string(result.sex),result.birthday.toStdString(),
        result.phoneNumber.toStdString(),result.history.toStdString()
    }));
}

//doc <id> <name> <nationalId> <sex> <birthday> <phoneNumber> <jobTitle> <organization> <section>
void ServerSocketThread::getDoctorDataById(long id){
    //Connect DB
    NetUtils::DoctorData result={114,"Kaltsit","Mon3tr",1,"114","514","主任医师","RhodesIsland","111"};
    socket->write(NetUtils::wrapStrings({"doc",
        std::to_string(result.id),result.name.toStdString(),result.nationId.toStdString(),
        std::to_string(result.sex),result.birthday.toStdString(),result.phoneNumber.toStdString(),
        result.jobTitle.toStdString(),result.organization.toStdString(),result.section.toStdString()
    }));
}
void ServerSocketThread::getDoctorDataByNationalId(QString name){
    //Connect DB
    NetUtils::DoctorData result={114,"Kaltsit","Mon3tr",1,"114","514","主任医师","RhodesIsland","111"};
    socket->write(NetUtils::wrapStrings({"doc",
        std::to_string(result.id),result.name.toStdString(),result.nationId.toStdString(),
        std::to_string(result.sex),result.birthday.toStdString(),result.phoneNumber.toStdString(),
        result.jobTitle.toStdString(),result.organization.toStdString(),result.section.toStdString()
    }));
}
void ServerSocketThread::getDoctorDatasBySection(QString section){
    //Connect DB
    NetUtils::DoctorData result={114,"Kaltsit","Mon3tr",1,"114","514","主任医师","RhodesIsland","111"};
    socket->write(NetUtils::wrapStrings({"doc",
        std::to_string(result.id),result.name.toStdString(),result.nationId.toStdString(),
        std::to_string(result.sex),result.birthday.toStdString(),result.phoneNumber.toStdString(),
        result.jobTitle.toStdString(),result.organization.toStdString(),result.section.toStdString()
    }));
    result={514,"Ptilopsis","Silence",1,"1919","810","副主任医师","RhineLab","111"};
    socket->write(NetUtils::wrapStrings({"doc",
        std::to_string(result.id),result.name.toStdString(),result.nationId.toStdString(),
        std::to_string(result.sex),result.birthday.toStdString(),result.phoneNumber.toStdString(),
        result.jobTitle.toStdString(),result.organization.toStdString(),result.section.toStdString()
    }));
}

//app <patid> <docid> <date> <state>
void ServerSocketThread::getAppointmentsByDoctorId(long id){
    //Connect DB
    NetUtils::Appointment result={114,514,"191981",0};
    socket->write(NetUtils::wrapStrings({"app",
        std::to_string(result.patientId),std::to_string(result.doctorId),
        result.time.toStdString(),std::to_string(result.state)}));
}
void ServerSocketThread::getAppointmentsByPatientId(long id){
    //Connect DB
    NetUtils::Appointment result={114,514,"191981",0};
    socket->write(NetUtils::wrapStrings({"app",
        std::to_string(result.patientId),std::to_string(result.doctorId),
        result.time.toStdString(),std::to_string(result.state)}));
}

//mrc <patid> <docid> <time> <diag> <advc>
void ServerSocketThread::getMedicalRecordsByPatientId(long id){
    //Connect DB
    NetUtils::MedicalRecord result={114,514,"19","19","810"};
    socket->write(NetUtils::wrapStrings({"mrc",
        std::to_string(result.patientId),std::to_string(result.doctorId),result.date.toStdString(),
        result.diagnosis.toStdString(),result.advice.toStdString()}));
}
void ServerSocketThread::getMedicalRecordsByDoctorId(long id){
    //Connect DB
    NetUtils::MedicalRecord result={114,514,"19","19","810"};
    socket->write(NetUtils::wrapStrings({"mrc",
        std::to_string(result.patientId),std::to_string(result.doctorId),result.date.toStdString(),
        result.diagnosis.toStdString(),result.advice.toStdString()}));
}

//pst <patid> <docid> <date> <medid> <cnt> <advc>
void ServerSocketThread::getPrescriptionsByPatient(long id){
    //Connect DB
    NetUtils::Prescription result={114,514,"19",1,2,"11"};
    socket->write(NetUtils::wrapStrings({"pst",
        std::to_string(result.patientId),std::to_string(result.doctorId),result.date.toStdString(),
        std::to_string(result.medicineId),std::to_string(result.count),result.advice.toStdString()}));
}
void ServerSocketThread::getPrescriptionsByDoctor(long id){
    //Connect DB
    NetUtils::Prescription result={114,514,"19",1,2,"11"};
    socket->write(NetUtils::wrapStrings({"pst",
        std::to_string(result.patientId),std::to_string(result.doctorId),result.date.toStdString(),
        std::to_string(result.medicineId),std::to_string(result.count),result.advice.toStdString()}));
}

//trs <patid> <date> <height> <weight> <HR> <hBP> <lBP> <VC>
void ServerSocketThread::getTestResultsByPatient(long id){
    //Connect DB
    NetUtils::TestResult result={123,"456",1,1,4,5,1,4};
    socket->write(NetUtils::wrapStrings({"pst",
        std::to_string(result.patientId),result.date.toStdString(),
        std::to_string(result.height),std::to_string(result.weight),
        std::to_string(result.heartRate),std::to_string(result.highBP),
        std::to_string(result.lowBP),std::to_string(result.vitalCapacity)}));
}
