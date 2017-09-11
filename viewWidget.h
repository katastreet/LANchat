#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <QWidget>

class QLabel;
class QPushButton;
class QLineEdit;
class QVBoxLayout;
class QScrollArea;

class viewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit viewWidget(QWidget *parent = 0);

signals:
    void newMessageToBeSent(const QString &text);

public slots:
    void findSendClicked();
    void enableSendButton(const QString &text);
    void otherMessageRecieved(const QString &text);


private:
QPushButton *send;
QLineEdit *msg;
QVBoxLayout *messageLayout;
QScrollArea *messages;
};

#endif // VIEWWIDGET_H
