#ifndef QWENCLIENT_H
#define QWENCLIENT_H

#include <QNetworkReply>
#include <QNetworkAccessManager>

class QwenClient : public QObject
{
    Q_OBJECT
public:
    void setAPI_KEY(char * key);
    static QwenClient& getInstance();
    void ask(QString question);
private:
    QwenClient();
    ~QwenClient();
    QwenClient(const QwenClient&) = delete;
    const QwenClient &operator=(const QwenClient&) = delete;

    QNetworkAccessManager* manager;
    QByteArray API_KEY;
private slots:
    void networkReply(QNetworkReply*);
signals:
    void aiReply(QString);
};

#endif // QWENCLIENT_H
