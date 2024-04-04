#include "login.h"
#include "ui_login.h"
#include <QIcon>
#include <QToolButton>
#include <QVector>
#include "widget.h"
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/images/qq.jpg"));
    this->setWindowTitle("QQ");
    QStringList namelist;
    namelist << "王大拿"<<"王天来"<<"刘能"<<"谢永强"<<"谢广坤"<<"刘玉田";
    QVector<QToolButton*> vector;
    for (int i = 0;i < 6;++i) {
        QToolButton *btn = new QToolButton(this);

        btn->setIcon(QPixmap(QString(":/images/touxiang%1.jpg").arg(i+1)));
        btn->setIconSize(QSize(100,100));
        btn->setAutoRaise(true);

        btn->setText(QString("%1").arg(namelist[i]));

        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        ui->verticalLayout->addWidget(btn);
        vector.push_back(btn);
        Isshow.push_back(false);
    }
    for (int i = 0;i < 6; ++i) {
        connect(vector[i], &QToolButton::clicked,this,[=](){
            if(Isshow[i]){
                QMessageBox::warning(this,"警告","该聊天已被打开");
                return;
            }
            Isshow[i] = true;
            Widget *widget = new Widget(vector[i]->text(), nullptr);
            widget->setWindowIcon(QPixmap(QString(":/images/touxiang%1.jpg").arg(i+1)));
            widget->show();

            connect(widget,&Widget::closeWidget,this , [=](){
                Isshow[i] = false;
            });

        });
    }

}

Login::~Login()
{
    delete ui;
}
