#include "seriallog.h"
#include "./ui_seriallog.h"

serialLog::serialLog(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::serialLog)
{
    ui->setupUi(this);
}

serialLog::~serialLog()
{
    delete ui;
}

