#ifndef IPBOX_H
#define IPBOX_H
#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../ui_ipbox.h"

class IpBox : public QDialog
{
    Q_OBJECT

public:
    IpBox(QWidget *parent = 0, std::string alias = 0, std::string addr = 0, std::string prt = 0, std::string ship = "jvship");
    std::string getName();
    std::string getIp();
    std::string getPort();

private:
    Ui_IpBox *ui;
    QString ip, port, name;

private slots:
    void on_okbutton_clicked();
};

#endif // IPBOX_H
