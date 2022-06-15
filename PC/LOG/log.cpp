#include "log.h"
#include "ui_log.h"

LOG::LOG(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::LOG)
{
    connect(&serialPort, &QSerialPort::readyRead, this, &LOG::handleReadyRead);
    ui->setupUi(this);

    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        ui->cmbPort->addItem(serialPortInfo.portName());
    }
}

LOG::~LOG() {
    delete ui;
}

void LOG::handleReadyRead() {
    QByteArray data;
    data.append(serialPort.readAll());
    ui->txtOutput->append(data);
}



void LOG::on_btnConnect_clicked() {

    serialPort.setPortName(this->ui->cmbPort->currentText());
    serialPort.setBaudRate(QSerialPort::Baud9600);

    if (!serialPort.open(QIODevice::ReadWrite)) {
            QMessageBox::warning(this, "Ошибка", "Не удалось подключится к порту");
            return;
    }

}


void LOG::on_fileBtn_clicked() {
    return;
}

