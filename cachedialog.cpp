#include "cachedialog.h"
#include "ui_cachedialog.h"

int cval1;


int cacheDialog::cbuffermode() {
   return ui->buffermode->currentIndex();
}

QString cacheDialog::cbufferfactor() {
   return ui->bufferfactor->text();
}

QString cacheDialog::cbuffersize() {
   return ui->buffersize->text();
}


void cacheDialog::setcbuffersize(const QString &cbuffersize)
{
    ui->buffersize->setText(cbuffersize);
}

void cacheDialog::setcbuffermode(const int &cbuffermode)
{

    ui->buffermode->setCurrentIndex(cbuffermode);
}

void cacheDialog::setcbufferfactor(const QString &cbufferfactor)
{
    ui->bufferfactor->setText(cbufferfactor);
}


int cacheDialog::returncval1() {
   return cval1;
}


cacheDialog::cacheDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cacheDialog)
{
    ui->setupUi(this);
}

cacheDialog::~cacheDialog()
{
    delete ui;
}


void cacheDialog::on_cpreset1_clicked()
{

    setcbuffermode(1);
    setcbuffersize("0");
    setcbufferfactor("10");

}

void cacheDialog::on_cpreset2_clicked()
{
    setcbuffermode(2);
    setcbuffersize("104857600");
    setcbufferfactor("1");
}

void cacheDialog::on_cpreset3_clicked()
{
    setcbuffermode(2);
    setcbuffersize("52428800");
    setcbufferfactor("1");

}


////////////////////////////////////

void cacheDialog::on_writecxml_clicked()
{
   cval1 = 2;
   QDialog::accept();
}

void cacheDialog::on_resetcxml_clicked()
{
     ui->buffersize->setText("20971520");
     ui->buffermode->setCurrentIndex(2);
     ui->bufferfactor->setText("1");

     ui->cpreset1->setAutoExclusive(false);
     ui->cpreset2->setAutoExclusive(false);
     ui->cpreset3->setAutoExclusive(false);

     ui->cpreset1->setChecked(false);
     ui->cpreset2->setChecked(false);
     ui->cpreset3->setChecked(false);

     ui->cpreset1->setAutoExclusive(true);
     ui->cpreset2->setAutoExclusive(true);
     ui->cpreset3->setAutoExclusive(true);

}

