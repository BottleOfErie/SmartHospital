#include "h/DoctorPatientCommunicationUserListWidget.h"

DoctorPatientCommunicationUserListWidget::DoctorPatientCommunicationUserListWidget(NetUtils::DoctorData doctor)
    : QLabel(doctor.name)
{
    type=_doctor;
    name=doctor.name;
    id=doctor.id;
}

DoctorPatientCommunicationUserListWidget::DoctorPatientCommunicationUserListWidget(NetUtils::PatientData patient)
    : QLabel(patient.name)
{
    type=_doctor;
    name=patient.name;
    id=patient.id;
}
