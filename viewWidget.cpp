
#include "viewWidget.h"
#include<QtGui>
#include<QtWidgets>
#include"network.h"

viewWidget::viewWidget(QWidget *parent) : QWidget(parent)
{
QLabel *messageDisplay = new QLabel(tr("your messages:"));
send = new QPushButton(tr("send"));
send->setEnabled(false);
msg = new QLineEdit();
connect(send, SIGNAL(clicked()),this, SLOT(findSendClicked()));
connect(send,SIGNAL(clicked()),msg,SLOT(clear()));
connect(msg,SIGNAL(returnPressed()),send, SLOT(click()));
connect(msg,SIGNAL(textChanged(const QString &)),this,SLOT(enableSendButton(const QString &)));

messageLayout = new QVBoxLayout;
messageLayout->addWidget(messageDisplay,1);
messageDisplay->setMinimumWidth(300);

QWidget *messageWidget = new QWidget;
messageWidget->setLayout(messageLayout);
//messageLayout->addStretch();

messages = new QScrollArea;
messages->setWidget(messageWidget);

QHBoxLayout *bottomLayout = new QHBoxLayout;
bottomLayout->addWidget(msg);
bottomLayout->addWidget(send);

QVBoxLayout *mainLayout = new QVBoxLayout;
mainLayout->addWidget(messages);
mainLayout->addLayout(bottomLayout);
setLayout(mainLayout);
setMinimumHeight(400);
setMinimumWidth(400);
}

void viewWidget::findSendClicked()//i have sent the message
{
   QString text = msg->text();
   emit newMessageToBeSent(text);
   QLabel *msn = new QLabel(text);
   //if
   msn->setAlignment(Qt::AlignLeft);
   messageLayout->addWidget(msn);
   messageLayout->setSizeConstraint(QLayout::SetFixedSize);//adjust the layout for new message
   messages->verticalScrollBar()->setSliderPosition(messages->verticalScrollBar()->maximum());

}

void viewWidget::enableSendButton(const QString &text)
{
    send->setEnabled(!text.isEmpty());
}

void viewWidget::otherMessageRecieved(const QString &text)
{
    QLabel *msn = new QLabel(text);
    //if
    msn->setAlignment(Qt::AlignRight);
    messageLayout->addWidget(msn);
    messageLayout->setSizeConstraint(QLayout::SetFixedSize);//adjust the layout for new message
    messages->verticalScrollBar()->setSliderPosition(messages->verticalScrollBar()->maximum());
}
