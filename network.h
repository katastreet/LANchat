#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include<string>
class tcpClient;
class QString;

using std::string;

class network : public QObject
{
    Q_OBJECT
public:
    explicit network(QString host="\0",QString p="\0",QObject *parent = 0);
    void startReceivingMessage();

signals:
void newMessageRecieved(const QString& text);

public slots:
void messageSendingProcedure(const QString& text);



private:
QString hostname;
QString port;
void messageRecievingProcedure();

tcpClient *n;
};

#endif // NETWORK_H
