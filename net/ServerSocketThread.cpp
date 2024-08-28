#include <cstdio>
#include <QTime>
#include <QCoreApplication>

#include "ServerSocketThread.h"

ServerSocketThread::ServerSocketThread(qintptr descriptor,SqliteOperator*db){
    socketDescripter=descriptor;
    dbop=db;
    buffer = QString();
    alive=true;

    connect(this,SIGNAL(toDoDisconnect()),this,SLOT(doDisconnect_slot()));
    noReplyCount=0;
}

ServerSocketThread::~ServerSocketThread(){
    socket->close();
    delete socket;
}

void ServerSocketThread::run(){
    socket=new QTcpSocket();
    socket->setSocketDescriptor(socketDescripter);
    qDebug("ServerSocket connected from:%s",socket->peerAddress().toString().toStdString().data());
    socket->write(NetUtils::wrapMessage("ping"));
    while (true) {
        if(socket->waitForReadyRead(NetUtils::waitTime/5)){
            buffer+=socket->readAll();
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
        }else{
            socket->write(NetUtils::wrapMessage("ping"));
            noReplyCount++;
        }
        if(noReplyCount>5){
            qDebug("Client No-reply For more than %ld ms,disconnected!",5*NetUtils::waitTime);
            emit toDoDisconnect();
            alive=false;
            return;
        }
    }
}

void ServerSocketThread::doDisconnect_slot(){
    socket->disconnectFromHost();
}


void ServerSocketThread::doCommand(QString str){
    if(noReplyCount>0) noReplyCount--;
    if(str.compare("ping")!=0)
        qDebug("[%s]Server:%s",QTime::currentTime().toString("HH:mm:ss:zzz").toStdString().data(),str.toStdString().data());
    auto arr=str.split(NetUtils::messagePartition);
    if(str.startsWith("login")){
        loginCMD(arr[1],arr[2],arr[3].toInt());
    }else if(str.startsWith("RDoc")){
        registerAsDoctor(arr[1],arr[2]);
    }else if(str.startsWith("RPat")){
        registerAsPatient(arr[1],arr[2]);
    }
    else if(str.startsWith("GPatId")){
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
    if(dbop->validateLogin(id,passwd)){
        if(type==0){
            auto pat=dbop->queryPatientByNationId(id);
            if(pat.length()>0){
                socket->write(NetUtils::wrapStrings({"login",std::to_string(pat.first().id)}));
                return;
            }
        }else if(type==1){
            auto doc=dbop->queryDoctorByNationId(id);
            if(doc.length()>0){
                socket->write(NetUtils::wrapStrings({"login",std::to_string(doc.first().id)}));
                return;
            }
        }
    }
    socket->write(NetUtils::wrapStrings({"login","-1"}));
}

//reg <id>
void ServerSocketThread::registerAsDoctor(QString nationalId, QString passwd){
    if(dbop->Login(nationalId,passwd)){
        dbop->insertDoctor("","",nationalId,-1,"","","","","");
        auto doc=dbop->queryDoctorByNationId(nationalId);
        if(doc.length()>0){
            socket->write(NetUtils::wrapStrings({"reg",std::to_string(doc.first().id)}));
            return;
        }
    }
    socket->write(NetUtils::wrapStrings({"reg","-1"}));
}
void ServerSocketThread::registerAsPatient(QString nationalId, QString passwd){
    if(dbop->Login(nationalId,passwd)){
        dbop->insertPatient("",nationalId,-1,"","","");
        auto pat=dbop->queryPatientByNationId(nationalId);
        if(pat.length()>0){
            socket->write(NetUtils::wrapStrings({"reg",std::to_string(pat.first().id)}));
            return;
        }
    }
    socket->write(NetUtils::wrapStrings({"reg","-1"}));
}

void ServerSocketThread::resetPassword(long id, QString oldpasswd, QString newpasswd){
    //ODS
    socket->write(NetUtils::wrapStrings({"RPas","false"}));
}

//pat <id> <name> <nationalId> <sex> <birthday> <phoneNumber> <history>
void ServerSocketThread::getPatientDataById(long id){
    auto lst=dbop->queryPatientById(id);
    foreach(auto result,lst)
        socket->write(NetUtils::wrapStrings({"pat",
            std::to_string(result.id),result.name.toStdString(),result.nationId.toStdString(),
            std::to_string(result.gender),result.birthday.toStdString(),
            result.phoneNumber.toStdString(),result.history.toStdString()
        }));
}
void ServerSocketThread::getPatientDataByNationalId(QString name){
    auto lst=dbop->queryPatientByNationId(name);
    foreach(NetUtils::PatientData result,lst)
        socket->write(NetUtils::wrapStrings({"pat",
            std::to_string(result.id),result.name.toStdString(),result.nationId.toStdString(),
            std::to_string(result.gender),result.birthday.toStdString(),
            result.phoneNumber.toStdString(),result.history.toStdString()
        }));
}

//doc <id> <name> <nationalId> <sex> <birthday> <phoneNumber> <jobTitle> <organization> <section> <workingId>
void ServerSocketThread::getDoctorDataById(long id){
    auto lst=dbop->queryDoctorById(id);
    foreach(auto result,lst){
        socket->write(NetUtils::wrapStrings({"doc",
            std::to_string(result.id),result.name.toStdString(),result.nationId.toStdString(),
            std::to_string(result.gender),result.birthday.toStdString(),result.phoneNumber.toStdString(),
            result.jobTitle.toStdString(),result.organization.toStdString(),result.section.toStdString(),
            result.workingId.toStdString()
        }));
    }
}
void ServerSocketThread::getDoctorDataByNationalId(QString name){
    auto lst=dbop->queryDoctorByNationId(name);
    foreach(auto result,lst){
        socket->write(NetUtils::wrapStrings({"doc",
            std::to_string(result.id),result.name.toStdString(),result.nationId.toStdString(),
            std::to_string(result.gender),result.birthday.toStdString(),result.phoneNumber.toStdString(),
            result.jobTitle.toStdString(),result.organization.toStdString(),result.section.toStdString(),
            result.workingId.toStdString()
        }));
    }
}
void ServerSocketThread::getDoctorDatasBySection(QString section){
    auto lst=dbop->queryDoctorBySection(section);
    foreach(auto result,lst){
        socket->write(NetUtils::wrapStrings({"doc",
            std::to_string(result.id),result.name.toStdString(),result.nationId.toStdString(),
            std::to_string(result.gender),result.birthday.toStdString(),result.phoneNumber.toStdString(),
            result.jobTitle.toStdString(),result.organization.toStdString(),result.section.toStdString(),
            result.workingId.toStdString()
        }));
    }
}

//app <patid> <docid> <date> <state>
void ServerSocketThread::getAppointmentsByDoctorId(long id){
    auto lst=dbop->queryAppointmentByDoctorId(id);
    foreach(auto result,lst){
        socket->write(NetUtils::wrapStrings({"app",
            std::to_string(result.patientId),std::to_string(result.doctorId),
            result.time.toStdString(),std::to_string(result.state)}));
    }
}
void ServerSocketThread::getAppointmentsByPatientId(long id){
    auto lst=dbop->queryAppointmentByPatientId(id);
    foreach(auto result,lst){
        socket->write(NetUtils::wrapStrings({"app",
            std::to_string(result.patientId),std::to_string(result.doctorId),
            result.time.toStdString(),std::to_string(result.state)}));
    }
}

//mrc <patid> <docid> <time> <diag> <advc>
void ServerSocketThread::getMedicalRecordsByPatientId(long id){
    auto lst=dbop->queryMedicalRecordByPatientId(id);
    foreach(auto result,lst){
        socket->write(NetUtils::wrapStrings({"mrc",
            std::to_string(result.patientId),std::to_string(result.doctorId),result.date.toStdString(),
            result.diagnosis.toStdString(),result.advice.toStdString()}));
    }
}
void ServerSocketThread::getMedicalRecordsByDoctorId(long id){
    auto lst=dbop->queryMedicalRecordByDoctorId(id);
    foreach(auto result,lst){
        socket->write(NetUtils::wrapStrings({"mrc",
            std::to_string(result.patientId),std::to_string(result.doctorId),result.date.toStdString(),
            result.diagnosis.toStdString(),result.advice.toStdString()}));
    }
}

//pst <patid> <docid> <date> <medid> <cnt> <advc>
void ServerSocketThread::getPrescriptionsByPatient(long id){
    auto lst=dbop->queryPrescriptionByPatientId(id);
    foreach(auto result,lst)
    socket->write(NetUtils::wrapStrings({"pst",
        std::to_string(result.patientId),std::to_string(result.doctorId),result.date.toStdString(),
        std::to_string(result.medicineId),std::to_string(result.count),result.advice.toStdString()}));
}
void ServerSocketThread::getPrescriptionsByDoctor(long id){
    auto lst=dbop->queryPrescriptionByDoctorId(id);
    foreach(auto result,lst)
    socket->write(NetUtils::wrapStrings({"pst",
        std::to_string(result.patientId),std::to_string(result.doctorId),result.date.toStdString(),
        std::to_string(result.medicineId),std::to_string(result.count),result.advice.toStdString()}));
}

//trs <patid> <date> <height> <weight> <HR> <hBP> <lBP> <VC>
void ServerSocketThread::getTestResultsByPatient(long id){
    auto lst=dbop->queryHealthAssessmentByPatientId(id);
    foreach(auto result,lst)
    socket->write(NetUtils::wrapStrings({"trs",
        std::to_string(result.patientId),result.date.toStdString(),
        std::to_string(result.height),std::to_string(result.weight),
        std::to_string(result.heartRate),std::to_string(result.highBP),
        std::to_string(result.lowBP),std::to_string(result.vitalCapacity)}));
}

//msg <patid> <docid> <time> <dir> <text> <read>
void ServerSocketThread::getMessageAsPatient(long id){
    auto lst=dbop->queryChatRecordByPatientId(id);
    foreach(auto result,lst)
    socket->write(NetUtils::wrapStrings({"msg",
        std::to_string(result.patientId),std::to_string(result.doctorId),
        std::to_string(result.timeStamp),std::to_string(result.sendDirection),
        result.message.toStdString(),result.isRead?"true":"false"}));
}
void ServerSocketThread::getMessageAsDoctor(long id){
    auto lst=dbop->queryChatRecordByDoctorId(id);
    foreach(auto result,lst)
    socket->write(NetUtils::wrapStrings({"msg",
        std::to_string(result.patientId),std::to_string(result.doctorId),
        std::to_string(result.timeStamp),std::to_string(result.sendDirection),
        result.message.toStdString(),result.isRead?"true":"false"}));
}

//med <id> <name> <price> <cnt> <manu> <batch>
void ServerSocketThread::getMedicineById(long id){
    auto lst=dbop->queryMedicineById(id);
    foreach(auto result,lst)
    socket->write(NetUtils::wrapStrings({"med",
        std::to_string(result.medicineId),result.name.toStdString(),
        std::to_string(result.price),std::to_string(result.count),
        result.manufactuer.toStdString(),result.batch.toStdString()}));
}
void ServerSocketThread::getMedicineByName(QString name){
    auto lst=dbop->queryMedicineByName(name);
    foreach(auto result,lst)
    socket->write(NetUtils::wrapStrings({"med",
        std::to_string(result.medicineId),result.name.toStdString(),
        std::to_string(result.price),std::to_string(result.count),
        result.manufactuer.toStdString(),result.batch.toStdString()}));
}
void ServerSocketThread::setPatient(NetUtils::PatientData data){
    if(dbop->queryPatientById(data.id).length()>0){
        dbop->updatePatient(data.id,data.name,data.nationId,data.gender,data.birthday,data.phoneNumber,data.history);
    }else{
        //ODS
        dbop->insertPatient(data.name,data.nationId,data.gender,data.birthday,data.phoneNumber,data.history);
    }
}
void ServerSocketThread::setDoctor(NetUtils::DoctorData data){
    if(dbop->queryDoctorById(data.id).length()>0){
        dbop->updateDoctor(data.id,data.workingId,data.name,data.nationId,data.gender,data.birthday,data.phoneNumber,data.jobTitle,data.organization,data.section);
    }else{
        //ODS
        dbop->insertDoctor(data.workingId,data.name,data.nationId,data.gender,data.birthday,data.phoneNumber,data.jobTitle,data.organization,data.section);
    }
}
void ServerSocketThread::setAppointment(NetUtils::Appointment data){
    if(!dbop->insertAppointment(data.patientId,data.doctorId,data.time,data.state)){
        dbop->updateAppointment(data.patientId,data.doctorId,data.time,data.state);
    }
}
void ServerSocketThread::setMedicalRecord(NetUtils::MedicalRecord data){
    if(!dbop->insertMedicalRecord(data.patientId,data.doctorId,data.date,data.diagnosis,data.advice)){
        dbop->updateMedicalRecord(data.patientId,data.doctorId,data.date,data.diagnosis,data.advice);
    }
}
void ServerSocketThread::setPrescription(NetUtils::Prescription data){
    auto lst=dbop->queryMedicineById(data.medicineId);
    if(lst.length()<=0){
        qDebug("Server:No such medicine:%ld",data.medicineId);
        return;
    }
    //DS
    if(!dbop->insertPrescription(data.patientId,data.doctorId,data.date,lst.first().name,data.medicineId,data.count,data.advice)){
        dbop->updatePrescription(data.patientId,data.doctorId,data.date,data.medicineId,data.count,data.advice);
    }
}
void ServerSocketThread::setTestResult(NetUtils::TestResult data){
    if(!dbop->insertHealthAssessment(data.patientId,data.date,data.height,data.weight,
        data.heartRate,data.highBP,data.lowBP,data.vitalCapacity)){
        dbop->updateHealthAssessment(data.patientId,data.date,data.height,data.weight,
                data.heartRate,data.highBP,data.lowBP,data.vitalCapacity);
    }
}
void ServerSocketThread::setMessage(NetUtils::Message data){
    if(!dbop->insertChatRecord(data.patientId,data.doctorId,QString::number(data.timeStamp),data.sendDirection,data.message,data.isRead)){
        //ODS
        dbop->updateChatRecord(data.patientId,data.doctorId,QString::number(data.timeStamp),data.message,data.isRead);
    }
}
void ServerSocketThread::setMedicine(NetUtils::Medicine data){
    if(dbop->queryMedicineById(data.medicineId).length()>0){
        dbop->updateMedicine(data.medicineId,data.name,data.price,data.count,data.manufactuer,data.batch);
    }else{
        dbop->insertMedicine(data.name,data.price,data.count,data.manufactuer,data.batch);
    }
}

<<<<<<< Updated upstream
//v <bool>
void ServerSocketThread::verifyMedicineWithId(long id){
    bool result=dbop->queryMedicineById(id).length()>0;
    socket->write(NetUtils::wrapStrings({"v",result?"true":"false"}));
}
void ServerSocketThread::verifymedicineWithName(QString name){
    bool result=dbop->queryMedicineByName(name).length()>0;
    socket->write(NetUtils::wrapStrings({"v",result?"true":"false"}));
}
=======

>>>>>>> Stashed changes
