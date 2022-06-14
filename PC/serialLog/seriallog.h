#ifndef SERIALLOG_H
#define SERIALLOG_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class serialLog; }
QT_END_NAMESPACE

class serialLog : public QMainWindow
{
    Q_OBJECT

public:
    serialLog(QWidget *parent = nullptr);
    ~serialLog();

private:
    Ui::serialLog *ui;
};
#endif // SERIALLOG_H
