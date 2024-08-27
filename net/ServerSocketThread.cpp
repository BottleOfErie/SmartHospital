#include <cstdio>

#include "ServerSocketThread.h"

ServerSocketThread::ServerSocketThread(qintptr descriptor,SqliteOperator*db){
    socketDescripter=descriptor;
    dbop=db;
    buffer = QString();
    alive=true;

    socket=new QTcpSocket();
    socket->setSocketDescriptor(socketDescripter);
    qDebug("ServerSocket connected from:%s",socket->peerAddress().toString().toStdString().data());
    socket->write(NetUtils::wrapMessage("ping"));

    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead_slot()));
    connect(this,SIGNAL(toDoPing()),this,SLOT(doPing_slot()));
    connect(this,SIGNAL(toDoDisconnect()),this,SLOT(doDisconnect_slot()));
    noReplyCount=0;
}

ServerSocketThread::~ServerSocketThread(){
    socket->close();
    delete socket;
}

void ServerSocketThread::run(){
    while (true) {
        emit toDoPing();
        noReplyCount++;
        this->msleep(NetUtils::waitTime/2);
        emit toDoPing();
        noReplyCount++;
        this->msleep(NetUtils::waitTime/2);
        if(noReplyCount>5){
            qDebug("Client No-reply For more than %ld ms,disconnected!",NetUtils::waitTime);
            emit toDoDisconnect();
            alive=false;
            return;
        }
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
    if(noReplyCount>0) noReplyCount--;
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
    else if(str.startsWith("GMsgPat")){
        getMessageAsPatient(arr[1].toLong());
    }else if(str.startsWith("GMsgDoc")){
        getMessageAsDoctor(arr[1].toLong());
    }
    else if(str.startsWith("GMedId")){
        getMedicineById(arr[1].toLong());
    }else if(str.startsWith("GMsgNm")){
        getMedicineByName(arr[1]);
    }

    else if(str.startsWith("SPat")){
        NetUtils::PatientData ret;
        ret.id=arr[1].toLong();
        ret.name=arr[2];
        ret.nationId=arr[3];
        ret.gender=arr[4].toInt();
        ret.birthday=arr[5];
        ret.phoneNumber=arr[6];
        ret.history=arr[7];
        setPatient(ret);
    }else if(str.startsWith("SDoc")){
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
        setDoctor(ret);
    }else if(str.startsWith("SApp")){
        NetUtils::Appointment ret;
        ret.patientId=arr[1].toLong();
        ret.doctorId=arr[2].toLong();
        ret.time=arr[3];
        ret.state=arr[4].toInt();
        setAppointment(ret);
    }else if(str.startsWith("SMrc")){
        NetUtils::MedicalRecord ret;
        ret.patientId=arr[1].toLong();
        ret.doctorId=arr[2].toLong();
        ret.date=arr[3];
        ret.diagnosis=arr[4];
        ret.advice=arr[5];
        setMedicalRecord(ret);
    }else if(str.startsWith("SPst")){
        NetUtils::Prescription ret;
        ret.patientId=arr[1].toLong();
        ret.doctorId=arr[2].toLong();
        ret.date=arr[3];
        ret.medicineId=arr[4].toLong();
        ret.count=arr[5].toInt();
        ret.advice=arr[6];
        setPrescription(ret);
    }else if(str.startsWith("STrs")){
        NetUtils::TestResult ret;
        ret.patientId=arr[1].toLong();
        ret.date=arr[2];
        ret.height=arr[3].toFloat();
        ret.weight=arr[4].toFloat();
        ret.heartRate=arr[5].toInt();
        ret.highBP=arr[6].toFloat();
        ret.lowBP=arr[7].toFloat();
        ret.vitalCapacity=arr[8].toInt();
        setTestResult(ret);
    }else if(str.startsWith("SMsg")){
        NetUtils::Message ret;
        ret.patientId=arr[1].toLong();
        ret.doctorId=arr[2].toLong();
        ret.timeStamp=arr[3].toLongLong();
        ret.sendDirection=arr[4].toInt();
        ret.message=arr[5];
        ret.isRead=arr[6].compare("true")==0;
        setMessage(ret);
    }else if(str.startsWith("SMed")){
        NetUtils::Medicine ret;
        ret.medicineId = arr[1].toLong();
        ret.name=arr[2];
        ret.price=arr[3].toFloat();
        ret.count=arr[4].toLong();
        ret.manufactuer=arr[5];
        ret.batch=arr[6];
        setMedicine(ret);
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
        std::to_string(result.gender),result.birthday.toStdString(),
        result.phoneNumber.toStdString(),result.history.toStdString()
    }));
}
void ServerSocketThread::getPatientDataByNationalId(QString name){
    //Connect DB
    NetUtils::PatientData result={114,"Firefly","514",1,"114","514","1919810"};
    socket->write(NetUtils::wrapStrings({"pat",
        std::to_string(result.id),result.name.toStdString(),result.nationId.toStdString(),
        std::to_string(result.gender),result.birthday.toStdString(),
        result.phoneNumber.toStdString(),result.history.toStdString()
    }));
}

//doc <id> <name> <nationalId> <sex> <birthday> <phoneNumber> <jobTitle> <organization> <section>
void ServerSocketThread::getDoctorDataById(long id){
    //Connect DB
    NetUtils::DoctorData result={114,"Kaltsit","Mon3tr",1,"114","514","主任医师","RhodesIsland","111"};
    socket->write(NetUtils::wrapStrings({"doc",
        std::to_string(result.id),result.name.toStdString(),result.nationId.toStdString(),
        std::to_string(result.gender),result.birthday.toStdString(),result.phoneNumber.toStdString(),
        result.jobTitle.toStdString(),result.organization.toStdString(),result.section.toStdString()
    }));
}
void ServerSocketThread::getDoctorDataByNationalId(QString name){
    //Connect DB
    NetUtils::DoctorData result={114,"Kaltsit","Mon3tr",1,"114","514","主任医师","RhodesIsland","111"};
    socket->write(NetUtils::wrapStrings({"doc",
        std::to_string(result.id),result.name.toStdString(),result.nationId.toStdString(),
        std::to_string(result.gender),result.birthday.toStdString(),result.phoneNumber.toStdString(),
        result.jobTitle.toStdString(),result.organization.toStdString(),result.section.toStdString()
    }));
}
void ServerSocketThread::getDoctorDatasBySection(QString section){
    //Connect DB
    NetUtils::DoctorData result={114,"Kaltsit","Mon3tr",1,"114","514","主任医师","RhodesIsland","111"};
    socket->write(NetUtils::wrapStrings({"doc",
        std::to_string(result.id),result.name.toStdString(),result.nationId.toStdString(),
        std::to_string(result.gender),result.birthday.toStdString(),result.phoneNumber.toStdString(),
        result.jobTitle.toStdString(),result.organization.toStdString(),result.section.toStdString()
    }));
    result={514,"Ptilopsis","Silence",1,"1919","810","副主任医师","RhineLab","111"};
    socket->write(NetUtils::wrapStrings({"doc",
        std::to_string(result.id),result.name.toStdString(),result.nationId.toStdString(),
        std::to_string(result.gender),result.birthday.toStdString(),result.phoneNumber.toStdString(),
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
    socket->write(NetUtils::wrapStrings({"trs",
        std::to_string(result.patientId),result.date.toStdString(),
        std::to_string(result.height),std::to_string(result.weight),
        std::to_string(result.heartRate),std::to_string(result.highBP),
        std::to_string(result.lowBP),std::to_string(result.vitalCapacity)}));
}

//msg <patid> <docid> <time> <dir> <text> <read>
void ServerSocketThread::getMessageAsPatient(long id){
    //Connect DB
    NetUtils::Message result={123,456,114514,0,"1919810",false};
    socket->write(NetUtils::wrapStrings({"msg",
        std::to_string(result.patientId),std::to_string(result.doctorId),
        std::to_string(result.timeStamp),std::to_string(result.sendDirection),
        result.message.toStdString(),result.isRead?"true":"false"}));
}
void ServerSocketThread::getMessageAsDoctor(long id){
    //Connect DB
    NetUtils::Message result={123,456,114514,0,"1919810",false};
    socket->write(NetUtils::wrapStrings({"msg",
        std::to_string(result.patientId),std::to_string(result.doctorId),
        std::to_string(result.timeStamp),std::to_string(result.sendDirection),
        result.message.toStdString(),result.isRead?"true":"false"}));
}

//med <id> <name> <price> <cnt> <manu> <batch>
void ServerSocketThread::getMedicineById(long id){
    //Connect DB
    NetUtils::Medicine result={114,"RedTea",5,14,"123","456"};
    socket->write(NetUtils::wrapStrings({"med",
        std::to_string(result.medicineId),result.name.toStdString(),
        std::to_string(result.price),std::to_string(result.count),
        result.manufactuer.toStdString(),result.batch.toStdString()}));
}
void ServerSocketThread::getMedicineByName(QString name){
    //Connect DB
    NetUtils::Medicine result={114,"RedTea",5,14,"123","456"};
    socket->write(NetUtils::wrapStrings({"med",
        std::to_string(result.medicineId),result.name.toStdString(),
        std::to_string(result.price),std::to_string(result.count),
        result.manufactuer.toStdString(),result.batch.toStdString()}));
}
void ServerSocketThread::setPatient(NetUtils::PatientData data){
    //CDB
}
void ServerSocketThread::setDoctor(NetUtils::DoctorData data){
    //CDB
}
void ServerSocketThread::setAppointment(NetUtils::Appointment data){
    //optimize data structure
    /*if(!dbop->insertAppointment(data.patientId,data.doctorId,data.time,QString(data.state))){
        dbop->updateAppointment(data.patientId,data.doctorId,data.time,QString(data.state));
    }*/
}
void ServerSocketThread::setMedicalRecord(NetUtils::MedicalRecord data){
    if(!dbop->insertMedicalRecord(data.patientId,data.doctorId,data.date,data.diagnosis,data.advice)){
        dbop->updateMedicalRecord(data.patientId,data.doctorId,data.date,data.diagnosis,data.advice);
    }
}
void ServerSocketThread::setPrescription(NetUtils::Prescription data){
    //optimize data structure
    //if(!dbop->insertPrescription(data.patientId,data.doctorId,data.date,))
}
void ServerSocketThread::setTestResult(NetUtils::TestResult data){
    //CDB
    if(!dbop->insertHealthAssessment(data.patientId,data.date,data.height,data.weight,
        data.heartRate,data.highBP,data.lowBP,data.vitalCapacity)){
        dbop->updateHealthAssessment(data.patientId,data.date,data.height,data.weight,
                data.heartRate,data.highBP,data.lowBP,data.vitalCapacity);
    }
}
void ServerSocketThread::setMessage(NetUtils::Message data){
    //data structure
    //if(!dbop->insertChatRecord(data.patientId,data.doctorId,data.timeStamp))
}
void ServerSocketThread::setMedicine(NetUtils::Medicine data){
    //data structure
    //(!dbop->insertMedicine(data.))
}
