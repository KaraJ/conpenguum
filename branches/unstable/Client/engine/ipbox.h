#ifndef IPBOX_H
#define IPBOX_H
#include "../ui_ipbox.h"

#include <QDialog>
#include <QString>

class IpBox : public QDialog
{
    Q_OBJECT

public:
    IpBox(QWidget *parent = 0);
    QString ip, port, name;

private:
    Ui_IpBox *ui;

private slots:
    void on_okbutton_clicked();
};

#endif // IPBOX_H
