#ifndef IPBOX_H
#define IPBOX_H
#include "../ui_ipbox.h"
#include <QDialog>
#include <QString>
using namespace std;

class IpBox : public QDialog
{
    Q_OBJECT

public:
    IpBox(QWidget *parent = 0, string alias = 0, string addr = 0, string prt = 0);
    string getName();
    string getIp();
    string getPort();

private:
    Ui_IpBox *ui;
    QString ip, port, name;

private slots:
    void on_okbutton_clicked();
};

#endif // IPBOX_H
