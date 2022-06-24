#include "log.h"
#include "ui_log.h"
#include <string>
#include <sstream>

template <typename T>
std::string toString(T val) {
    std::ostringstream oss;
    oss << val;
    return oss.str();
}

LOG::LOG(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::LOG) {
    connect(&serialPort, &QSerialPort::readyRead, this, &LOG::handleReadyRead);
    ui->setupUi(this);

    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        ui->cmbPort->addItem(serialPortInfo.portName());
    }
}

LOG::~LOG() {
    if(file.isOpen()) {
        file.flush();
        file.close();
    }
    delete ui;
}

void LOG::handleReadyRead() {

    static QByteArray bytes;
    QByteArray in_data;
    QByteArray temp_data;
    QString temp_string;


    in_data.append(serialPort.readAll());

    if (in_data.indexOf("\n") != -1) {

    bytes += in_data;
    auto n = bytes.indexOf('\n');
    temp_data = bytes.split('\n').at(0);

    if (!crc8(temp_data.constData(), 6)) {
        temp_string = prepareToWrite(temp_data.constData(),n);
        ui->txtOutput->append(temp_string);
        unsigned int result = ((uint16_t)temp_data.constData()[2] & 0xFF) + ((uint16_t)temp_data.constData()[3] & 0xFF) * 256;
        stream << QString::fromStdString(toString(result)) <<' ' << QString::fromStdString(toString((uint16_t)temp_data.constData()[4] & 0xFF)) << '\n';

    }

    bytes.remove(0,n+1);

    } else {
    bytes += in_data;
    }
}

QString LOG::prepareToWrite(const char * arr, int size) {

    QString result;
    result.clear();

    for (int i = 0; i < size; ++i) {
        result += QString::fromStdString(toString((uint16_t)arr[i] & 0xFF));
        result += ' ';
    }

    return result;
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

    if (file.isOpen()) {
        file.flush();
        file.close();
    }
    if (ui->lineEdit->text().endsWith(".txt")) {
        file.setFileName(ui->lineEdit->text());
    } else {
        file.setFileName(ui->lineEdit->text() + ".txt");
    }
    if (file.exists()) {
        QMessageBox::warning(this,"Предупреждение","Файл существует! Он будет открыт для добавления данных.");
    }
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
    }

    stream.setDevice(&file);
    stream << '\n' << "Эксперимент №__, SigmaMilliMeter = " << '\n';
    file.flush();

}

uint8_t crc8(const char * buffer, uint8_t size) {
    uint8_t crc, i;
    crc = 0xFF;
    while (size--) {
        crc ^= *buffer++;
        for (i = 0; i < 8; i++) {
            if (crc & 0x80) crc = (crc << 1) ^ 0x31;
            else crc <<= 1;
        }
    }

    return crc;
}


void LOG::on_btnDisconnect_clicked()
{
    serialPort.close();
    return;
}


void LOG::on_btnUpdate_clicked()
{
    ui->cmbPort->clear();
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        ui->cmbPort->addItem(serialPortInfo.portName());
    }
}


void LOG::on_pushButton_clicked()
{
    ui->txtOutput->clear();
    stream << '\n' << "Эксперимент №__, SigmaMilliMeter = " << '\n';
    file.flush();
}

