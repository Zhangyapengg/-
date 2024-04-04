#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QString name, QWidget *parent);

    void sendMsg(); //广播UDP信息
    QString getName();  //获取名字
    QString getMsg();   //获取聊天信息
    void userEnter(QString username);   //处理用户进入
    void userLeft(QString username, QString time);  //接受UDP信息
    void ReceiveMessage();


    ~Widget();

    void closeEvent(QCloseEvent *event);
signals:

    void closeWidget();

private slots:
    void on_sendmsg_clicked();

    void on_exit_clicked();

    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_fontSize_currentIndexChanged(const QString &arg1);

    void on_bold_clicked(bool checked);

    void on_italic_clicked(bool checked);

    void on_unserline_clicked(bool checked);

    void on_clean_clicked();

    void on_color_clicked();

    void on_save_clicked();

private:
    Ui::Widget *ui;
    QString m_name;

    quint16 port;
    QString uName;
    QUdpSocket *udpSocket;

};
#endif // WIDGET_H
