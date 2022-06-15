#ifndef LOG_H
#define LOG_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class LOG; }
QT_END_NAMESPACE

class LOG : public QMainWindow
{
    Q_OBJECT

public:
    LOG(QWidget *parent = nullptr);
    ~LOG();



private slots:

    void handleReadyRead();

    void on_btnConnect_clicked();

    void on_fileBtn_clicked();

private:
    Ui::LOG *ui;
    QSerialPort serialPort;
};
#endif // LOG_H
