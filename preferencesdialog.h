#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>

namespace Ui {
class preferencesDialog;
}

class preferencesDialog : public QDialog
{
    Q_OBJECT


public:
    explicit preferencesDialog(QWidget *parent = 0 );

      void setPackagename(const QString &packagename);
      void setPulldir(const QString &pulldir);


      void setversioncheck(const bool &versioncheck);
      void setisusb(const bool &isusb);

      void setversionLabel(const QString &versiontext);
      void setdevicename(const QString &device_name);

      void setdaddr(const QString &daddr);
      void setdescription(const QString &description);
      void setfilepath(const QString &filepath);
      void setdataroot(const QString &data_root);
      void setdeviceindex(const int &deviceindex);
      void setport(const QString &port);
      void setadb_pref(const QString &adb_pref);

      void setrecnum(const QString &recnum);

    ~preferencesDialog();

public:
   QString xbmcpackageName();

   QString pulldir();
   QString daddr();
   QString description();
   QString filepath();
   QString data_root();
   QString port();


   bool versioncheck();  
   bool isusb();

int returnval1();

private slots:
   void on_pfolderButton_clicked();

   void on_getUpdate_clicked();


   void onRequestCompleted();


   void on_pushButton_clicked();


   void on_kodiButton_clicked();

   void on_spmcButton_clicked();

   void on_otherButton_clicked();

   void on_tvmcButton_clicked();

   void on_isusb_clicked(bool checked);



   void on_listkodirootBox_clicked();

private:
    Ui::preferencesDialog *ui;



};

#endif // PREFERENCESDIALOG_H
