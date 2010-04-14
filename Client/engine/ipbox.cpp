#include "ipbox.h"

using std::string;

IpBox::IpBox(QWidget *parent, string alias, string addr, string prt)
: QDialog(parent), ui(new Ui_IpBox), ip(QString(addr.c_str())), port(QString(prt.c_str())), name(QString(alias.c_str()))
{
    ui->setupUi(this);

    ui->nameentry->setText(name);
    ui->ipentry->setText(ip);
    ui->portentry->setText(port);
    ui->ipentry->setFocus();
}

bool isValidIp(string str)
{
	int dots = 0;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (isdigit(str[i]))
			continue;
		if (str[i] != '.' || ++dots > 3)
			return false;
	}
	if (dots != 3 || str[0] == '.' || str[str.size() - 1] == '.')
		return false;
	return true;
}

bool isValidPort(string str)
{
	for (size_t i = 0; i < str.size(); i++)
		if (!isdigit(str[i]))
			return false;
	return (str.size() > 3);
}

void IpBox::on_okbutton_clicked()
{
	if (isValidIp(ui->ipentry->text().toStdString()))
		ip = ui->ipentry->text();
	else
	{
		QMessageBox::warning(this, "Error", "Invalid IP address", 1, 0, 0);
		return;
	}


	if (isValidPort(ui->portentry->text().toStdString()))
		port = ui->portentry->text();
	else
	{
		QMessageBox::warning(this, "Error", "Invalid port number", 1, 0, 0);
		return;
	}

	if (!ui->nameentry->text().contains("\"", Qt::CaseInsensitive) && !ui->nameentry->text().contains("\'", Qt::CaseInsensitive))
		name = ui->nameentry->text();
	else
	{
		QMessageBox::warning(this, "Error", "Invalid Characters", 1, 0, 0);
		return;
	}

	this->accept();
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
