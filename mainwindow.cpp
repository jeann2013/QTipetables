#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QProcess>
#include <QDesktopWidget>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBoxFilter->addItem("INPUT");
    ui->comboBoxFilter->addItem("OUTPUT");
    ui->comboBoxFilter->addItem("FORWARD");
    ui->comboBoxMangle->addItem("DROP");
    ui->comboBoxMangle->addItem("ACCEPT");
    ui->comboBoxMangle->addItem("REJECT");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonApply_clicked()
{
    QProcess process;

    QMessageBox::StandardButton reply;
    QString Port = ui->textPort->toPlainText();
    QString Action = ui->comboBoxFilter->currentText();

    QString ActionApply = "iptables -A " + Action + " -p tcp --destination-port "+ Port + " -j DROP";

    reply = QMessageBox::question(this,"You will wan apply this Command to IpTables? :", ActionApply ,QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QProcess::execute(ActionApply);
        QMessageBox::about(this,"Successfully!","Rule was Apply Successfuly!");
        qDebug() << ActionApply;
      } else {
        qDebug() << "Yes was *not* clicked";
      }

}

void MainWindow::on_pushButtonClose_clicked()
{
    this->close();
}
