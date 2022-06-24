#ifndef LOG_H
#define LOG_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class LOG; }
QT_END_NAMESPACE

class LOG : public QMainWindow {
    Q_OBJECT

public:
    LOG(QWidget *parent = nullptr);
    ~LOG();



private slots:

    void handleReadyRead();

    void on_btnConnect_clicked();

    void on_fileBtn_clicked();

    void on_btnDisconnect_clicked();

    void on_btnUpdate_clicked();

private:
    Ui::LOG *ui;
    QSerialPort serialPort;
    QString prepareToWrite(const char * arr, int size);
    QFile file;
    QTextStream stream;
};

uint8_t crc8(const char * buffer, uint8_t size);

#endif // LOG_H
