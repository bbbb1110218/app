#include "widget.h"
#include "./ui_widget.h"
#include <QString>
#include <QDebug>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <QProcess>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>



/*static char  curlFormat[1024]*/
#if 1
QString Urlformat="curl -H 'Content-Type: application/json' -d "
                          "'{\"contents\":[{\"parts\":[{\"text\":\"%1\"}]}]}' -X POST "
                          "\"https://generativelanguage.googleapis.com/v1beta/models/"
                          "gemini-pro:generateContent?key=%2\"";
#else 
    QString Urlformat = "curl -H \"Content-Type: application/json\" -d "
                    "\"{\\\"contents\\\":[{\\\"parts\\\":[{\\\"text\\\":\\\"%1\\\"}]}]}\" -X POST "
                    "\"https://generativelanguage.googleapis.com/v1beta/models/"
                    "gemini-pro:generateContent?key=%2\"";
#endif

QString GwaitString=QString::fromStdString("等待回复中...");

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_process.setProgram("curl");
    say_process.setProgram("/usr/bin/say");
    connect(&m_process, SIGNAL(readyReadStandardOutput()),
            this, SLOT(onStandardOutputReady()));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnAsk_clicked()
{
#if 0
    QString inputText=ui->textInput->toPlainText();
    qDebug() << "String : " <<inputText <<"\n"
             << "String len:" << inputText.length()
             << "\n";

    ui->testOutput->clear();
    char tmp[1024];



    QString queryStr=Urlformat.arg(inputText.toUtf8().data()).arg("AIzaSyByHIKCZnGzRPEERXtxT5OckyUHZZK2z0U");

    QByteArray ba = queryStr.toUtf8();

    qDebug() << "QueryStr = \n" <<
        queryStr <<
        "\n";
    qDebug() << "Utf_8 =" << ba.data()
             <<"\n";

//    std::system(ba.data());
//    QProcess process;

    m_process.startCommand(ba);

//    QByteArray stdoutData = process.readAllStandardOutput();

//    QString output = QString::fromLatin1(ba);


//    ui->testOutput->clear();
//    ui->testOutput->appendPlainText(output);

//    ui->testOutput->appendPlainText(queryStr);

#else
//    if()
    //TODO :: 添加语言是否中断
    if(say_process.state() == QProcess::Running){
        say_process.kill();
        return;
    }

    QString inputText = ui->textInput->toPlainText();
    qDebug() << "String : " << inputText << "\n"
             << "String len:" << inputText.length() << "\n";

    ui->testOutput->clear();

    QString json = QString("{\"contents\":[{\"parts\":[{\"text\":\"%1\"}]}]}").arg(inputText);
    QString key = "AIzaSyByHIKCZnGzRPEERXtxT5OckyUHZZK2z0U";
    QString url = "https://generativelanguage.googleapis.com/v1beta/models/gemini-pro:generateContent?key=" + key;

    QStringList arguments;
    arguments << "-H" << "Content-Type: application/json" << "-d" << json << "-X" << "POST" << url;

    m_process.setProgram("curl");
    m_process.setArguments(arguments);
    m_process.start();
    ui->testOutput->clear();
    ui->testOutput->appendPlainText(GwaitString);
#endif 


}


void Widget::onStandardOutputReady(){
//    QByteArray ba = m_process.readAllStandardOutput();
    QByteArray ba = m_process.readAllStandardOutput();
    QJsonDocument doc = QJsonDocument::fromJson(ba);

    ui->testOutput->clear();
    if (doc.isObject()) {
        QJsonObject obj = doc.object();
        QJsonArray candidates = obj["candidates"].toArray();
        if (!candidates.isEmpty()) {
            QJsonObject firstCandidate = candidates[0].toObject();
            QJsonObject content = firstCandidate["content"].toObject();
            QJsonArray parts = content["parts"].toArray();
            if (!parts.isEmpty()) {
                QJsonObject firstPart = parts[0].toObject();
                QString text = firstPart["text"].toString();

                ui->testOutput->appendPlainText(text);
            }
        }
    }


}

void Widget::on_btnSay_clicked()
{
    if(say_process.state() == QProcess::Running){
        say_process.kill();
        return;
    }
    QString sayString=ui->testOutput->toPlainText();
    if(!sayString.isEmpty() && sayString !="no data" && sayString != GwaitString ){
        QStringList argument;
        argument << sayString;
        say_process.setArguments(argument);
        say_process.start();

    }




}

