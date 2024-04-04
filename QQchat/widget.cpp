#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDataStream>
#include <QDateTime>
#include <QColorDialog>
#include <QFileDialog>

Widget::Widget(QString name, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_name = name;

    this->setWindowTitle(m_name);

    this->port = 8989;
    this->udpSocket = new QUdpSocket(this);

    udpSocket->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);

    connect(udpSocket,&QUdpSocket::readyRead,this,&Widget::ReceiveMessage);

}

void Widget::sendMsg()
{
    QByteArray array;
    QDataStream stream(&array,QIODevice::WriteOnly);

    stream<<this->getName();

    if(this->ui->msgEdit->toPlainText()=="")
    {
        QMessageBox::warning(this,"警告","发送内容不能为空");
        return;
    }
    stream<<this->getMsg();
    udpSocket->writeDatagram(array.data(),array.size(),QHostAddress::Broadcast,this->port);

}

QString Widget::getName()
{
    return m_name;
}

QString Widget::getMsg()
{
    QString msg = ui->msgEdit->toHtml();
    ui->msgEdit->clear();
    ui->msgEdit->setFocus();
    return msg;
}


void Widget::ReceiveMessage()
{
    qint64 size = udpSocket->pendingDatagramSize();
    int mysize = static_cast<int>(size);
    QByteArray array = QByteArray(mysize,0);
    udpSocket->readDatagram(array.data(),size);
    QDataStream stream(&array,QIODevice::ReadOnly);

    QString name,msg;
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    stream>>name>>msg;
    ui->msgBrowser->setTextColor(Qt::blue);
    ui->msgBrowser->setCurrentFont(QFont("Times New Roman",10));
    ui->msgBrowser->append("["+name+"]"+time);
    ui->msgBrowser->append(msg);
}


Widget::~Widget()
{
    delete ui;
}

void Widget::closeEvent(QCloseEvent *event)
{
    emit closeWidget();

    udpSocket->close();
    udpSocket->destroyed();

}


void Widget::on_sendmsg_clicked()
{
    sendMsg();
}

void Widget::on_exit_clicked()
{
    this->close();
}

void Widget::on_fontComboBox_currentFontChanged(const QFont &f)
{
    ui->msgEdit->setFontFamily(f.toString());
    ui->msgEdit->setFocus();
}

void Widget::on_fontSize_currentIndexChanged(const QString &arg1)
{
    ui->msgEdit->setFontPointSize(arg1.toDouble());
    ui->msgEdit->setFocus();
}

void Widget::on_bold_clicked(bool checked)
{
    if (checked)
    {
        ui->msgEdit->setFontWeight(QFont::Bold);
    }
    else
    {
        ui->msgEdit->setFontWeight(QFont::Normal);
    }
}

void Widget::on_italic_clicked(bool checked)
{
    ui->msgEdit->setFontItalic(checked);
    ui->msgEdit->setFocus();
}

void Widget::on_unserline_clicked(bool checked)
{
    ui->msgEdit->setFontUnderline(checked);
    ui->msgEdit->setFocus();
}

void Widget::on_clean_clicked()
{
    ui->msgEdit->clear();
}

void Widget::on_color_clicked()
{
    QColor color = QColorDialog::getColor(color,this);
    ui->msgEdit->setTextColor(color);
}

void Widget::on_save_clicked()
{
    if(ui->msgBrowser->document()->isEmpty())
    {
        QMessageBox::warning(this,"提示","聊天记录为空，保存失败！");
        return;
    }
    else
    {
        QString filename = QFileDialog::getSaveFileName(this,"保存聊天记录","聊天记录","(*.txt)");
        if(!filename.isEmpty())
        {
            QFile file(filename);
            file.open(QIODevice::WriteOnly | QFile::Text);
            QTextStream stream(&file);
            stream<<ui->msgBrowser->toPlainText();
            file.close();
        }
    }
}
