#ifndef NETUTILS_H
#define NETUTILS_H

#include <initializer_list>
#include <QString>
#include <string>

namespace NetUtils {
    extern const QString messagePrefix;
    extern const QString messageSuffix;
    extern const QString messagePartition;
    extern const long waitTime;

    const QByteArray wrapMessage(const QString& message);
    const QString combineStrings(const std::initializer_list<std::string>& args);
    const QByteArray wrapStrings(const std::initializer_list<std::string>& args);

    struct PatientData{
        long id;
        QString name;
        QString nationId;
        int sex;
        QString birthday;
        QString phoneNumber;
        QString history;
    };

    struct DoctorData{
        long id;
        QString name;
        QString nationId;
        int sex;
        QString birthday;
        QString phoneNumber;
        QString jobTitle;
        QString organization;
        QString section;
    };

    struct Appointment{
        long patientId;
        long doctorId;
        QString time;
        int state;
    };

    struct MedicalRecord{
        long patientId;
        long doctorId;
        QString date;
        QString diagnosis;
        QString advice;
    };

    struct Prescription{
        long patientId;
        long doctorId;
        QString date;
        long medicineId;
        int count;
        QString advice;
    };

    struct TestResult{
        long patientId;
        QString date;
        float height;
        float weight;
        int heartRate;
        float highBP;
        float lowBP;
        int vitalCapacity;
    };

    struct Message{
        long patientId;
        long doctorId;
        long long timeStamp;
        int sendDirection;
        QString message;
        bool isRead;
    };

    struct Medicine{
        long medicineId;
        QString name;
        float price;
        long count;
        QString manufactuer;
        QString batch;
    };
}

#endif
