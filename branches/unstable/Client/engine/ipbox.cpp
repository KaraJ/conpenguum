#include "ipbox.h"
using namespace std;

IpBox::IpBox(QWidget *parent, string alias, string addr, string prt)
: QDialog(parent), ui(new Ui_IpBox), ip(QString(addr.c_str())), port(QString(prt.c_str())), name(QString(alias.c_str()))
{
    ui->setupUi(this);

    ui->nameentry->setText(name);
    ui->ipentry->setText(ip);
    ui->portentry->setText(port);
    ui->ipentry->setFocus();
}

void IpBox::on_okbutton_clicked()
{
	ip = ui->ipentry->text();
	name = ui->nameentry->text();
	port = ui->portentry->text();

	this->hide();
}

string IpBox::getName()
{
	return name.toStdString();
}

string IpBox::getIp()
{
	return ip.toStdString();
}

string IpBox::getPort()
{
	return port.toStdString();
}
