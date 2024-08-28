#ifndef DOCTORPATIENTCOMMUNICATIONUSERLISTWIDGET_H
#define DOCTORPATIENTCOMMUNICATIONUSERLISTWIDGET_H

#include <QLabel>
#include "net/NetUtils.h"

class DoctorPatientCommunicationUserListWidget:public QLabel{
    Q_OBJECT
public:
    enum usertype{_patient,_doctor};
    DoctorPatientCommunicationUserListWidget(NetUtils::DoctorData doctor);
    DoctorPatientCommunicationUserListWidget(NetUtils::PatientData patient);

    usertype type;
    QString name;
    long id;

};

#endif // DOCTORPATIENTCOMMUNICATIONUSERLISTWIDGET_H
