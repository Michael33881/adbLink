#include "firestarterdialog.h"
#include "ui_firestarterdialog.h"
#include <QDesktopServices>
#include <QUrl>


int fval1 = 0;


int firestarterDialog::firestarter() {
   return fval1;
}

firestarterDialog::firestarterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::firestarterDialog)
{
    ui->setupUi(this);

    QPixmap pix(":/assets/donate.png");
    QIcon icon(pix);
    ui->donate->setIcon(icon);
    ui->donate->setIconSize(pix.size());

}

firestarterDialog::~firestarterDialog()
{
    delete ui;
}

void firestarterDialog::on_donate_clicked()
{
 QString link = "https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=KKQ6VU34YGKYS";
 QDesktopServices::openUrl(QUrl(link));
}

void firestarterDialog::on_pushButton1_clicked()
{
fval1 = 1;
}
