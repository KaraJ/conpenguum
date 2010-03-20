#include "ipbox.h"

IpBox::IpBox(QWidget *parent) : QDialog(parent), ui(new Ui_IpBox)
{
    ui->setupUi(this);
}

void IpBox::on_okbutton_clicked()
{
	ip = ui->ipentry->text().trimmed();
	name = ui->nameentry->text().trimmed();
	port = ui->portentry->text().trimmed();

	this->hide();
}
