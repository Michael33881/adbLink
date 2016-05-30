#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog2.h"
#include "helpdialog.h"
#include "uninstalldialog.h"
#include "keyboarddialog.h"
#include "llamadialog.h"
#include "firestarterdialog.h"
#include "usbfiledialog.h"
#include "uuiddialog.h"
#include "kodidialog.h"
#include "cachedialog.h"
#include "creditsdialog.h"
#include "cifsdialog.h"
#include "unbootdialog.h"
#include "datadialog.h"
#include "unlockdialog.h"
#include "backupdialog.h"
#include "bootmenudialog.h"
#include "mediacenterdialog.h"
#include "restdialog.h"
#include "filedownloader.h"
#include <QMessageBox>
#include <QTableWidget>
#include <QResource>
#include <QProcess>
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QProgressBar>
#include <QTimer>
#include <QLabel>
#include <QInputDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <preferencesdialog.h>
#include <QElapsedTimer>
#include <QTextStream>
#include <QDate>
#include <QRegularExpression>
#include <QStringList>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDesktopServices>
#include <QUrl>
#include <QPixmap>
#include <QIcon>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtNetwork>
#include <QtNetwork/QNetworkInterface>
#include <adblogdialog.h>
#include <QFileInfo>
#include <QThread>

// #include <QDebug>

#ifdef Q_OS_LINUX
 int os=0;
#elif defined(Q_OS_WIN)
  int os=1;
#elif defined(Q_OS_MAC)
int os=2;
#endif


// QString num="123";
//  int n = num.toInt();

/*

ro.product.model=AFTM
stick


ro.product.model=AFTB
tv

 */


const QString vqurl = "http://www.jocala.com/version.txt";
const QString version = "2.04";

bool isConnected = false;
bool serverRunning = false;
bool is_packageInstalled = false;
bool mounted_op = false;
bool firstrun=true;
bool dbexists = false;
bool updatecheck = true;
bool versioncheck = true;
bool sshcheck = false;
bool mountcheck = false;
bool killadbBool = true;
bool resetadbBool = true;
bool usbdev;
bool    select1;
bool    select2;
bool isusb = false;
bool    select3;
bool    select4;
bool    os5;
bool    amazon;
bool    nvidia;

QString port = "5555";
QString filename = "";
QString adbdir =  "";
QString adb = "";
QString fastboot = "";
QString xmldir = "";
QString splashdir = "";
QString recoverydir = "";
QString stkrecoverydir = "";
QString hdir = "";
QString daddr="";
QString sldir = "";
QString pushdir = "";
QString pulldir = "";
QString xbmcpackage ="";
QString data_root = "";
QString buffersize = "";
QString bufferfactor = "";
QString dbstring = "";
QString description = "";
QString filepath = "";
QString busypath = "";
QString ipaddress1;
QString share1;
QString mount1;
QString nfs1;
QString adblog;
QString ipaddress2;
QString share2;
QString mount2;
QString nfs2;
QString ipaddress3;
QString share3;
QString mount3;
QString nfs3;
QString ipaddress4;
QString share4;
QString mount4;
QString nfs4;
QString externalLocation;
QString adbstr1 = "ADB running. ";
QString adbstr2 = "ADB stopped. ";
QString devstr1 = "  Current device connected";
QString devstr2 = "  Current device not connected.";
QString devstr3 = "  USB Mode";
QString devstr4 = "  Console Mode";
//QString amazon_update1 = "Amazon updates on   ";
//QString amazon_update0 = "Amazon updates off  ";
QString sshserver1 = "SSH server on       ";
QString sshserver2 = "SSH server off      ";
QString program = "adbLink";
QString tempdir = "/data/local/tmp/";

int usbcheck;
int rootpath;
int ftvupdate;
int checkversion;
int extdata;
int buffermode = 1;
int tsvalue = 4000;
int ct = 1;
int Id = 0;
int deviceboxindex = 0;

QSqlDatabase db;



//////////////////////////////////////////////
 MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

     if (os == 1)
        {
         adbdir = "./";
          // adbdir = QDir::currentPath();
         adb = adbdir+"adb.exe";
         adb = '"'+adb+'"';


     }



   if (os == 2)

        {
           adbdir = QCoreApplication::applicationDirPath();
           adbdir = adbdir+"/adbfiles/";


           if (QFile::exists(adbdir+"adb"))
           {
               adb = adbdir+"adb";
               adb = '"'+adb+'"';
               QProcess::execute ("chmod 0755 "+ adb);
           }

           else

           {
           QFile::copy(adbdir+"adb.osx", adbdir+"adb");
           adb = adbdir+"adb";
           adb = '"'+adb+'"';
           QProcess::execute ("chmod 0755 "+ adb);
           }


           if (QFile::exists(adbdir+"fastboot"))
           {
               fastboot = adbdir+"fastboot";
               fastboot = '"'+fastboot+'"';
               QProcess::execute ("chmod 0755 "+ fastboot);
           }

           else

           {
           QFile::copy(adbdir+"fastboot.osx", adbdir+"fastboot");
           fastboot = adbdir+"fastboot";
           fastboot = '"'+fastboot+'"';
           QProcess::execute ("chmod 0755 "+ fastboot);
           }




   }

   if (os == 0)

        {
           adbdir = QCoreApplication::applicationDirPath();
           adbdir = adbdir+"/adbfiles/";
           QProcess::execute ("chmod 0755 "+ adbdir+"adb.linux");

           if (QFile::exists(adbdir+"adb"))
           {
               adb = adbdir+"adb";
               adb = '"'+adb+'"';
               QProcess::execute ("chmod 0755 "+ adb);


           }

           else

           {
           QFile::copy(adbdir+"adb.linux", adbdir+"adb");
           adb = adbdir+"adb";
           adb = '"'+adb+'"';
           QProcess::execute ("chmod 0755 "+ adb);
           }

           if (QFile::exists(adbdir+"fastboot"))
           {
               fastboot = adbdir+"fastboot";
               fastboot = '"'+fastboot+'"';
               QProcess::execute ("chmod 0755 "+ fastboot);


           }

           else

           {
           QFile::copy(adbdir+"fastboot.linux", adbdir+"fastboot");
           adb = adbdir+"fastboot";
           adb = '"'+adb+'"';
           QProcess::execute ("chmod 0755 "+ fastboot);
           }



        }



      dbstring = adbdir+"adblink.db";
      xmldir = adbdir+"remotes/";
      splashdir = adbdir+"splash/";
      recoverydir = adbdir+"cwmrecovery/";
      stkrecoverydir = adbdir+"stkrecovery/";

     ui->setupUi(this);
     setFixedSize(size());



     ui->statusBar->addPermanentWidget(ui->update_status);
     ui->statusBar->addPermanentWidget(ui->server_running);
     ui->statusBar->addPermanentWidget( ui->progressBar);
     ui->progressBar->setHidden(true);

          #ifdef Q_OS_MAC
            //https://bugreports.qt.io/browse/QTBUG-51120
            ui->progressBar->setTextVisible(true);
          #endif //Q_OS_MAC

     QPixmap pix(":/assets/donatel.png");
     QIcon icon(pix);
     ui->donate->setIcon(icon);
     ui->donate->setText("");
     ui->donate->setIconSize(pix.size());


     //ui->apptitle->setText("The Kodi for Android Companion");
     ui->server_running->setText(adbstr2);
     // ui->device_connected->setText(devstr2);
     ui->update_status->setText("");
     ui->sambaLabel->setVisible(false);

  rotate_logfile();


  logfile("adbLink "+version);

  QDateTime dateTime = QDateTime::currentDateTime();
  QString dtstr = dateTime.toString("MMddyyhhmmss");
  logfile(dtstr);

  if (os == 1)
          {
          logfile("Windows");
          }

     if (os == 2)

          {
        logfile("OS X");
          }



     if (os == 0)

          {
        logfile("Linux");

          }

 logfile("------------");


  hdir = QDir::homePath();
  open_pref_database();

   if (!dbexists)
    createTables();

     db.open();

     // addcolumn1();

    loaddevicebox();  // initial load
    description = ui->deviceBox->currentText();
    getRecord(description);



    connect(ui->deviceBox, SIGNAL(currentIndexChanged(int)),
       SLOT(readInc()));


    if (!(os == 1))
      {  QString cstring = "chmod 0755 "+adb;
         QString command=RunProcess(cstring);
       }

    start_server();
    logfile("starting server");
    if (serverRunning)
     { ui->server_running->setText(adbstr1);
        }

    else
    { ui->server_running->setText(adbstr2);
      //ui->device_connected->setText(devstr2);
      ui->update_status->setText("");
      ui->sambaLabel->setVisible(true);
    }


    on_refreshConnectedDevices_clicked();

    // check_root_menu();

     if (checkversion==1)
          get_data();

}


MainWindow::~MainWindow()
{



    logfile("closing program");
    kill_server();
    db.close();
    delete ui;

}




/////////////////
QString MainWindow::getadb()

{
    QString gadb="";
    QString editport="";

    if (!isusb)
        editport=":"+port;

    gadb=adb+" -s "+daddr+editport+" ";


    return gadb;

}


/////////////////////////////////////////////

bool MainWindow::fileExists(QString path) {
    QFileInfo checkFile(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (checkFile.exists() && checkFile.isFile()) {
        return true;
    } else {
        return false;
    }
}

/////////////////////////////////////////
void MainWindow::delayTimer(int rdelay)
{

 QElapsedTimer rtimer;

int nMilliseconds;
 int i = 0;

 rtimer.start();

while(i == 0)
  {
    qApp->processEvents();
     nMilliseconds = rtimer.elapsed();
   if (nMilliseconds >= rdelay)
       break;
}


}



///////////////////////////////////////////////
QString MainWindow::RunProcess(QString cstring)
{
 QProcess run_command;
 run_command.setProcessChannelMode(QProcess::MergedChannels);
 run_command.start(cstring);

 run_command.waitForStarted();

 while(run_command.state() != QProcess::NotRunning)
     qApp->processEvents();

 QString command=run_command.readAll();

 return command;
}


//////////////////////////////////////////////
void MainWindow::rotate_logfile()

{

 QFile file(adbdir+"adblink.old.log");

 if( file.exists() )
     QFile::remove(adbdir+"adblink.old.log");


QFile file2(adbdir+"adblink.log");

if( file2.exists() )
    file2.rename(adbdir+"adblink.old.log");


}


//////////////////////////////////////////////
void MainWindow::logfile(QString line)

{


QFile file(adbdir+"adblink.log");
   if(!file.open(QFile::WriteOnly | QFile::Text | QFile::Append))
      {
       QMessageBox::critical(0, "","Can't create logfile!\n",QMessageBox::Cancel);
       return;
      }

   QTextStream out(&file);
            out  << line << endl;

 }


/////////////////////////////////////////
void MainWindow::rebootDevice(QString reboot)
{

 QElapsedTimer rtimer;
 int nMilliseconds;

QProcess reboot_device;
rtimer.start();
reboot_device.setProcessChannelMode(QProcess::MergedChannels);

QString cstring = getadb() + " " + reboot;

reboot_device.start(cstring);
reboot_device.waitForStarted();
while(reboot_device.state() != QProcess::NotRunning)
  {
    qApp->processEvents();
     nMilliseconds = rtimer.elapsed();
   if (nMilliseconds >= 5000)
       break;
}


}


/////////////////////////////////////////////////////
bool MainWindow::mount_system(QString mnt)
{
       QString cstring = getadb() + " shell su -c mount -o remount,"+mnt+ " /system";
       QString command=RunProcess(cstring);



        if (command.isEmpty())
          {
            logfile("/system mounted "+mnt);
            // logfile(cstring);
            logfile(command);
            return true;
          }
            else
          {
            logfile("/system not mounted "+mnt);
            // logfile(cstring);
            logfile(command);
            return false;
          }

}

/////////////////////////////////////////////////////
bool MainWindow::mount_root(QString mnt)
{
       QString cstring = getadb() + " shell su -c mount -o remount,"+mnt+ " /";
       QString command=RunProcess(cstring);

       // logfile(cstring);
       logfile(command);

    if (command.isEmpty())
           {
             logfile("/ mounted "+mnt);
             // logfile(cstring);
             logfile(command);
             return true;
            }
            else
            {
               logfile("/ not mounted "+mnt);
               // logfile(cstring);
               logfile(command);
               return false;
               }

}



/////////////////////////////
bool MainWindow::is_su()
{

QString cstring = getadb() + " shell ls /system/xbin/su";
QString command=RunProcess(cstring);



if (command.contains("No such file or directory"))
  {

    return false;
   }
    else
  {
     return true;
   }


}




/////////////////////////////
bool MainWindow::is_busybox()
{

QString cstring;
QString command;
busypath="/data/local/tmp/adblink/";

cstring = getadb() + " shell ls /data/local/tmp/adbfire";
command=RunProcess(cstring);


if (!command.contains("No such file or directory"))
   {
    cstring = getadb() + " shell rm -r /data/local/tmp/adbfire";
    command=RunProcess(cstring);
   }


cstring = getadb() + " shell ls /data/local/tmp/adblink";
command=RunProcess(cstring);


if (command.contains("No such file or directory"))
   {
    cstring = getadb() + " shell mkdir -p /data/local/tmp/adblink";
    command=RunProcess(cstring);
   }

  cstring = getadb() + " shell ls /data/local/tmp/adblink/busybox";
  command=RunProcess(cstring);


  if (command.contains("No such file or directory"))
     {
      QString busybox = adbdir+"busybox";
      QString cstring = getadb() + " push "+busybox+ " /data/local/tmp/adblink/";
      QString command=RunProcess(cstring);
      if (!command.contains("bytes"))
        {
          logfile("busybox install failed ");
          // logfile(cstring);
           logfile(command);
           busypath="";
           QMessageBox::critical(0,"","busybox install failed. See log.");
           return false;
          }
     else
      {
          // logfile(cstring);
          logfile(command);

          cstring = getadb() + " shell chmod 755 /data/local/tmp/adblink/busybox";
          command=RunProcess(cstring);

          // logfile(cstring);
          logfile(command);

           cstring = getadb() + " shell /data/local/tmp/adblink/busybox --install -s /data/local/tmp/adblink";
           command=RunProcess(cstring);

           // logfile(cstring);
           logfile(command);

      }


  }

  return true;

}


/////////////////////////////
bool MainWindow::is_system_tools()
{

QString cstring;
QString command;

cstring = getadb() + " shell ls /data/local/tmp/adblink/mntdrives.sh";
command=RunProcess(cstring);


if (command.contains("No such file or directory"))
     return false;
else
     return true;

}




/////////////////////////////
QString MainWindow::is_amazon()
{

QString cstring;
QString command;
QString device_name;

  if (isConnected)
    { cstring = getadb() + " shell cat /system/build.prop";
       command=RunProcess(cstring);
  }

  if (command.contains("amazon"))
  {   device_name = "Amazon device";
      return device_name;
  }


  if (command.contains("nvidia"))
  {   device_name = "Nvidia device";
      return device_name;
  }


        device_name = "Unknown device";
        return device_name;

}


////////////////////////////////////////////////
 QString MainWindow::strip (QString str)
{
    str = str.simplified();
    str.replace( " ", "" );
    return str;
}

 ////////////////////////////////////////////

 void MainWindow::blank_entry_form()
 {

     daddr="";
     description="";
     sldir = hdir;
     pushdir = hdir;
     pulldir = hdir;
     isusb = false;
     filepath = "/files/.kodi";
     port = "5555";
     buffermode = 1;
     buffersize = "20971520";
     bufferfactor = "1";
     versioncheck=true;
     xbmcpackage = "org.xbmc.kodi";
     data_root="/sdcard/";


 }


 //////////////////////////////////////////
 void MainWindow::kill_server()
{

 QString cstring = adb + " kill-server";
 QString command=RunProcess(cstring);
 // logfile(cstring);
 logfile("server stopped");
 serverRunning = false;

}


//////////////////////////////////////
void MainWindow::start_server()
{

    QString cstring = adb + " kill-server";
    QString command=RunProcess(cstring);


      cstring = adb + " start-server";
      command=RunProcess(cstring);

     if (command.contains("daemon started successfully"))
        {
           logfile("server started");
          // logfile(cstring);
           logfile(command);
           serverRunning = true;
          }

         else
        {
         logfile("start-server failed!");
         // logfile(cstring);
         logfile(command);
         serverRunning = false;
         }
}


/////////////////////////////////////////////////////
bool MainWindow::is_os5()
{

    bool os_5;
    QString editport = ":"+port;
    QString command;
    QString cstring;

    if (isusb)
    editport = "";

    QString osname="ro.build.version.fireos=5";
    cstring = getadb() + " shell cat /system/build.prop | grep " + osname;
    command=RunProcess(cstring);
        if (command.contains("5."))
            {os_5 = true;
              }
            else
            { os_5 = false;
               }



        return os_5;

}


/////////////////////////////////////////////////////
bool MainWindow::is_package(QString package)
{

    QString editport = ":"+port;

    if (isusb)
    editport = "";




    QString cstring = getadb() + " -s "+daddr+editport+" shell pm list packages ";
    QString command=RunProcess(cstring);
    logfile ("package: "+cstring);

        if (command.contains(package))
            {
            logfile(package+ " is installed");
            // logfile(cstring);
            // logfile(command);
            is_packageInstalled = true;
            }
            else
            {
            logfile(package+ " not found");
            // logfile(cstring);
            // logfile(command);
            is_packageInstalled = false;}

        return  is_packageInstalled;
}


/////////////////////////////////////////////////////
bool MainWindow::amazon_updates(QString onoff)
{

    QString cstring;
    QString command;
    QString pkg;

    if (is_os5())
    {

       cstring = getadb() + " shell su -c pm "+ onoff + " com.amazon.device.software.ota";


    }

    else
    {
        cstring = getadb() + " shell su -c pm "+ onoff + " com.amazon.dcp";
     }


      command=RunProcess(cstring);



       logfile("amazon updates");

        if (onoff == "enable")
           {

            if (command.contains("enabled"))
               {
                // logfile(cstring);
                logfile(command);
                return true;
            }

            else

            {
                // logfile(cstring);
                logfile(command);
                return false;
            }


           }




        if (onoff == "disable")
           {

            if (command.contains("disabled"))
              {
                // logfile(cstring);
                logfile(command);
                return true;
            }

            else

            {
                // logfile(cstring);
                logfile(command);
                return false;
            }

           }

        return false;
}



//////// DATABASE ///////////////////

////////////////////////////////
int MainWindow::getShareCount()
{

   int rowcount=0;
   QString sqlstatement = "SELECT Count(*) FROM netshare";

    QSqlQuery query;
    query.exec(sqlstatement);
    while (query.next()) {
          rowcount = query.value(0).toInt();
    }

    if (query.lastError().isValid())
     {
        logfile(sqlstatement);
        logfile("SqLite error:" + query.lastError().text());
        logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
       }


    return rowcount;
}


////////////////////////////////
int MainWindow::getRows()
{

   int rowcount=0;
   QString sqlstatement = "SELECT Count(*) FROM device";

    QSqlQuery query;
    query.exec(sqlstatement);
    while (query.next()) {
          rowcount = query.value(0).toInt();
    }

    if (query.lastError().isValid())
     {
        logfile(sqlstatement);
        logfile("SqLite error:" + query.lastError().text());
        logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
       }


    return rowcount;
}




////////////////////////////////

void MainWindow::createTables()
{


    logfile("creating adblink.db");

   QString sqlstatement = "create table device(Id INTEGER PRIMARY KEY, daddr varchar(130) ,description varchar(20) NOT NULL UNIQUE,sldir varchar(100),pushdir varchar(100),pulldir varchar(100), xbmcpackage varchar(50) , sshpassword varchar(10) , versioncheck int, buffermode int, buffersize varchar(10), bufferfactor varchar(10), filepath varchar(20), port varchar(6),isusb int)";

    QSqlQuery query;
    query.exec(sqlstatement);

    if (query.lastError().isValid())
     {
        logfile(sqlstatement);
        logfile("SqLite error:" + query.lastError().text());
        logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
       }


   sqlstatement = "create table netshare(Id INTEGER PRIMARY KEY, sharedescrip varchar(20) NOT NULL UNIQUE, ipaddress1 varchar(20),ipaddress2 varchar(20), ipaddress3 varchar(20),ipaddress4 varchar(20),share1 varchar(60),share2 varchar(60), share3 varchar(60),share4 varchar(60),mount1 varchar(60), mount2 varchar(60), mount3 varchar(60), mount4 varchar(60), nfs1 varchar(1),  nfs2 varchar(1), nfs3 varchar(1), nfs4 varchar(1))";

    query.exec(sqlstatement);

    if (query.lastError().isValid())
     {
        logfile(sqlstatement);
        logfile("SqLite error:" + query.lastError().text());
        logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
       }




}





////////////////////////////////

void MainWindow::insertDevice()
{

   logfile("Insert new record");

   QSqlQuery query;

    daddr.replace(QString("'"), QString("''"));
    description.replace(QString("'"), QString("''"));
    xbmcpackage.replace(QString("'"), QString("''"));
    sldir.replace(QString("'"), QString("''"));
    pushdir.replace(QString("'"), QString("''"));
    pulldir.replace(QString("'"), QString("''"));
    xbmcpackage.replace(QString("'"), QString("''"));
    filepath.replace(QString("'"), QString("''"));
    port.replace(QString("'"), QString("''"));
    data_root.replace(QString("'"), QString("''"));


    // usbck.setNum(usbcheck);
    // ftvupdt.setNum(ftvupdate);

    QString ckversion;
    QString buffermd;
    QString usbflag;


    ckversion.setNum(checkversion);
    buffermd.setNum(buffermode);
    usbflag.setNum(isusb);

QString sql1  = "INSERT INTO device( daddr, description, sldir, pushdir, pulldir, xbmcpackage, sshpassword, versioncheck, buffermode, buffersize, bufferfactor, filepath , port ,isusb )";

QString sql2 = " VALUES  ('"+daddr+"', '"+description+"', '"+sldir+"',  '"+pushdir+"', '"+pulldir+"', '"+xbmcpackage+"','"+data_root+"', '"+ckversion+"', '"+buffermd+"',  '"+buffersize+"',  '"+bufferfactor+"', '"+filepath+"', '"+port+"','"+usbflag+"' )";

QString sqlstatement = sql1+sql2;

      query.exec(sqlstatement);

      if (query.lastError().isValid())
       {
         logfile(sqlstatement);
         logfile("SqLite error:" + query.lastError().text());
         logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
        }


}



////////////////////////////////
void MainWindow::insertShare()
{

   logfile("Insert new share record");
   logfile(description);

   QSqlQuery query;

    description.replace(QString("'"), QString("''"));

    ipaddress1.replace(QString("'"), QString("''"));
    share1.replace(QString("'"), QString("''"));
    mount1.replace(QString("'"), QString("''"));
    nfs1.replace(QString("'"), QString("''"));

    ipaddress2.replace(QString("'"), QString("''"));
    share2.replace(QString("'"), QString("''"));
    mount2.replace(QString("'"), QString("''"));
    nfs2.replace(QString("'"), QString("''"));

    ipaddress3.replace(QString("'"), QString("''"));
    share3.replace(QString("'"), QString("''"));
    mount3.replace(QString("'"), QString("''"));
    nfs3.replace(QString("'"), QString("''"));

    ipaddress4.replace(QString("'"), QString("''"));
    share4.replace(QString("'"), QString("''"));
    mount4.replace(QString("'"), QString("''"));
    nfs4.replace(QString("'"), QString("''"));



QString sql1 = " INSERT INTO netshare( sharedescrip , ipaddress1,share1 ,mount1 , nfs1 ,ipaddress2,share2 ,mount2 , nfs2,  ipaddress3,share3 ,mount3 , nfs3,ipaddress4,share4 ,mount4 , nfs4 )";

QString sql2 = " VALUES  ('"+description+"', '"+ipaddress1+"', '"+share1+"','"+mount1+"','"+nfs1+"','"+ipaddress2+"','"+share2+"','"+mount2+"','"+nfs2+"','"+ipaddress3+"','"+share3+"','"+mount3+"','"+nfs3+"','"+ipaddress4+"','"+share4+"','"+mount4+"','"+nfs4+"' )";

QString sqlstatement = sql1+sql2;

      query.exec(sqlstatement);

      if (query.lastError().isValid())
       {
         logfile(sqlstatement);
         logfile("SqLite error:" + query.lastError().text());
         logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
        }


}





////////////////////////////////
void MainWindow::updateRoot()
{
logfile("updateRoot()");


    logfile("updating database adblink.db");

    QString sqlstatement;
    QString tempstring;

    QString idstring;
    idstring.setNum(Id);
    logfile(idstring);
    QSqlQuery query;

    QString quote = "\"";



     tempstring = data_root;
     tempstring.replace(QString("'"), QString("''"));


      sqlstatement = "UPDATE device SET sshpassword='"+tempstring+"'  WHERE Id="+ idstring;
      query.exec(sqlstatement);

      if (query.lastError().isValid())
       {
         logfile(sqlstatement);
         logfile("SqLite error:" + query.lastError().text());
         logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
        }




}




//////////////////////////////////////////////

void MainWindow::updateDevice(QString olddescription)
{
logfile("updateDevice()");


    logfile("updating database adblink.db");

    QString str1;
    QString str2;
    QString str3;
    QString str4;
    QString str5;
    QString tempstring;
    QString sqlstatement;

    str1.setNum(usbcheck);
    str2.setNum(ftvupdate);
    str3.setNum(checkversion);
    str4.setNum(buffermode);
    str5.setNum(isusb);

  //  int idstring = Id.t;
    QString idstring;
    idstring.setNum(Id);
    logfile(idstring);
    QSqlQuery query;

    QString quote = "\"";




    if (olddescription != description)
    {

        tempstring = description;
        tempstring.replace(QString("'"), QString("''"));

           olddescription = quote+olddescription+quote;

            sqlstatement = "UPDATE netshare SET sharedescrip='"+tempstring+"'  WHERE sharedescrip="+ olddescription;
             query.exec(sqlstatement);

             if (query.lastError().isValid())
              {
                logfile(sqlstatement);
                logfile("SqLite error:" + query.lastError().text());
                logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
               }

    }


    tempstring = daddr;
    tempstring.replace(QString("'"), QString("''"));

    sqlstatement = "UPDATE device SET daddr='"+tempstring+"'  WHERE Id="+ idstring;
    logfile(sqlstatement);
    query.exec(sqlstatement);

     if (query.lastError().isValid())
      {
        logfile(sqlstatement);
        logfile("SqLite error:" + query.lastError().text());
        logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
       }


     tempstring = sldir;
     tempstring.replace(QString("'"), QString("''"));


     sqlstatement = "UPDATE device SET sldir='"+tempstring+"'  WHERE Id="+ idstring;
     query.exec(sqlstatement);


     if (query.lastError().isValid())
      {
        logfile(sqlstatement);
        logfile("SqLite error:" + query.lastError().text());
        logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
       }


     tempstring = pushdir;
     tempstring.replace(QString("'"), QString("''"));

     sqlstatement = "UPDATE device SET pushdir='"+tempstring+"'  WHERE Id="+ idstring;
     query.exec(sqlstatement);

     if (query.lastError().isValid())
      {
        logfile(sqlstatement);
        logfile("SqLite error:" + query.lastError().text());
        logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
       }


     tempstring = pulldir;
     tempstring.replace(QString("'"), QString("''"));

     sqlstatement = "UPDATE device SET pulldir='"+tempstring+"'  WHERE Id="+ idstring;
     query.exec(sqlstatement);


     if (query.lastError().isValid())
      {
        logfile(sqlstatement);
        logfile("SqLite error:" + query.lastError().text());
        logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
       }


     tempstring = xbmcpackage;
     tempstring.replace(QString("'"), QString("''"));

     sqlstatement = "UPDATE device SET xbmcpackage='"+tempstring+"'  WHERE Id="+ idstring;
     query.exec(sqlstatement);

     if (query.lastError().isValid())
      {
        logfile(sqlstatement);
        logfile("SqLite error:" + query.lastError().text());
        logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
       }


     tempstring = data_root;
     tempstring.replace(QString("'"), QString("''"));


      sqlstatement = "UPDATE device SET sshpassword='"+tempstring+"'  WHERE Id="+ idstring;
      query.exec(sqlstatement);

      if (query.lastError().isValid())
       {
         logfile(sqlstatement);
         logfile("SqLite error:" + query.lastError().text());
         logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
        }


      tempstring = str3;
      tempstring.replace(QString("'"), QString("''"));

      sqlstatement = "UPDATE device SET versioncheck='"+tempstring+"'  WHERE Id="+ idstring;
      query.exec(sqlstatement);

      if (query.lastError().isValid())
       {
         logfile(sqlstatement);
         logfile("SqLite error:" + query.lastError().text());
         logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
        }


      tempstring = str4;
      tempstring.replace(QString("'"), QString("''"));


       sqlstatement = "UPDATE device SET buffermode='"+tempstring+"'  WHERE Id="+ idstring;
       query.exec(sqlstatement);

       if (query.lastError().isValid())
        {
          logfile(sqlstatement);
          logfile("SqLite error:" + query.lastError().text());
          logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
         }


       tempstring = buffersize;
       tempstring.replace(QString("'"), QString("''"));

       sqlstatement = "UPDATE device SET buffersize='"+tempstring+"'  WHERE Id="+ idstring;
        query.exec(sqlstatement);

        if (query.lastError().isValid())
         {
           logfile(sqlstatement);
           logfile("SqLite error:" + query.lastError().text());
           logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
          }


        tempstring = bufferfactor;
        tempstring.replace(QString("'"), QString("''"));

         sqlstatement = "UPDATE device SET bufferfactor='"+tempstring+"'  WHERE Id="+ idstring;
         query.exec(sqlstatement);

         if (query.lastError().isValid())
          {
            logfile(sqlstatement);
            logfile("SqLite error:" + query.lastError().text());
            logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
           }


         tempstring = description;
         tempstring.replace(QString("'"), QString("''"));

          sqlstatement = "UPDATE device SET description='"+tempstring+"'  WHERE Id="+ idstring;
          query.exec(sqlstatement);

          if (query.lastError().isValid())
           {
             logfile(sqlstatement);
             logfile("SqLite error:" + query.lastError().text());
             logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
            }

          tempstring = filepath;
          tempstring.replace(QString("'"), QString("''"));

           sqlstatement = "UPDATE device SET filepath='"+tempstring+"'  WHERE Id="+ idstring;
           query.exec(sqlstatement);

           if (query.lastError().isValid())
            {
              logfile(sqlstatement);
              logfile("SqLite error:" + query.lastError().text());
              logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
             }


           tempstring = port;
           tempstring.replace(QString("'"), QString("''"));

           sqlstatement = "UPDATE device SET port='"+tempstring+"'  WHERE Id="+ idstring;
           query.exec(sqlstatement);

           if (query.lastError().isValid())
            {
              logfile(sqlstatement);
              logfile("SqLite error:" + query.lastError().text());
              logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
             }



           tempstring = str5;
           tempstring.replace(QString("'"), QString("''"));

           sqlstatement = "UPDATE device SET isusb='"+tempstring+"'  WHERE Id="+ idstring;
           query.exec(sqlstatement);

           if (query.lastError().isValid())
            {
              logfile(sqlstatement);
              logfile("SqLite error:" + query.lastError().text());
              logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
             }




}




////////////////////////////////////////////////

void MainWindow::updateShares()
{


    logfile("updating shares table adblink.db");


    QSqlQuery query;
    QString sharedescrip;
    QString tempstring;
    QString sqlstatement;

    QString quote = "\"";
    QString descrip = quote+description+quote;



    tempstring = ipaddress1;
    tempstring.replace(QString("'"), QString("''"));


     sqlstatement = "UPDATE netshare SET ipaddress1='"+tempstring+"'  WHERE sharedescrip="+ descrip;
     query.exec(sqlstatement);

     if (query.lastError().isValid())
      {
        logfile(sqlstatement);
        logfile("SqLite error:" + query.lastError().text());
        logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
       }




     tempstring = share1;
     tempstring.replace(QString("'"), QString("''"));

     sqlstatement = "UPDATE netshare SET share1='"+tempstring+"'  WHERE sharedescrip="+ descrip;
      query.exec(sqlstatement);

      if (query.lastError().isValid())
       {
         logfile(sqlstatement);
         logfile("SqLite error:" + query.lastError().text());
         logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
        }


      tempstring = mount1;
      tempstring.replace(QString("'"), QString("''"));

       sqlstatement = "UPDATE netshare SET mount1='"+tempstring+"'  WHERE sharedescrip="+ descrip;
       query.exec(sqlstatement);

       if (query.lastError().isValid())
        {
          logfile(sqlstatement);
          logfile("SqLite error:" + query.lastError().text());
          logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
         }



       tempstring = nfs1;
       tempstring.replace(QString("'"), QString("''"));

        sqlstatement = "UPDATE netshare SET nfs1='"+tempstring+"'  WHERE sharedescrip="+ descrip;
        query.exec(sqlstatement);

        if (query.lastError().isValid())
         {
           logfile(sqlstatement);
           logfile("SqLite error:" + query.lastError().text());
           logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
          }



        tempstring = ipaddress2;
        tempstring.replace(QString("'"), QString("''"));

         sqlstatement = "UPDATE netshare SET ipaddress2='"+tempstring+"'  WHERE sharedescrip="+ descrip;
         query.exec(sqlstatement);

         if (query.lastError().isValid())
          {
            logfile(sqlstatement);
            logfile("SqLite error:" + query.lastError().text());
            logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
           }



         tempstring = share2;
         tempstring.replace(QString("'"), QString("''"));

         sqlstatement = "UPDATE netshare SET share2='"+tempstring+"'  WHERE sharedescrip="+ descrip;
          query.exec(sqlstatement);

          if (query.lastError().isValid())
           {
             logfile(sqlstatement);
             logfile("SqLite error:" + query.lastError().text());
             logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
            }


          tempstring = mount2;
          tempstring.replace(QString("'"), QString("''"));

           sqlstatement = "UPDATE netshare SET mount2='"+tempstring+"'  WHERE sharedescrip="+ descrip;
           query.exec(sqlstatement);

           if (query.lastError().isValid())
            {
              logfile(sqlstatement);
              logfile("SqLite error:" + query.lastError().text());
              logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
             }



           tempstring = nfs2;
           tempstring.replace(QString("'"), QString("''"));

            sqlstatement = "UPDATE netshare SET nfs2='"+tempstring+"'  WHERE sharedescrip="+ descrip;
            query.exec(sqlstatement);

            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }




            tempstring = ipaddress3;
            tempstring.replace(QString("'"), QString("''"));

             sqlstatement = "UPDATE netshare SET ipaddress3='"+tempstring+"'  WHERE sharedescrip="+ descrip;
             query.exec(sqlstatement);

             if (query.lastError().isValid())
              {
                logfile(sqlstatement);
                logfile("SqLite error:" + query.lastError().text());
                logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
               }



             tempstring = share3;
             tempstring.replace(QString("'"), QString("''"));

             sqlstatement = "UPDATE netshare SET share3='"+tempstring+"'  WHERE sharedescrip="+ descrip;
              query.exec(sqlstatement);

              if (query.lastError().isValid())
               {
                 logfile(sqlstatement);
                 logfile("SqLite error:" + query.lastError().text());
                 logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
                }


              tempstring = mount3;
              tempstring.replace(QString("'"), QString("''"));

               sqlstatement = "UPDATE netshare SET mount3='"+tempstring+"'  WHERE sharedescrip="+ descrip;
               query.exec(sqlstatement);

               if (query.lastError().isValid())
                {
                  logfile(sqlstatement);
                  logfile("SqLite error:" + query.lastError().text());
                  logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
                 }



               tempstring = nfs3;
               tempstring.replace(QString("'"), QString("''"));

                sqlstatement = "UPDATE netshare SET nfs3='"+tempstring+"'  WHERE sharedescrip="+ descrip;
                query.exec(sqlstatement);

                if (query.lastError().isValid())
                 {
                   logfile(sqlstatement);
                   logfile("SqLite error:" + query.lastError().text());
                   logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
                  }




                tempstring = ipaddress4;
                tempstring.replace(QString("'"), QString("''"));

                 sqlstatement = "UPDATE netshare SET ipaddress4='"+tempstring+"'  WHERE sharedescrip="+ descrip;
                 query.exec(sqlstatement);

                 if (query.lastError().isValid())
                  {
                    logfile(sqlstatement);
                    logfile("SqLite error:" + query.lastError().text());
                    logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
                   }



                 tempstring = share4;
                 tempstring.replace(QString("'"), QString("''"));

                 sqlstatement = "UPDATE netshare SET share4='"+tempstring+"'  WHERE sharedescrip="+ descrip;
                  query.exec(sqlstatement);

                  if (query.lastError().isValid())
                   {
                     logfile(sqlstatement);
                     logfile("SqLite error:" + query.lastError().text());
                     logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
                    }


                  tempstring = mount4;
                  tempstring.replace(QString("'"), QString("''"));

                   sqlstatement = "UPDATE netshare SET mount4='"+tempstring+"'  WHERE sharedescrip="+ descrip;
                   query.exec(sqlstatement);

                   if (query.lastError().isValid())
                    {
                      logfile(sqlstatement);
                      logfile("SqLite error:" + query.lastError().text());
                      logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
                     }



                   tempstring = nfs4;
                   tempstring.replace(QString("'"), QString("''"));

                    sqlstatement = "UPDATE netshare SET nfs4='"+tempstring+"'  WHERE sharedescrip="+ descrip;
                    query.exec(sqlstatement);

                    if (query.lastError().isValid())
                     {
                       logfile(sqlstatement);
                       logfile("SqLite error:" + query.lastError().text());
                       logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
                      }


}



///////////////////////////////////////////////

void MainWindow::getRecord(QString descrip)

{


  QString sqlstatement;


  logfile("getting database record");

  QString quote = "\"";

  descrip = quote+descrip+quote;
  QSqlQuery query;


   sqlstatement= "SELECT Id FROM device WHERE description=" + descrip;
   query.exec(sqlstatement);
   logfile(sqlstatement);


           while (query.next()) {
                  Id = query.value(0).toInt();
                }


             if (query.lastError().isValid())
              {
                logfile(sqlstatement);
                logfile("SqLite error:" + query.lastError().text());
                logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
               }



             sqlstatement= "SELECT daddr FROM device WHERE description=" + descrip;
             query.exec(sqlstatement);
             logfile(sqlstatement);


                     while (query.next()) {
                            daddr = query.value(0).toString();
                          }


                       if (query.lastError().isValid())
                        {
                          logfile(sqlstatement);
                          logfile("SqLite error:" + query.lastError().text());
                          logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
                         }





         sqlstatement="SELECT sldir FROM device  WHERE description=" + descrip;
         query.exec(sqlstatement);
           while (query.next()) {
                sldir = query.value(0).toString();
          }

           if (query.lastError().isValid())
            {
              logfile(sqlstatement);
              logfile("SqLite error:" + query.lastError().text());
              logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
             }


           sqlstatement="SELECT pushdir FROM device  WHERE description=" + descrip;
           query.exec(sqlstatement);
            while (query.next()) {
                 pushdir = query.value(0).toString();
           }

        //    logfile(sqlstatement);
         //   logfile(pushdir);

            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }


           sqlstatement="SELECT pulldir FROM device  WHERE description=" + descrip;
            query.exec(sqlstatement);
            while (query.next()) {
                  pulldir = query.value(0).toString();
            }

        //    logfile(sqlstatement);
        //    logfile(pulldir);

            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }



            sqlstatement="SELECT xbmcpackage FROM device  WHERE description=" + descrip;
            query.exec(sqlstatement);
            while (query.next()) {
                  xbmcpackage = query.value(0).toString();
            }

      //      logfile(sqlstatement);
      //      logfile(xbmcpackage);

            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }


            sqlstatement="SELECT sshpassword FROM device  WHERE description=" + descrip;
            query.exec(sqlstatement);
            while (query.next()) {
                  data_root = query.value(0).toString();
            }

         //   logfile(sqlstatement);
         //   logfile(sshpassword);

            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }


            sqlstatement="SELECT versioncheck FROM device  WHERE description=" + descrip;
            query.exec(sqlstatement);
            while (query.next()) {
                  checkversion = query.value(0).toInt();
            }

        //    logfile(sqlstatement);

            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }

          //  logfile(sqlstatement);

            sqlstatement="SELECT buffermode FROM device  WHERE description=" + descrip;
            query.exec(sqlstatement);
            while (query.next()) {
                  buffermode = query.value(0).toInt();
            }

        //    logfile(sqlstatement);

            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }



            sqlstatement="SELECT buffersize FROM device  WHERE description=" + descrip;
            query.exec(sqlstatement);
            while (query.next()) {
                  buffersize = query.value(0).toString();
            }


        //      logfile(sqlstatement);
         //     logfile(buffersize);

            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }


            sqlstatement="SELECT bufferfactor FROM device  WHERE description=" + descrip;
            query.exec(sqlstatement);
            while (query.next()) {
                  bufferfactor = query.value(0).toString();
            }

        //    logfile(sqlstatement);
         //   logfile(bufferfactor);

            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }


            sqlstatement="SELECT description FROM device  WHERE description=" + descrip;
            query.exec(sqlstatement);
            while (query.next()) {
                  description = query.value(0).toString();
            }

         //   logfile(sqlstatement);
         //   logfile(description);

            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }


            sqlstatement="SELECT filepath FROM device  WHERE description=" + descrip;
            query.exec(sqlstatement);
            while (query.next()) {
                  filepath = query.value(0).toString();
            }

        //    logfile(sqlstatement);
        //    logfile(filepath);

            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }



            sqlstatement="SELECT port FROM device  WHERE description=" + descrip;
            query.exec(sqlstatement);
            while (query.next()) {
                  port = query.value(0).toString();
            }

        //    logfile(sqlstatement);
        //    logfile(filepath);

            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }



            sqlstatement="SELECT isusb FROM device  WHERE description=" + descrip;
            query.exec(sqlstatement);
            while (query.next()) {
                  isusb = query.value(0).toInt();
            }

        //    logfile(sqlstatement);

            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }



     if (sldir.isEmpty())
         sldir = hdir;

     if (pushdir.isEmpty())
      pushdir = hdir;

     if (pulldir.isEmpty())
      pulldir = hdir;

     if (xbmcpackage.isEmpty())
         xbmcpackage = "org.xbmc.kodi";

     if (data_root.isEmpty())
         data_root = "/sdcard/";

     if (checkversion==0)
         versioncheck=false;
     else
         versioncheck=true;


}




///////////////////////////////////

void MainWindow::readShares()

{


    QString sqlstatement;


    logfile("reading share table");

     QSqlQuery query;



     QString quote = "\"";

     QString descrip = quote+description+quote;




     sqlstatement= "SELECT ipaddress1 FROM netshare WHERE sharedescrip="+ descrip;
     query.exec(sqlstatement);
         while (query.next()) {
             ipaddress1 = query.value(0).toString();
         }




         if (query.lastError().isValid())
          {
            logfile(sqlstatement);
            logfile("SqLite error:" + query.lastError().text());
            logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
           }




         sqlstatement="SELECT share1 FROM netshare  WHERE sharedescrip="+ descrip;
         query.exec(sqlstatement);
           while (query.next()) {
                share1 = query.value(0).toString();
          }



           if (query.lastError().isValid())
            {
              logfile(sqlstatement);
              logfile("SqLite error:" + query.lastError().text());
              logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
             }




           sqlstatement="SELECT mount1 FROM netshare WHERE sharedescrip="+ descrip;
           query.exec(sqlstatement);
            while (query.next()) {
                 mount1 = query.value(0).toString();
           }



            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }


           sqlstatement="SELECT nfs1 FROM netshare  WHERE sharedescrip="+ descrip;
            query.exec(sqlstatement);
            while (query.next()) {
                  nfs1 = query.value(0).toString();
            }


            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }



        sqlstatement= "SELECT ipaddress2 FROM netshare WHERE sharedescrip="+ descrip;
        query.exec(sqlstatement);
            while (query.next()) {
                ipaddress2 = query.value(0).toString();
            }




            if (query.lastError().isValid())
             {
               logfile(sqlstatement);
               logfile("SqLite error:" + query.lastError().text());
               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
              }

            sqlstatement="SELECT share2 FROM netshare  WHERE sharedescrip="+ descrip;
            query.exec(sqlstatement);
              while (query.next()) {
                   share2 = query.value(0).toString();
             }



              if (query.lastError().isValid())
               {
                 logfile(sqlstatement);
                 logfile("SqLite error:" + query.lastError().text());
                 logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
                }

              sqlstatement="SELECT mount2 FROM netshare WHERE sharedescrip="+ descrip;
              query.exec(sqlstatement);
               while (query.next()) {
                    mount2 = query.value(0).toString();
              }



               if (query.lastError().isValid())
                {
                  logfile(sqlstatement);
                  logfile("SqLite error:" + query.lastError().text());
                  logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
                 }


              sqlstatement="SELECT nfs2 FROM netshare  WHERE sharedescrip="+ descrip;
               query.exec(sqlstatement);
               while (query.next()) {
                     nfs2 = query.value(0).toString();
               }


               if (query.lastError().isValid())
                {
                  logfile(sqlstatement);
                  logfile("SqLite error:" + query.lastError().text());
                  logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
                 }


               sqlstatement= "SELECT ipaddress3 FROM netshare WHERE sharedescrip="+ descrip;
               query.exec(sqlstatement);
                   while (query.next()) {
                       ipaddress3 = query.value(0).toString();
                   }


    //              logfile(sqlstatement);

                   if (query.lastError().isValid())
                    {
                      logfile(sqlstatement);
                      logfile("SqLite error:" + query.lastError().text());
                      logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
                     }




                   sqlstatement="SELECT share3 FROM netshare  WHERE sharedescrip="+ descrip;
                   query.exec(sqlstatement);
                     while (query.next()) {
                          share3 = query.value(0).toString();
                    }



                     if (query.lastError().isValid())
                      {
                        logfile(sqlstatement);
                        logfile("SqLite error:" + query.lastError().text());
                        logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
                       }




                     sqlstatement="SELECT mount3 FROM netshare WHERE sharedescrip="+ descrip;
                     query.exec(sqlstatement);
                      while (query.next()) {
                           mount3 = query.value(0).toString();
                     }



                      if (query.lastError().isValid())
                       {
                         logfile(sqlstatement);
                         logfile("SqLite error:" + query.lastError().text());
                         logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
                        }


                     sqlstatement="SELECT nfs3 FROM netshare  WHERE sharedescrip="+ descrip;
                      query.exec(sqlstatement);
                      while (query.next()) {
                            nfs3 = query.value(0).toString();
                      }


                      if (query.lastError().isValid())
                       {
                         logfile(sqlstatement);
                         logfile("SqLite error:" + query.lastError().text());
                         logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
                        }


                      sqlstatement= "SELECT ipaddress4 FROM netshare WHERE sharedescrip="+ descrip;
                      query.exec(sqlstatement);
                          while (query.next()) {
                              ipaddress4 = query.value(0).toString();
                          }


        //                 logfile(sqlstatement);

                          if (query.lastError().isValid())
                           {
                             logfile(sqlstatement);
                             logfile("SqLite error:" + query.lastError().text());
                             logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
                            }




                          sqlstatement="SELECT share4 FROM netshare  WHERE sharedescrip="+ descrip;
                          query.exec(sqlstatement);
                            while (query.next()) {
                                 share4 = query.value(0).toString();
                           }



                            if (query.lastError().isValid())
                             {
                               logfile(sqlstatement);
                               logfile("SqLite error:" + query.lastError().text());
                               logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
                              }




                            sqlstatement="SELECT mount4 FROM netshare WHERE sharedescrip="+ descrip;
                            query.exec(sqlstatement);
                             while (query.next()) {
                                  mount4 = query.value(0).toString();
                            }


                             if (query.lastError().isValid())
                              {
                                logfile(sqlstatement);
                                logfile("SqLite error:" + query.lastError().text());
                                logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
                               }


                            sqlstatement="SELECT nfs4 FROM netshare  WHERE sharedescrip="+ descrip;
                             query.exec(sqlstatement);
                             while (query.next()) {
                                   nfs4 = query.value(0).toString();
                             }


                             if (query.lastError().isValid())
                              {
                                logfile(sqlstatement);
                                logfile("SqLite error:" + query.lastError().text());
                                logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
                               }


}




//////////////////////////////////////////////

void MainWindow::deleteRecord(QString descrip)

{


  QString sqlstatement;
  logfile("getting database record");

  QString quote = "\"";

  descrip = quote+descrip+quote;
  QSqlQuery query;


   sqlstatement= "DELETE FROM device WHERE description=" + descrip;
   query.exec(sqlstatement);
   logfile(sqlstatement);


   sqlstatement= "DELETE FROM netshare WHERE sharedescrip=" + descrip;
   query.exec(sqlstatement);
   logfile(sqlstatement);






}







//////////////////////////////////////////////
void MainWindow::open_pref_database()

{

    QFile Fout(dbstring);

    if(!Fout.exists())
    {
      dbexists = false;
    }
    else
    {
      dbexists = true;
    }

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbstring);


    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            "Database error:\n"+dbstring
                     , QMessageBox::Cancel);
     logfile("error opening database "+dbstring);

    }



}





/////////////////////////////////////

void MainWindow::addcolumn1()
{
QString sqlstatement="SELECT rootpath FROM device ";
 QSqlQuery query;
 query.exec(sqlstatement);

 if (query.lastError().number() == 1)
  {
     sqlstatement = "ALTER TABLE device ADD COLUMN rootpath int";
     query.exec(sqlstatement);


     if (query.lastError().isValid())
      {
        logfile("rootpath column NOT added to device table");
        logfile(sqlstatement);
        logfile("SqLite error:" + query.lastError().text());
        logfile("SqLite error code:"+ QString::number( query.lastError().number() ));
        QMessageBox::critical(0,"","Can't alter databse. See log.");
     }
   else logfile("rootpath column added to device table");

 }

}


//////////////////////////////////

bool MainWindow::isConnectedToNetwork()
{
    QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();
    bool result = false;

    for (int i = 0; i < ifaces.count(); i++)
    {
        QNetworkInterface iface = ifaces.at(i);
        if ( iface.flags().testFlag(QNetworkInterface::IsUp)
             && !iface.flags().testFlag(QNetworkInterface::IsLoopBack) )
        {


            // this loop is important
            for (int j=0; j<iface.addressEntries().count(); j++)
            {

                // we have an interface that is up, and has an ip address
                // therefore the link is present

                // we will only enable this check on first positive,
                // all later results are incorrect

                if (result == false)
                    result = true;
            }
        }

    }

    return result;
}





/////////////////////////////////////////////////
void MainWindow::writeConfig()

{

   QString l1;
   QString l2;
   QString l3;
   QString l4;

   QString cstring;
   QString command;



 QString sshDir = QDir::homePath() + "/.ssh";


 if ( !QDir(sshDir).exists() )
  {
     QDir().mkdir(sshDir);
     cstring = "chmod 0700 "+sshDir;
     command=RunProcess(cstring);
     // logfile(cstring);
     logfile(command);
 }


 l1 = "Host "+daddr;
 l2 = "HostName "+daddr;
 l3 = "IdentityFile ~/.ssh/id_adblink";
 l4 = "User root";

 if (!fileExists(sshDir+"/config"))
   {

    QString cfgfile = sshDir+"/config";
    QFile file(cfgfile);

      if(!file.open(QFile::WriteOnly |  QFile::Text))
       {
        QMessageBox::critical(0, "","Can't open config file!\n",QMessageBox::Cancel);
        logfile("error creating config!");
        return;
       }

QTextStream out(&file);

   out  << l1 << endl;
   out  << l2 << endl;
   out  << l3 << endl;
   out  << l4 << endl;
   out  << endl;

    file.flush();
    file.close();

}

 else

  {

     QString cfgfile = sshDir+"/config";
     QFile file(cfgfile);


      QFile xfile(cfgfile);
        if (!xfile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
          QMessageBox::critical(0, "","Can't open config file!\n",QMessageBox::Cancel);
          return;
        }

        QStringList stringList;
        QTextStream textStream(&xfile);

        while (!textStream.atEnd())
            stringList << textStream.readLine();

        file.close();



if (!stringList.contains(l1))
{

      if(!file.open(QFile::WriteOnly | QFile::Text | QFile::Append))
         {
           QMessageBox::critical(0, "","Can't open config file!\n",QMessageBox::Cancel);
           return;
         }


 QTextStream out(&file);

 out  << l1 << endl;
 out  << l2 << endl;
 out  << l3 << endl;
 out  << l4 << endl;
 out  << endl;


  file.flush();
  file.close();

 }

 }


 if (!fileExists(sshDir+"/id_adblink"))
   {
      cstring = "cp "+adbdir+"id_adblink  "+sshDir;
      command=RunProcess(cstring);
      // logfile(cstring);
       logfile(command);
    }


 cstring = "chmod 0600 "+sshDir+"/id_adblink";
 command=RunProcess(cstring);
 // logfile(cstring);
 logfile(command);

 cstring = "chmod 0600 "+sshDir+"/config";
 command=RunProcess(cstring);
 // logfile(cstring);
 logfile(command);


}



/////////////////////////////////////

void MainWindow::delay(int secs)
{
    QTime dieTime= QTime::currentTime().addSecs(secs);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


/////////////////////////////////////////////////////////////////////////
bool MainWindow::find_daddr(QString deviceid)
{
   bool usbdaddr = false;

   for(int row = 0; row < ui->listDevices->count(); row++)
   {
       if (ui->listDevices->item(row)->text()==deviceid)
           usbdaddr=true;
   }

    return usbdaddr;
}



//////////////////////////////////////////////////////////////////////
void MainWindow::loaddevicebox() {

    QString sqlstatement;

        QSqlQuery query;

       ui->deviceBox->clear();
       sqlstatement= "SELECT description FROM device";
       query.exec(sqlstatement);
           while (query.next()) {
              description = query.value(0).toString();
              ui->deviceBox->addItem(description);
           }

}

//////////////////////////////////////////////////////////////////////
void MainWindow::get_data() {
   QNetworkRequest request;
   request.setUrl(QUrl(vqurl));

   QNetworkAccessManager *nam = new QNetworkAccessManager();
   QNetworkReply *reply = nam->get(request);

   connect(reply, SIGNAL(finished()),
           this, SLOT(onReqCompleted()));



}

/////////////////////////////////
void MainWindow::onReqCompleted() {
   QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());


   if (reply->error() != QNetworkReply::NoError)
   {

       int err = reply->error();
       QString s2 = QString::number(err);
       QMessageBox::critical(0, "","Network error: " + s2,QMessageBox::Cancel);
       return;

   }

   QByteArray data = reply->readAll();

   QString s1(data);

       s1 = strip(s1);

       int err = reply->error();

       QString s2 = QString::number(err);

       if (version != s1)
       {
           QMessageBox::StandardButton reply;
            reply = QMessageBox::question(0, "", program+" version "+s1+" is ready. Download?",
                    QMessageBox::Yes|QMessageBox::No);
              if (reply == QMessageBox::Yes)
               {
                  QString link = "http://www.jocala.com";
                  QDesktopServices::openUrl(QUrl(link));
                }

       }

       delete reply;

}






//////////////////////////////////////////////////////////////////////
void MainWindow::on_actionQuit_triggered()
{

    QCoreApplication::quit();

}


/////////////////////////////////////////////////////
void MainWindow::TimerEvent()
{
  int value = ui->progressBar->value();

  if (value >= 100)
      {
         value = 0;
         ui->progressBar->reset();
     }


  ui->progressBar->setValue(value+1);


}


/////////////////////////////////////////////////////
void MainWindow::readInc()
{


     description = ui->deviceBox->currentText();
     getRecord(description);

     QString lookup=daddr;

      if(!isusb)
       lookup=lookup+":"+port;

     isConnected=find_daddr(lookup);


      if (isConnected)
        {


         check_update_status();
      }




}

////////////////////////////////////////////////////////////////////////////
void MainWindow::on_sideload_Button_clicked()
{

    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

   // if (!isConnected && !isusb)
          //on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }




    QString cstring;
    QString command;

    QElapsedTimer rtimer;
    int nMilliseconds;
    rtimer.start();

   QString fileName = QFileDialog::getOpenFileName(this,
          tr("Select app to install"), sldir , tr("APK Files (*.apk)"));


    if (!fileName.isEmpty() )
    {

    QFileInfo finfo(fileName);
    sldir = finfo.absolutePath();

    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Install", "Install "+fileName+"?\n",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes)
      {


          ui->progressBar->setHidden(false);
          ui->progressBar->setValue(0);


          QTimer *timer = new QTimer(this);
          connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
          timer->start(tsvalue);

           cstring = getadb() + " install -r " + '"'+ fileName+'"';


           QString command=RunProcess(cstring);

           ui->progressBar->setHidden(true);

           // logfile(cstring);
           logfile(command);

           nMilliseconds = rtimer.elapsed();
           logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


           if (command.contains("Success"))

               QMessageBox::information(this,"","Installed");
              else      
               QMessageBox::critical(this,"","Install failed");

    }

  }


}


///////////////////////////////////////////////////////////////////////////
void MainWindow::on_uninstall_Button_clicked()
{

    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

    //if (!isConnected && !isusb)
         // on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }



QString package = "";
QString cstring;
bool keepbox = false;




    QElapsedTimer rtimer;
    int nMilliseconds;
    rtimer.start();




    logfile("open uninstall dialog");



    uninstallDialog dialog(port,daddr);


    dialog.setdescription(description);

    // dialog.setModal(true);
    if(dialog.exec() == QDialog::Accepted)
    {

    package = dialog.packageName();
    keepbox = dialog.keepBox();

    }

    else return;


    if (package.isEmpty())
       {
        QMessageBox::critical(this,"","No file selected");
        return;
        }



            if ( !is_package(package))
               { QMessageBox::critical(
                     this,
                     "",
                     package +" not installed");
                  return;

            logfile("Error: "+ package +" not installed");
            }


            QMessageBox::StandardButton reply;
                  reply = QMessageBox::question(this, "Uninstall", "Uninstall "+package+"?",
                     QMessageBox::Yes|QMessageBox::No);
                  if (reply == QMessageBox::Yes) {

                      ui->progressBar->setHidden(false);
                      ui->progressBar->setValue(0);

                      QTimer *timer = new QTimer(this);
                      connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
                      timer->start(tsvalue);


                      if (!keepbox)
                      cstring = getadb()+" shell pm uninstall " + package;
                      else
                      cstring = getadb()+" shell pm uninstall -k " + package;

                      logfile("uninstall: "+cstring);

                      QString command=RunProcess(cstring);


                      ui->progressBar->setHidden(true);

                      // logfile(cstring);

                      nMilliseconds = rtimer.elapsed();
                      logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


                      if (!command.contains("Success"))

                         {   logfile(command);
                          QMessageBox::critical(
                                      this,
                                     "",
                                      "Uninstall failed");
                        }
                          else
                      {
                            logfile(command);
                             QMessageBox::information(
                                      this,
                                      "",
                                      "Uninstalled");
                       }


                  }
}


/////////////////////////////////////////////////////////////////////////
void MainWindow::on_connButton_clicked()
{


    QString cstring;
    QString command;
    QString pkg1 = "package:com.amazon.device.software.ota";
    QString pkg2 = "package:com.amazon.dcp";


    if (isusb )
      {

          QMessageBox::critical(
               this,
               tr("adbLink"),
               tr("Inactive for USB connections"));
            return;
      }

    if (daddr.isEmpty())
    {

        QMessageBox::critical(
             this,
             tr("adbLink"),
             tr("Device address required."));
          return;
    }





    QElapsedTimer rtimer;
    int nMilliseconds;
    rtimer.start();


    QString sambastring;
    QString sambacheck;

      cstring = adb + " connect "+daddr+":"+port;
      command=RunProcess(cstring);
      logfile("connect"+command);
      logfile("");

    logfile("connection attempt");
    // logfile(cstring);
    logfile(command);


    if (command.contains("connected to"))
    {   isConnected=true;


           on_refreshConnectedDevices_clicked();


    }
       else
        isConnected=false;

     if(isConnected)
       {


         if (os == 0)
          QObject().thread()->usleep(1000*1000*.1);
          // patch from superelchi@xda


         ui->server_running->setText(adbstr1);
         serverRunning = true;

         if (is_su() && isConnected)
          {


             cstring = getadb() + " shell pm list packages -d";
             command=RunProcess(cstring);



         }

      }

     firstrun=false;
     nMilliseconds = rtimer.elapsed();
     logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );

}





////////////////////////////////////////////////////////////////
void MainWindow::on_disButton_clicked()
{



    if (isusb )
      {
          QMessageBox::critical(
               this,
               tr("adbLink"),
               tr("Inactive for USB connections"));
            return;
      }


    if (daddr.isEmpty())
    {

        QMessageBox::critical(
             this,
             tr("adbLink"),
             tr("Device address required."));
          return;
    }



    QElapsedTimer rtimer;
    int nMilliseconds;
    rtimer.start();


        ui->sambaLabel->setVisible(false);


         QString cstring = adb + " disconnect "+daddr+":"+port ;
         QString command=RunProcess(cstring);

         logfile("disconnect: "+daddr);
         // logfile(cstring);

        isConnected=false;



         //ui->update_status->setText("");
         //on_utilityButton_clicked();

         on_refreshConnectedDevices_clicked();
         nMilliseconds = rtimer.elapsed();
         logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


}


/////////////////////////////////////////////////////////////////////////
void MainWindow::on_actionAbout_triggered()
{


    Dialog2 dialog2;
    dialog2.setModal(true);
    dialog2.setvLabel(version);
    dialog2.exec();

}


//////////////////////////////////////////////
void MainWindow::on_actionHelp_triggered()
{
    logfile("opening help");
    helpDialog helpdialog;
    helpdialog.setModal(true);
    helpdialog.exec();
}



/////////////////////////////////////////////
void MainWindow::on_backupButton_clicked()
{



 QString lookup=daddr;
 QString cstring;
 QString command;
 QString mcpath;
 QString thpath;
 QString envpath;
 QString rootpath;
 QString thumbpath;



  if(!isusb)
   lookup=lookup+":"+port;

 isConnected=find_daddr(lookup);

 //if (!isConnected && !isusb)
       //on_connButton_clicked();

  if (!isConnected)
        { QMessageBox::critical(0,"",devstr2);
           return;
        }



    is_package(xbmcpackage);

   if (!is_packageInstalled)
      { QMessageBox::critical(
            this,
            "",
            xbmcpackage+" not installed");
         return;
       }


   backupDialog dialog;

    dialog.setadb_backup(getadb(),data_root);

    dialog.setModal(true);

if(dialog.exec() == QDialog::Accepted)
{

     QString n_data_root = dialog.return_data_root();

     if(!n_data_root.startsWith("/"))
        n_data_root.prepend("/");

     if(!n_data_root.endsWith("/"))
        n_data_root.append("/") ;


     thumbpath = dialog.returnthumb();

     rootpath=n_data_root+"Android/data/"+xbmcpackage;
     thumbpath=rootpath+filepath+"/userdata/";



   QElapsedTimer rtimer;
   int nMilliseconds;
   rtimer.start();



 QString hdir = QDir::homePath();


 mcpath = rootpath+filepath;

 cstring = getadb() + " shell ls "+mcpath;
 command=RunProcess(cstring);

 if (command.contains("No such file or directory"))
  {
    QMessageBox::critical(this,"","Kodi's files not found on "+n_data_root);
    logfile("backup result: "+command+"/n"+cstring);
    return;
 }


 cstring = getadb() + " shell ls "+thumbpath+"/Thumbnails";
 command=RunProcess(cstring);
 logfile("backup: "+command);
 if (command.contains("No such file or directory"))
  {
   logfile("Thumbnails not found");
   QMessageBox::critical(this,"","Thumbnails not found.  "+thumbpath );
   return;
 }


 QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Backup Destination"),
                                               hdir,
                                               QFileDialog::ShowDirsOnly
                                               | QFileDialog::DontResolveSymlinks);

if (!dir.isEmpty() )
 {
  QMessageBox::StandardButton reply;
   reply = QMessageBox::question(this, "Backup", "backup Kodi to "+dir,
                                 QMessageBox::Yes|QMessageBox::No);
   if (reply == QMessageBox::Yes)
   {
    logfile("backup function started");
       QString udir = dir+"/userdata";
       ui->progressBar->setHidden(false);
       ui->progressBar->setValue(0);

       QTimer *timer = new QTimer(this);
       connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
       timer->start(tsvalue);

       mcpath=mcpath+"/";
       dir = dir + "/";

       if (os == 1)
       {
           dir.replace("/","\\");
           udir.replace("/","\\");
       }


     


      

       cstring = getadb() + " pull "+mcpath+".  "+'"'+dir+'"';
       command=RunProcess(cstring);
       logfile("backup: "+cstring);




       QString dbfile=dir+"userdata/Database/Addons16.db";
       QString thfile=dir+"userdata/Thumbnails";
       QString udfile=dir+"userdata";

       if (!QDir(thfile).exists())
       {

           cstring = getadb() +  " pull "+thumbpath+" "+'"'+dir+'"'+"/userdata";
            command=RunProcess(cstring);
           logfile("backup: "+cstring);
           QFile::rename(dir+"/userdata/advancedsettings.xml", dir+"/userdata/advancedsettings.backup");

       }


        if  (QDir(udfile).exists())
         QMessageBox::information(this,"","Backup Complete!");
        else
          QMessageBox::critical(this,"","Backup Failed. See Log.");


   } //end of do backup
 } // end of !dir

nMilliseconds = rtimer.elapsed();
logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );
ui->progressBar->setHidden(true);


}  // end-dialog-accepted.

}  // end function

///////////////////////////////////////////
void MainWindow::on_fpushButton_clicked()

{
    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }

     if(!is_busybox())
     {
         QMessageBox::critical(0,"","Busybox installation failed.");
        return;
       }


     QElapsedTimer rtimer;
     int nMilliseconds;
     rtimer.start();

     if (data_root.isEmpty())
         data_root="/sdcard/";

    QString cstring;
    QString command;
    QString hidden;
    QString xpath = "";
    QString mcpath=data_root+ "/Android/data/"+xbmcpackage+filepath;

/*
    cstring = getadb() + " shell ls "+mcpath;

    command=RunProcess(cstring);

    if (command.contains("No such file or directory"))
     {
        QMessageBox::critical(
                    this,
                   "",
                    "Destination path missing");
                    return;
    }

*/

switch(ui->comboBox->currentIndex() ){
case 0:
xpath = mcpath+"/addons/";
break;

case 1:
xpath = mcpath+"/userdata/keymaps/";
break;

case 2:
xpath = mcpath+"/media/";
break;

case 3:
xpath = mcpath+"/sounds/";
break;

case 4:
xpath = mcpath+"/system/";
break;

case 5:
xpath = mcpath+"/userdata/";
break;

case 6:
xpath = mcpath+"/temp/";
break;

case 7:
xpath = "/sdcard/";
break;



default:
xpath = mcpath+"/addons/";
break;
}

QString cname = ui->comboBox->currentText();


QString dirpath = ui->customdir->text();
if (!dirpath.isEmpty())

{
    if(!dirpath.startsWith("/"))
       dirpath.prepend("/");

    if(!dirpath.endsWith("/"))
       dirpath.append("/") ;

       xpath=dirpath;
       cname = xpath;


}

 QString fileName = QFileDialog::getOpenFileName(this,
 "Push file to "+cname, pushdir, tr("Files (*)"));


 if (!fileName.isEmpty() )
 {

     QFileInfo finfo(fileName);
     pushdir = finfo.absolutePath();

     QString cstring = getadb() + " shell ls "+xpath;

     QString command=RunProcess(cstring);

     // logfile(cstring);

      if (command.contains("No such file or directory"))
       { QMessageBox::critical(
                      this,
                     "",
                      "Destination path missing. Check the Kodi partition setting in the device record, or run Kodi to set up internal folders.");
          logfile(xpath);
          logfile("Destination path missing. Check the Kodi partition setting in the device record, or run Kodi to set up internal folders.");
          return;
      }




     QMessageBox::StandardButton reply;
       reply = QMessageBox::question(this, "Push", "Push "+fileName+" to "+cname+"?",
           QMessageBox::Yes|QMessageBox::No);
       if (reply == QMessageBox::Yes) {


           ui->progressBar->setHidden(false);
           ui->progressBar->setValue(0);


           QTimer *timer = new QTimer(this);
           connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
           timer->start(tsvalue);

           cstring = getadb() + " push "+'"'+fileName+'"'+ " "+xpath;

           command=RunProcess(cstring);

           if (command.contains("bytes"))
            {
               // logfile(cstring);
               logfile(command);
               QMessageBox::information(
                           this,
                          "",
                          "File Pushed." );
           }
               else
           {
               // logfile(cstring);
               logfile(command);

               QMessageBox::critical(
                           this,
                           "",
                        "Push failed ");
           }

   }

}

 ui->progressBar->setHidden(true);
 nMilliseconds = rtimer.elapsed();
 logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );



}



/////////////////////////////////////////////////
void MainWindow::on_restoreButton_clicked()

{

    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }


    is_package(xbmcpackage);

   if (!is_packageInstalled)
      { QMessageBox::critical(
            this,
            "",
            xbmcpackage+" not installed");
         return;
   }


   QString cstring;
   QString command;
   QString rootpath;
   QString thumbpath;
   QString envpath;
   QString mcpath;



   cstring = cstring = getadb() +  " shell ps | grep "+xbmcpackage;
   command=RunProcess(cstring);


   if (command.contains(xbmcpackage))
      { QMessageBox::critical(this,"","Cannot restore while\n"+xbmcpackage+" is running!");
        logfile(xbmcpackage+" running. Restore failed");
        return;
       }




   restDialog dialog;

    dialog.setModal(true);

    dialog.setadb_restore(getadb());

   if(dialog.exec() == QDialog::Accepted)
   {



       data_root = dialog.restore_data_root();

       // QMessageBox::critical(0,"",data_root );


        if(!data_root.startsWith("/"))
          data_root.prepend("/");

       if(!data_root.endsWith("/"))
          data_root.append("/") ;




        rootpath=data_root+"Android/data/"+xbmcpackage;

          //QMessageBox::critical(this,"",rootpath);
          //return;


              envpath=rootpath+"/files/";
              mcpath=rootpath+filepath;



   QElapsedTimer rtimer;
   int nMilliseconds;
   rtimer.start();


// extra rms





 QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Backup Destination"),
  hdir,QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);




 if (!dir.isEmpty() )
 {


   if (!QDir(dir+"/userdata").exists() )

     {
       QMessageBox::critical(0,"","Invalid backup folder!" );
       return;
     }


 QMessageBox::StandardButton reply;
   reply = QMessageBox::question(this, "Restore", "Restore Kodi from "+dir+" to "+data_root+" ?"+"\nThis will overwrite the existing setup!",
                                 QMessageBox::Yes|QMessageBox::No);
   if (reply == QMessageBox::Yes) {


       ui->progressBar->setHidden(false);
       ui->progressBar->setValue(0);

       QTimer *timer = new QTimer(this);
       connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
       timer->start(tsvalue);


     // nuke existing

       cstring = getadb() + " shell rm -r /sdcard/Android/data/"+xbmcpackage;
       command=RunProcess(cstring);
       logfile(command);

       cstring = getadb() + " shell rm -r "+rootpath;
       command=RunProcess(cstring);
       logfile(command);

       cstring = getadb() + " shell ls "+mcpath;
       command=RunProcess(cstring);
       logfile(command);

       if (command.contains("No such file or directory"))
        {
           cstring = getadb() + " shell mkdir -p "+mcpath;
           command=RunProcess(cstring);
           logfile(command);
           QString errorp = command;
           cstring = getadb() + " shell ls "+mcpath;
           command=RunProcess(cstring);

           if (command.contains("No such file or directory"))
            {
               QMessageBox::critical(this,"","Error creating restore point");
               logfile("Restore error:"+ errorp);
               return;
             }

        } // nuke existing

       cstring = getadb() + " shell rm /sdcard/xbmc_env.properties";
       command=RunProcess(cstring);

       cstring = getadb() + " shell rm -r "+mcpath + "/*";

       command=RunProcess(cstring);

       cstring = getadb() + " push "+'"'+dir+'"'+ " "+mcpath;

        command=RunProcess(cstring);

        ui->progressBar->setHidden(true);

        // logfile(cstring);
        logfile(command);

        nMilliseconds = rtimer.elapsed();
        logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );



        if (command.contains("bytes"))

       {
           QMessageBox::information(
                       this,
                      "",
                      "Restore complete." );

           if (data_root != "/sdcard/")
             {
               cstring = getadb() + " shell echo xbmc.data="+envpath+" > /sdcard/xbmc_env.properties";
               command=RunProcess(cstring);
               logfile("create /sdcard/xbmc_env.properties");
               // logfile(cstring);
               logfile(command);
           }

        }
           else

       {

           QMessageBox::critical(
                       this,
                       "",
                    "Restore failed ");
       }




   }

}

}

}

//////////////////////////////////////////
void MainWindow::on_pushRemote_clicked()
{

    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

   // if (!isConnected && !isusb)
         // on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }



    is_package(xbmcpackage);

   if (!is_packageInstalled)
      { QMessageBox::critical(
            this,
            "",
            xbmcpackage+" not installed");
         return;
   }




QElapsedTimer rtimer;
int nMilliseconds;
rtimer.start();


if (data_root.isEmpty())
    data_root="/sdcard/";

QString cstring;
QString command;
QString hidden;
QString xpath = "";
QString mcpath=data_root+ "/Android/data/"+xbmcpackage+filepath;


cstring = getadb() + " shell ls "+mcpath;

command=RunProcess(cstring);

if (command.contains("No such file or directory"))
{
   QMessageBox::critical(
               this,
              "",
               "Destination path missing "+mcpath);
               return;
}

mcpath = mcpath+"/userdata/keymaps/";

cstring = getadb() + " shell ls "+mcpath;

command=RunProcess(cstring);

if (command.contains("No such file or directory"))
 {
   //// logfile(cstring);
   //logfile(command);

    QMessageBox::critical(
                this,
               "",
                "Destination path missing");
                return;
}




 QString fileName = QFileDialog::getOpenFileName(this,
 "Choose remote xml file", xmldir, tr("Files (*.xml)"));

 if (!fileName.isEmpty() )
 {


     QMessageBox::StandardButton reply;
       reply = QMessageBox::question(this, "Push", fileName+" selected. Continue?",
           QMessageBox::Yes|QMessageBox::No);
       if (reply == QMessageBox::Yes) {


           cstring = getadb() + " push "+'"'+fileName+'"'+ " "+mcpath+"/keyboard.xml";

           command=RunProcess(cstring);

           // logfile(cstring);
           logfile("push remote:"+command);

           nMilliseconds = rtimer.elapsed();
           logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );



           if (command.contains("bytes"))


           {

               QMessageBox::information(
                           this,
                          "",
                          "Remote xml installed." );
           }
               else

           {

               QMessageBox::critical(
                           this,
                           "",
                        "Remote xml installation failed.");}


   }

}

}

////////////////////////////////////////////////
void MainWindow::on_adbshellButton_clicked()
{

  // PATH=$PATH:/data/local/tmp

   QString lookup=daddr;

    if(!isusb)
     lookup=lookup+":"+port;

   isConnected=find_daddr(lookup);

  // if (!isConnected && !isusb)
      //   on_connButton_clicked();

    if (!isConnected)
          { QMessageBox::critical(0,"",devstr2);
             return;
          }


    if(!is_busybox())
    {
        QMessageBox::critical(0,"","Busybox installation failed.");
       return;
    }



    description = ui->deviceBox->currentText();
    getRecord(description);





    logfile("detaching console process");
    logfile(daddr+":"+port);

    QString cstring = "";


    if (os == 1)

       {

       if (isusb)
           { cstring = "cmd /k  adb -s "+daddr+" shell";
             // logfile(cstring);
              QProcess::startDetached(cstring);
            }
        else
          {   cstring = "cmd /k  adb -s "+daddr+":"+port+ " shell";
              // logfile(cstring);
              QProcess::startDetached(cstring);
           }
     }


     else

       {

        QString commstr = adbdir+"console.sh";
        QFile::remove(commstr);
        QFile file(commstr);



                 if(!file.open(QFile::WriteOnly))

             {
                logfile("error creating console.sh!");
                 QMessageBox::critical(this,"","Error creating command file!");
                 return;
             }



       QTextStream out(&file);

       out  << "#!/bin/sh" << endl;




       out  <<  getadb()+ " shell " << endl;
       cstring = getadb()+ " shell";
       // logfile(cstring);

             file.flush();
             file.close();

       cstring = "chmod 0755 " + commstr ;
       QString command=RunProcess(cstring);

      //  cstring = "gnome-terminal -e "+adbdir+"console.sh";
      //  cstring = "x-terminal-emulator -e "+adbdir+"console.sh";

       if (os == 0)
         cstring = "x-terminal-emulator -e "+adbdir+"console.sh";
       if (os == 2)
       cstring = "open -a Terminal.app "+adbdir+"console.sh";



        QProcess::startDetached(cstring);
        }


}


//////////////////////////////////////////////////
void MainWindow::getpackage()
{

logfile("opening getpackage dialog");

    mediacenterDialog dialog;

    if(dialog.exec() == QDialog::Accepted)
    {
      xbmcpackage = dialog.xbmcpackageName();
      filepath = dialog.filepath();
    }

} // end getpackage





////////////////////////////////////////////////////////////////////////////////
void MainWindow::on_actionReboot_triggered()
{

     QString cstring;

     QString lookup=daddr;

      if(!isusb)
       lookup=lookup+":"+port;

     isConnected=find_daddr(lookup);

    // if (!isConnected && !isusb)
          // on_connButton_clicked();

      if (!isConnected)
            { QMessageBox::critical(0,"",devstr2);
               return;
            }




   QMessageBox::StandardButton reply;
     reply = QMessageBox::question(this, "Reboot Device", "Reboot Device?",
         QMessageBox::Yes|QMessageBox::No);
     if (reply == QMessageBox::Yes) {
         isConnected=false;
         //ui->device_connected->setText(devstr2);
         ui->update_status->setText("");
        logfile("rebooting device");
        rebootDevice(" reboot");
     }

}

///////////////////////////////////////////////////////////////////////////////////
void MainWindow::on_actionRecovery_triggered()
{
    QString cstring;
    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

  //  if (!isConnected && !isusb)
       //   on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }




   QMessageBox::StandardButton reply;
     reply = QMessageBox::question(this, "", "Reboot Recovery?",
         QMessageBox::Yes|QMessageBox::No);
     if (reply == QMessageBox::Yes) {
         isConnected=false;
         //ui->device_connected->setText(devstr2);
         ui->update_status->setText("");
         logfile("rebooting device recovery");
         rebootDevice(" reboot recovery");
        }

}


//////////////////////////////////////////////////////
void MainWindow::on_actionInstall_busybox_triggered()
{

    if (!isConnected)
       { QMessageBox::critical(
             this,
             tr("adbLink"),
             tr("Device not connected"));
          return;
    }



   if (!is_su())
      { QMessageBox::critical(
            this,
            "",
            "Root required!");
         return;
   }


   QElapsedTimer rtimer;
   int nMilliseconds;
   rtimer.start();


   QMessageBox::StandardButton reply;
         reply = QMessageBox::question(this, "", "Install Mount Tools?",
            QMessageBox::Yes|QMessageBox::No);
         if (reply == QMessageBox::No)
         return;


         ui->progressBar->setHidden(false);
         ui->progressBar->setValue(0);


         QTimer *timer = new QTimer(this);
         connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
         timer->start(tsvalue);

    logfile("starting systools install");

    mount_system("rw");

    QString busybox1 = adbdir+"busybox";

    QString busybox5 = adbdir+"xbin.tar";

    QString cstring = getadb() + " shell ls /data/local/tmp/adblink";
    QString command=RunProcess(cstring);


    if (command.contains("No such file or directory"))
       {
        cstring = getadb() + " shell mkdir -p /data/local/tmp/adblink";
        command=RunProcess(cstring);
       }



    QFile Fout1(busybox1);

         if(!Fout1.exists())
            {

            QMessageBox::critical(
            this,
            tr("adbLink"),
            busybox1+" not found.");

            logfile(busybox1+" not found.");
            ui->progressBar->setHidden(true);
            return;
             }



      QFile Fout5(busybox5);

      if(!Fout5.exists())
         {

           QMessageBox::critical(
            this,
            tr("adbLink"),
             busybox5+" not found.");
           logfile(busybox5+" not found.");
           ui->progressBar->setHidden(true);
            return;
          }



      cstring = getadb() + " push "+busybox1+ " "+busypath;
      command=RunProcess(cstring);

         if (!command.contains("bytes"))
           { QMessageBox::critical(
            this,
             "",
             "file1: mount tools install failed ");
             logfile("file1: mount tools install failed ");
             // logfile(cstring);
              logfile(command);
              ui->progressBar->setHidden(true);
             return;
             }



         // logfile(cstring);
         logfile(command);




                 cstring = getadb() + " push "+busybox5+ " "+busypath;

                 command=RunProcess(cstring);

                 if (!command.contains("bytes"))
                    { QMessageBox::critical(
                                 this,
                                 "",
                                 "file5: mount tools install failed");

                     logfile("file5: mount tools install failed ");
                     // logfile(cstring);
                     logfile(command);
                     ui->progressBar->setHidden(true);
                     return;
                    }

                 // logfile(cstring);
                 logfile(command);




     cstring = getadb() + " shell chmod 0755 "+busypath+"busybox";
     command=RunProcess(cstring);

     // logfile(cstring);
     logfile(command);



     cstring = getadb() + " shell "+ busypath+"busybox tar xf "+busypath+"xbin.tar -C /"+busypath;
     command=RunProcess(cstring);

     // logfile(cstring);
     logfile(command);

     cstring = getadb() + " shell su -c chmod 0755 "+ busypath+"*.sh";
     command=RunProcess(cstring);

     // logfile(cstring);
     logfile(command);


     cstring = getadb() + " shell chmod 0755 "+busypath+"02mntdrives";
     command=RunProcess(cstring);
     // logfile(cstring);
     logfile(command);


     cstring = getadb() + " shell chmod 0755 "+busypath+"mount.exfat-fuse";
     command=RunProcess(cstring);
     // logfile(cstring);
     logfile(command);

     cstring = getadb() + " shell chmod 0755 "+busypath+"ntfs-3g";
     command=RunProcess(cstring);
     // logfile(cstring);
     logfile(command);


     //cstring = getadb() + " shell "+busypath+"/binstall.sh";
     //command=RunProcess(cstring);

     // logfile(cstring);
     logfile(command);

      cstring = getadb() + " shell ls "+busypath+"mntdrives.sh";
      command=RunProcess(cstring);

      // logfile(cstring);
      logfile(command);

        if (command.contains("No such file or directory"))
          { logfile("systools install failed!");
            QMessageBox::critical( this,"","Mount Tools not installed!");
        }

        else
        {

          // logfile(cstring);
               logfile(command);
               cstring = getadb() + " shell rm "+ busypath+"xbin.tar";
               command=RunProcess(cstring);
               QMessageBox::information( this,"","Mount Tools installed!");
               logfile("systools installed");
               ui->progressBar->setHidden(false);

}

mount_system("ro");
nMilliseconds = rtimer.elapsed();
logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );
ui->progressBar->setHidden(true);

}




///////////////////////////////////////////////////////
void MainWindow::on_actionUninstall_Busybox_triggered()
{

    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

   // if (!isConnected && !isusb)
      //    on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }



   if (!is_su())
      { QMessageBox::critical(
            this,
            "",
            "Root required!");
         return;
   }

   QString cstring = getadb() + " shell ls /data/local/tmp/adblink/mntdrives.sh";
   QString command=RunProcess(cstring);


   if (command.contains("No such file or directory"))
      {
       QMessageBox::critical(this,"","Mount tools not installed");
       logfile("system tools not installed");
       return;
      }





   QString umntstring = busypath+"busybox umount /storage/usb/drive*/";
   QString rmsd = "rm -rf /storage/usb/drive*/";
   QString rmsh = "rm /system/etc/install-recovery-2.sh";



   QMessageBox::StandardButton reply;
         reply = QMessageBox::question(this, "Mount Tools", "Uninstall Mount Tools?\nThis will unmount drives mounted by adbLink and\nremove their mountpoint.",
            QMessageBox::Yes|QMessageBox::No);
         if (reply == QMessageBox::No)
         return;


         ui->progressBar->setHidden(false);
         ui->progressBar->setValue(0);

         QTimer *timer = new QTimer(this);
         connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
         timer->start(tsvalue);

         QElapsedTimer rtimer;
         int nMilliseconds;
         rtimer.start();

         logfile("mount uninstall");

         mount_system("rw");


          cstring = getadb() + " shell su -c "+busypath+"buninstall.sh";
          command=RunProcess(cstring);

          // logfile(cstring);
          logfile(command);



        //  cstring = getadb() + " shell su -c ls /storage/usb/drive*/";
        // command=RunProcess(cstring);

 /*
          if (!command.contains("No such file or directory"))

        {
             mount_root("rw");
             // logfile(cstring);
             logfile(command);

             cstring = getadb() + " shell su -c " + umntstring;
             command=RunProcess(cstring);;

             // logfile(cstring);
             logfile(command);

         cstring = getadb() + " shell su -c " + rmsh;
         command=RunProcess(cstring);;

         // logfile(cstring);
         logfile(command);



          cstring = getadb() + " shell su -c " + rmsd;
          command=RunProcess(cstring);

          // logfile(cstring);
          logfile(command);

          mount_root("ro");

      }

*/

      mount_system("ro");



    nMilliseconds = rtimer.elapsed();
    logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


    QMessageBox::information( this,"","Mount Tools uninstalled!");
    logfile("system tools uninstalled!");
    ui->progressBar->setHidden(true);


}

/////////////////////////////////////////////
void MainWindow::on_fdellButton_clicked()
{

    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

    // if (!isConnected && !isusb)
          // on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }


    if(!is_busybox())
    {
        QMessageBox::critical(0,"","Busybox installation failed.");
       return;
      }


    QElapsedTimer rtimer;
    int nMilliseconds;
    rtimer.start();




    if (data_root.isEmpty())
        data_root="/sdcard/";


     QString xpath = "";
     QString cname = ui->comboBox->currentText();
     QString fileName;
     QString pullfile;
     QString cstring;
    QString command;
    QString hidden;
    QString mcpath=data_root+ "/Android/data/"+xbmcpackage+filepath;

/*
     cstring = getadb() + " shell ls "+mcpath;

     command=RunProcess(cstring);

     if (command.contains("No such file or directory"))
      {
         QMessageBox::critical(
                     this,
                    "",
                     "Destination path missing");
                     return;
     }

*/

       // QMessageBox::critical(this,"",xbmcpackage);

       switch(ui->comboBox->currentIndex() ){
       case 0:
       xpath = mcpath+"/addons/";
       break;

       case 1:
       xpath = mcpath+"/userdata/keymaps";
       break;

       case 2:
       xpath = mcpath+"/media/";
       break;

       case 3:
       xpath = mcpath+"/sounds/";
       break;

       case 4:
       xpath = mcpath+"/system/";
       break;

       case 5:
       xpath = mcpath+"/userdata/";
       break;

       case 6:
       xpath = mcpath+"/temp/";
       break;

       case 7:
       xpath = "/sdcard/";
       break;

       default:
       xpath = mcpath+"/addons/";
       break;
       }


    QString dirpath = ui->customdir->text();
       if (!dirpath.isEmpty())

       {
           if(!dirpath.startsWith("/"))
              dirpath.prepend("/");

           if(!dirpath.endsWith("/"))
              dirpath.append("/") ;

              xpath=dirpath;
              cname = xpath;
       }




  cstring = getadb() + " shell "+busypath+"busybox find " +xpath+ " -type f ";

  // cstring = getadb() + " shell ls " +xpath;

  command=RunProcess(cstring);

  if (command.isEmpty() || command.contains("No such file or directory"))
     { QMessageBox::critical(this,"","No files found");

      // logfile(cstring);
      logfile(command);
      logfile("no files found!");
      return;
      }

  QFile file21(adbdir+"temp.txt");

        if(!file21.open(QFile::WriteOnly))
    {

        logfile(adbdir+"temp.txt");
        logfile("error creating file");
        QMessageBox::critical(this,"","Error creating file!");
        return;
    }


    QTextStream out1(&file21);
    out1  << command << endl;

    file21.flush();
    file21.close();

  usbfileDialog sddialog;
  sddialog.setModal(true);
  sddialog.setData("Select file to delete");
  if(sddialog.exec() == QDialog::Accepted)
  pullfile = sddialog.binfileName();
  else return;

  if (pullfile.isEmpty())
     {
      QMessageBox::critical(this,"","No file selected");
      return;
      }


  QMessageBox::StandardButton reply3;
    reply3 = QMessageBox::question(this, "", "Delete "+pullfile,
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply3 == QMessageBox::No)
        return;

             
             // cstring = getadb() + " shell rm "+pullfile;
                cstring = getadb() + " shell rm "+'"'+pullfile+'"';
             //   cstring = getadb() + " push "+'"'+fileName+'"'+ " "+xpath;



             command=RunProcess(cstring);

             if (command.contains("exist"))
              {
                 // logfile(cstring);
                 logfile(command);
                 logfile( "Deletion failed");
                 QMessageBox::critical(
                             this,
                            "",
                             "Deletion failed");}
                 else
                  {
                    // logfile(cstring);
                    logfile(command);
                    logfile("Deletion succeeded");
                    QMessageBox::information(
                             this,
                             "",
                             "Deletion succeeded");}


 nMilliseconds = rtimer.elapsed();
 logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


}

//////////////////////////////////////////////////////
void MainWindow::on_actionFirmware_install_triggered()
{






    // recovery-stock-51.1.0.img

    bool usbstick = false;
    QString cstring;
    QString command;
    QString updatezip = "--update_package=/cache/update.zip";
    QString commstr = adbdir+"command";
    QString tmpstr = adbdir+"tmpstr";


    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

    // if (!isConnected && !isusb)
          // on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }


     if (!check_dep_menu())
         {
           QMessageBox::critical(0,"","Not supported on this device.");
           return;
          }



   if (!is_su())
      { QMessageBox::critical(
            this,
            "",
            "Root required!");
         return;
   }



 logfile("firmware installation query");

 QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "", "Install Firmware?",
                                 QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::No)
      {logfile("firmware installation cancelled");
        return;}


    QElapsedTimer rtimer;
     int nMilliseconds;

    rtimer.start();



    logfile("firmware installation started");


        cstring = getadb() + " shell su -c chmod 777 /cache";
        command=RunProcess(cstring);

        cstring = getadb() + " shell su -c chmod 777 /cache/recovery";
        command=RunProcess(cstring);


        if (command.contains("No such file or directory"))
         {

            // logfile(cstring);
            logfile(command);
            logfile("/cache/recovery/ not found");

            cstring = getadb() + " shell su -c mkdir -p /cache/recovery/";
            command=RunProcess(cstring);

            // logfile(cstring);
            logfile(command);

            if (!command.isEmpty())
             {

                QMessageBox::critical(this,"","Firmware installation aborted. See log.");
                logfile("Firmware installation aborted.");
                return;
             }



            cstring = getadb() + " shell su -c chmod 777 /cache/recovery";
            command=RunProcess(cstring);

            // logfile(cstring);
            logfile(command);

            if (!command.isEmpty())
             {  logfile("chmod error. cancelling firmware installation");
                QMessageBox::information( this,"","Error: "+command);
                return; }


        }




    QFile file(commstr);

        //if(!file.open(QFile::WriteOnly |
         //             QFile::Text))

       if(!file.open(QFile::WriteOnly))

        {

            // logfile(cstring);
            logfile(command);
            logfile("error creating command file. cancelling firmware installation.");
            QMessageBox::critical(this,"","Error creating command file!");
            return;
        }


        QTextStream out(&file);
        out  << updatezip << endl;

        file.flush();
        file.close();



    cstring = getadb() + " push "+commstr+ " "+tempdir;
    command=RunProcess(cstring);
    
    if (!command.contains("bytes"))
     { QMessageBox::information( this,"","Error: "+command);

        // logfile(cstring);
        logfile(command);
        logfile("error pushing command file. cancelling firmware installation.");

        return; }

    cstring = getadb() + " shell su -c cp " + tempdir+"command /cache/recovery/";
    command=RunProcess(cstring);

    if (!command.isEmpty())
     { QMessageBox::information( this,"","Error: "+command);

        // logfile(cstring);
        logfile(command);
        logfile("error cp command file. cancelling firmware installation.");

        return; }

    // logfile(cstring);
    logfile(command);

    cstring = getadb() + " shell su -c chmod 777 /cache/recovery/command";
    command=RunProcess(cstring);

    if (!command.isEmpty())
     { QMessageBox::information( this,"","Error: "+command);

        // logfile(cstring);
        logfile(command);
        logfile("error chmod command file. cancelling firmware installation.");

        return; }

    // logfile(cstring);
    logfile(command);

    QString fileName;

    QMessageBox::StandardButton reply2;
      reply2 = QMessageBox::question(this, "", "Are firmware files on usb storage?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply2 == QMessageBox::Yes)
         {

          logfile("searching usb for files");

          cstring = getadb() + " shell su -c "+busypath+"busybox find /storage/usb -name *.bin -o -name *.zip";
          command=RunProcess(cstring);

          if (command.isEmpty())
             { QMessageBox::critical(this,"","No files found");

              // logfile(cstring);
              logfile("no files found");
              return;
              }


          // logfile(cstring);
          logfile(command);

          QFile file21(adbdir+"temp.txt");

           // if(!file21.open(QFile::WriteOnly |
             //             QFile::Text))

          if(!file21.open(QFile::WriteOnly))

            {
                QMessageBox::critical(this,"","Error creating file!");

                // logfile(cstring);
                logfile(command);
                logfile("error creating "+adbdir+ "temp.txt");
                return;
            }


            QTextStream out1(&file21);
            out1  << command << endl;

            file21.flush();
            file21.close();



          usbfileDialog sddialog;
          sddialog.setModal(true);
          sddialog.setData("Select firmware file");
          if(sddialog.exec() == QDialog::Accepted)
          fileName = sddialog.binfileName();
          else return;


          if (fileName.isEmpty())
             {
              QMessageBox::critical(this,"","No file selected");

              logfile("no file selected");
              return;
              }



          usbstick = true;
          cstring = getadb() + " shell ls "+fileName;
          command=RunProcess(cstring);

          if (command.contains("No such file or directory"))
           {

              // logfile(cstring);
              logfile("no such file or directory");
              QMessageBox::critical(this,"","Error: "+command);
              return;
          }

          }

         else

      {
          usbstick = false;
          fileName = QFileDialog::getOpenFileName(this,
          "Choose firmware file", hdir, tr("Files (*)"));

      }



    if (!fileName.isEmpty() )
    {

     ui->progressBar->setHidden(false);
     ui->progressBar->setValue(0);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
    timer->start(tsvalue);

    if (!usbstick)
      {
        logfile("pushing "+fileName+" to "+tempdir);
        cstring = getadb() + " push "  + '"' +   fileName + '"'   + " "+tempdir+"update.zip";
        command=RunProcess(cstring);

        // logfile(cstring);
        logfile(command);

        if (!command.contains("bytes"))
        {
          logfile("pushing "+fileName+" to "+tempdir+" failed. Cancelling firmware installation");
           return;
        }

      }


    if (!usbstick)
    cstring = getadb() + " shell su -c cp " + " "+tempdir+"update.zip /cache/";
    else
    cstring = getadb() + " shell su -c cp " + fileName + " /cache/update.zip";

    command=RunProcess(cstring);

    if (!command.isEmpty())
    {

     nMilliseconds = rtimer.elapsed();
     logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );

      logfile("cp of firmware file to /cache failed. Cancelling firmware installation");
       return;
    }

    
   if (!usbstick)
   {
    cstring = getadb() + " shell rm "+tempdir+"update.zip";
    command=RunProcess(cstring);
    // logfile(cstring);
    logfile(command);

   }

   // logfile(cstring);
   logfile(command);



    cstring = getadb() + " shell rm "+tempdir+"command";
    command=RunProcess(cstring);

    // logfile(cstring);
    logfile(command);


    QFile::remove(commstr);
    QFile Fout(commstr);

    if(Fout.exists())
    {
        QMessageBox::critical(this,"","Error: rm of PC: "+commstr+" script");
        logfile("Error: rm of PC: "+commstr+" script");
    }



    ui->progressBar->setHidden(true);

    nMilliseconds = rtimer.elapsed();
   logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


    QMessageBox::StandardButton reply3;
      reply3 = QMessageBox::question(this, "", "Reboot to recovery?\nFirmware:"+fileName,
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply3 == QMessageBox::No)
       {

          logfile("firmware installation cancelled by user");

          cstring = getadb() + " shell su -c rm /cache/update.zip";
          command=RunProcess(cstring);

          // logfile(cstring);
          logfile(command);

          cstring = getadb() + " shell su -c rm /cache/recovery/command";
          command=RunProcess(cstring);


          // logfile(cstring);
          logfile(command);

          return;

       }

      logfile("rebooting to recovery");

      rebootDevice(" reboot recovery");
     
     isConnected=false;
     //ui->device_connected->setText(devstr2);

    }


}


//////////////////////////////////////////////
void MainWindow::on_mntButton_clicked()
{

    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }



     if (!is_su())
        { QMessageBox::critical(
              this,
              "",
              "Root required!");
           return;
     }


     if(!is_system_tools())
     {
         QMessageBox::critical(0,"","Mount Tools not installed");
        return;
       }




   QElapsedTimer rtimer;
   int nMilliseconds;
   rtimer.start();



QString cstring;
QString command;
QString sambacheck;
QString sambastring;

   ui->progressBar->setHidden(false);
   ui->progressBar->setValue(0);

   QTimer *timer = new QTimer(this);
   connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
   timer->start(tsvalue);


     if (is_os5())
         {
          cstring = getadb() + " shell su -c  /system/bin/setenforce 0";
          command=RunProcess(cstring);

          cstring = getadb() + " shell su -c  /system/bin/getenforce";
          command=RunProcess(cstring);

          if (!command.contains("Permissive"))
            { // logfile(cstring);
              logfile(command);
              logfile("Problem setting SELinux permissive");
              QMessageBox::critical( this,"","Problem setting SELinux Permissive");
               return;
          }

      }


       cstring = getadb() + " shell su -c "+busypath+"/mntdrives.sh";
       command=RunProcess(cstring);

       // logfile(cstring);
       logfile(command);


       ui->progressBar->setHidden(true);
       logfile(command);
       if (command.isEmpty()  || command.contains("FUSE"))
        {
           QMessageBox::information( this,"","USB drive(s) mounted");

           logfile("USB drive(s) mounted");
           // logfile(cstring);
           logfile(command);

           return;


}




       if (command.contains("resource busy"))
        {
           QMessageBox::information( this,"","USB drive already mounted");

           logfile("USB drive already mounted");
           // logfile(cstring);
           logfile(command);

           return;
        }


       if (!command.isEmpty() && !command.contains("Permissive"))
        {
           // logfile(cstring);
           logfile(command);
           logfile("error mounting usb drive");
           QMessageBox::information( this,"","Error: "+command);
           return;
        }



       nMilliseconds = rtimer.elapsed();
       logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );



}


//////////////////////////////////////////
void MainWindow::on_umntButton_clicked()
{

    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);


     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }


   if (!is_su())
      { QMessageBox::critical(
            this,
            "",
            "Root required!");
         return;
   }


   if(!is_system_tools())
   {
       QMessageBox::critical(0,"","Mount Tools not installed");
      return;
     }



   QElapsedTimer rtimer;
   int nMilliseconds;
   rtimer.start();






   QString cstring = getadb() + " shell ls /system/bin/setenforce";
   QString command=RunProcess(cstring);

   if (!command.contains("No such file or directory"))
      {
       cstring = getadb() + " shell su -c  /system/bin/setenforce 1";
       command=RunProcess(cstring);

       cstring = getadb() + " shell su -c  /system/bin/getenforce";
       command=RunProcess(cstring);

       if (!command.contains("Enforcing"))
         { // logfile(cstring);
           logfile(command);
           logfile("Problem setting SELinux enforcement");
           QMessageBox::critical( this,"","error setting SELinux Enforcement");
       }

   }




        ui->progressBar->setHidden(false);
        ui->progressBar->setValue(0);

        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
        timer->start(tsvalue);

    QString umntstring = "/system/bin/umount /storage/usb/*/";
    QString rmsd = "rm -r /storage/usb/*/";


    mount_root("rw");

       logfile("stopping samba");
       cstring = getadb() + " shell su -c /data/data/com.funkyfresh.samba/files/samba-rc stop";
       command=RunProcess(cstring);

       logfile("samba off!");
       ui->sambaLabel->setVisible(false);

       // logfile(cstring);
       logfile(command);

       cstring = getadb() + " shell su -c " + umntstring;
       command=RunProcess(cstring);

        ui->progressBar->setHidden(true);

       if (command.contains("failed"))
         { // logfile(cstring);
           logfile(command);
           logfile("error unmounting usb drive");
           QMessageBox::critical( this,"","USB drive not found!");}
       else
        {           
           cstring = getadb() + " shell su -c " + rmsd;
           command=RunProcess(cstring);
           QMessageBox::information( this,"","USB Drive(s) unmounted.");
           // logfile(cstring);
           logfile(command);
           logfile("usb drive unmounted");
        }

 mount_root("ro");

 nMilliseconds = rtimer.elapsed();
 logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


}


////////////////////////////////////////
void MainWindow::on_rwButton_clicked()
{
    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

   // if (!isConnected && !isusb)
       //   on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }




   //

   if (!is_su())
      { QMessageBox::critical(
            this,
            "",
            "Root required!");
         return;
   }


   QElapsedTimer rtimer;
   int nMilliseconds;
   rtimer.start();



   if (mount_system("rw"))

      {

       logfile("filesystem remounted r/w");
       QMessageBox::information(
                   this,
                  "",
                   "Filesystem mounted r/w");}
    else

   {

       logfile("filesystem not remounted!");
       QMessageBox::critical(
                      this,
                     "",
                      "Error: Filesystem not remounted r/w!");}


   nMilliseconds = rtimer.elapsed();
   logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


}

////////////////////////////////////////
void MainWindow::on_roButton_clicked()
{
    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

    //if (!isConnected && !isusb)
       //   on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }





 //

   if (!is_su())
      { QMessageBox::critical(
            this,
            "",
            "Root required!");
         return;
   }


   QElapsedTimer rtimer;
   int nMilliseconds;
   rtimer.start();




   if (mount_system("ro"))
    {

       logfile("filesystem remounted r/o");

       QMessageBox::information(
                   this,
                  "",
                   "Filesystem mounted r/o");}
    else

   {
       logfile("filesystem not remounted r/o!");
       QMessageBox::critical(
                      this,
                     "",
                      "Error: Filesystem not remounted r/o!");}


   nMilliseconds = rtimer.elapsed();
   logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


}



/////////////////////////////////////////
void MainWindow::on_fpullButton_clicked()
{

    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);


     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }


    if(!is_busybox())
    {
        QMessageBox::critical(0,"","Busybox installation failed.");
       return;
    }



       if (!QDir(pulldir).exists())
         {  QMessageBox::critical(
             this,
             "adbLink",
             "Pull directory not found");
          return ;
       }



    QElapsedTimer rtimer;
    int nMilliseconds;
    rtimer.start();


    if (data_root.isEmpty())
        data_root="/sdcard/";


     QString xpath = "";
     QString cname = ui->comboBox->currentText();    
     QString fileName;
     QString cstring;
    QString command;
    QString hidden;
    QString mcpath=data_root+ "/Android/data/"+xbmcpackage+filepath;


   /*
   cstring = getadb() + " shell ls "+mcpath;

     command=RunProcess(cstring);

     if (command.contains("No such file or directory"))
      {
         QMessageBox::critical(
                     this,
                    "",
                     "Destination path missing");
                     return;
     }

*/



       switch(ui->comboBox->currentIndex() ){
       case 0:
       xpath = mcpath+"/addons/";
       break;

       case 1:
       xpath = mcpath+"/userdata/keymaps/";
       break;

       case 2:
       xpath = mcpath+"/media/";
       break;

       case 3:
       xpath = mcpath+"/sounds/";
       break;

       case 4:
       xpath = mcpath+"/system/";
       break;

       case 5:
       xpath = mcpath+"/userdata/";
       break;

       case 6:
       xpath = mcpath+"/temp/";
       break;

       case 7:
       xpath = "/sdcard/";
       break;

       default:
       xpath = mcpath+"/addons/";
       break;
       }



     QString dirpath = ui->customdir->text();
     if (!dirpath.isEmpty())

     {
         if(!dirpath.startsWith("/"))
            dirpath.prepend("/");

         if(!dirpath.endsWith("/"))
            dirpath.append("/") ;

            xpath=dirpath;


     }





     cstring = getadb() + " shell "+busypath+"busybox find " +xpath+ " -type f ";

     // cstring = getadb() + " shell ls " +xpath;

     command=RunProcess(cstring);


     if (command.isEmpty() || command.contains("No such file or directory"))
        { QMessageBox::critical(this,"","No files found");

         // logfile(cstring);
         logfile(command);
         logfile("no files found!");
         return;
         }


     QFile file21(adbdir+"temp.txt");

       //if(!file21.open(QFile::WriteOnly |
       //              QFile::Text))

     if(!file21.open(QFile::WriteOnly))

       {
           QMessageBox::critical(this,"","Error creating file!");
           logfile("error creating file: "+adbdir+"temp.txt");

           return;
       }


       QTextStream out1(&file21);
       out1  << command << endl;

       file21.flush();
       file21.close();



     usbfileDialog sddialog;
     sddialog.setModal(true);
     sddialog.setData("Select file to pull");
     if(sddialog.exec() == QDialog::Accepted)
     fileName = sddialog.binfileName();
     else return;

     if (fileName.isEmpty())
        {
         QMessageBox::critical(this,"","No file selected");
         logfile("no file selected");
         return;
         }


     // QMessageBox::critical(this,"",xpath+"\n"+fileName);



     ui->progressBar->setHidden(false);
     ui->progressBar->setValue(0);


     QTimer *timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
     timer->start(tsvalue);


             // cstring = getadb() + " pull "+xpath+fileName+" " +'"'+pulldir+'"';

             cstring = getadb() + " pull "+'"'+fileName+'"'+" "+'"'+pulldir+'"';
             command=RunProcess(cstring);
             logfile(command);
             //QMessageBox::critical(this,"",command);


             if (!command.contains("bytes"))
              {

                 logfile("pull failed");
                 QMessageBox::critical(
                             this,
                            "",
                             "Pull failed");}
                 else
             {

                 logfile("pull succeeded");
                 QMessageBox::information(
                             this,
                             "",
                             "Pull succeeded");}

             ui->progressBar->setHidden(true);
             nMilliseconds = rtimer.elapsed();
             logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


}


/////////////////////////////////////////
void MainWindow::on_donate_clicked()
{
    QString link = "https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=JA5E5UP3ZSWBN";
   QDesktopServices::openUrl(QUrl(link));

    //QString link = "http://www.jocala.com/tr.apk";
    //QDesktopServices::openUrl(QUrl(link));

}

///////////////////////////////////////////////
void MainWindow::on_actionCredits_triggered()
{
    creditsDialog credits;
    credits.setModal(true);
    credits.exec();
}



///////////////////////////////////////////////
void MainWindow::check_update_status()
{

    QString command;
    QString cstring;
    QString pkg;

     if ( !is_su())
      { ui->update_status->setText("");
         return;
     }

    if (is_su() && isConnected)
     {


      cstring = getadb() + " shell pm list packages -d";
      command=RunProcess(cstring);



        if (is_os5())
            {
           pkg="com.amazon.device.software.ota";
            }

            else
            {
               pkg="com.amazon.dcp";
             }


        /*

       if (command.contains(pkg))
          {
           ui->update_status->setText(amazon_update0);
           updatecheck = false;
          }

       else
         {
              ui->update_status->setText(amazon_update1);
              updatecheck = true;
         }
*/


    }

}


/////////////////////////////////////////////////////////
void MainWindow::on_actionInstall_Recovery_triggered()
{





    QString cstring;
    QString command;
    QString fileName;

    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

    // if (!isConnected && !isusb)
         //  on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }

     if (!check_dep_menu())
         {
           QMessageBox::critical(0,"","Not supported on this device.");
           return;
          }



   if (!is_su())
      { QMessageBox::critical(
            this,
            "",
            "Root required!");
         return;
   }


   if (!is_system_tools())
   {
       QMessageBox::critical(this,"","System Tools not installed");
       logfile("System Tools not installed");
       return;
   }






   cstring = getadb() + " shell su -c cat /system/build.prop | grep 51.1.1.0";
   command=RunProcess(cstring);

   if (!command.isEmpty())
      { QMessageBox::critical(this,"","Downgrade firmware below 51.1.1.0 first!");
       logfile("firmware downgrade below 51.1.1.0 required for CWM recovery install");
       // logfile(cstring);
       return;
       }

   logfile("cwm recovery installation starts");


    QElapsedTimer rtimer;
     int nMilliseconds;

    rtimer.start();

    logfile("recovery installation started");

          fileName = QFileDialog::getOpenFileName(this,
          "Choose Clockwork Mod Image", recoverydir, tr("Files (*.img)"));

          if (!fileName.isEmpty() )
          {

      QMessageBox::StandardButton reply;
         reply = QMessageBox::question(this, "", "Install Clockwork Mod?\n\n"+fileName,
                                      QMessageBox::Yes|QMessageBox::No);
         if (reply == QMessageBox::No)
           {logfile("recovery installation cancelled");
             return;}


     ui->progressBar->setHidden(false);
     ui->progressBar->setValue(0);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
    timer->start(tsvalue);

        logfile("pushing "+fileName+" to "+tempdir);
        cstring = getadb() + " push "  + '"' +   fileName + '"'   + tempdir+"recovery.img";
        command=RunProcess(cstring);

        // logfile(cstring);
        logfile(command);

        if (!command.contains("bytes"))
        {
          logfile("pushing "+fileName+" to "+tempdir+" failed. Cancelling firmware installation");
           return;
        }



    cstring=getadb() + " shell su -c  dd if="+tempdir+"recovery.img of=/dev/block/platform/msm_sdcc.1/by-name/recovery";
    command=RunProcess(cstring);
    // logfile(cstring);
    logfile(command);



 if (!command.contains("bytes transferred"))
 {
   logfile("recovery installation failed");
   // logfile(cstring);
   logfile(command);
   QMessageBox::critical(this,"","Error: "+command);

 }


     cstring = getadb() + " shell rm "+tempdir+"recovery.img";
     command=RunProcess(cstring);
     // logfile(cstring);
     logfile(command);

   nMilliseconds = rtimer.elapsed();
   logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );
   ui->progressBar->setHidden(true);

   QMessageBox::information(this,"","New Recovery Installed");


    }

}



/////////////////////////////////////////////////
void MainWindow::on_actionInstall_SSH_triggered()

{

QString lookup=daddr;

   if(!isusb)
    lookup=lookup+":"+port;

  isConnected=find_daddr(lookup);

   if (!isConnected)
         { QMessageBox::critical(0,"",devstr2);
            return;
         }




  QMessageBox::StandardButton reply;
   reply = QMessageBox::question(0, "", "Install OpenSSH?",
           QMessageBox::Yes|QMessageBox::No);
     if (reply == QMessageBox::No)
      {
         return;
       }




  QString sshfile = adbdir+"sshelper.apk";

  bool file1 = false;


                     QElapsedTimer rtimer;
                     int nMilliseconds;
                     rtimer.start();



                     QFile Fout1(sshfile);

                     if(!Fout1.exists())
                     {

                         QMessageBox::critical(
                            this,
                            tr("adbLink"),
                            sshfile+" not found.");
                            logfile(sshfile+" not found.");

                            return;
                     }


                           ui->progressBar->setHidden(false);
                           ui->progressBar->setValue(0);

                           QTimer *timer = new QTimer(this);
                           connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
                           timer->start(tsvalue);

                           QString cstring = getadb() + " install -r "+sshfile;

                         QString command=RunProcess(cstring);

                           if (!command.contains("Success"))
                              {
                               // logfile(cstring);
                               logfile(command);
                               QMessageBox::information(
                                           this,
                                           "",
                                           "sshelper.apk install failed");
                                ui->progressBar->setHidden(true);
                                return;
                              }

                           else
                               file1 = true;



                                  // logfile(cstring);
                                  logfile(command);

if (file1)
{

QMessageBox::information( this,"","OpenSSH installed.\nRun SSHelper on your\nmedia device to finish setup.");
logfile("openssh installed");
ui->progressBar->setHidden(true);
nMilliseconds = rtimer.elapsed();
logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


}

}







/*

/////////////////////////////////////////////////
void MainWindow::on_actionInstall_SSH_triggered()
{

    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

   // if (!isConnected && !isusb)
       //   on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }






   if (!is_su())
      { QMessageBox::critical(
            this,
            "",
            "Root required!");
         return;
   }


   if (is_os5())
   {
       QMessageBox::critical(this,"","Not available for OS 5");
       return;
   }



   QString cstring;
   QString command;


   cstring = getadb() + " shell ls /system/xbin/mntdrives.sh";
   command=RunProcess(cstring);

   // logfile(cstring);
   logfile(command);

     if (command.contains("No such file or directory"))
       { logfile("system tools not installed!");
         QMessageBox::critical( this,"","System Tools not installed!");
         return;
     }



// /data/jocala/ssh/dropbear -A root -N root -s -g -R /data/jocala/ssh/.ssh/authorized_keys

   cstring = getadb() + " shell ls /system/xbin/ntfs-3g";
   command=RunProcess(cstring);


     if (command.contains("No such file or directory"))
      { QMessageBox::critical( this,"","System Tools required for SSH. Install from the Root Menu.");

         // logfile(cstring);
         logfile(command);
         logfile("System tools required for SSH.");
         return;
     }



   logfile("ssh installation query");

   QMessageBox::StandardButton reply1;
      reply1 = QMessageBox::question(this, "", "Install SSH?",
                                   QMessageBox::Yes|QMessageBox::No);
      if (reply1 == QMessageBox::No)
        {logfile("ssh installation cancelled");
          return;}


      QElapsedTimer rtimer;
         int nMilliseconds;
         rtimer.start();

         ui->progressBar->setHidden(false);
         ui->progressBar->setValue(0);


         QTimer *timer = new QTimer(this);
         connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
         timer->start(tsvalue);


          logfile("starting ssh install");


   cstring = getadb() + " push "+adbdir+ "/ssh.tar /sdcard/";
   command=RunProcess(cstring);


   if (!command.contains("bytes"))
      { QMessageBox::critical(
                   this,
                   "",
                   "SSH install failed");
       logfile("ssh.tar: ssh install failed ");
       // logfile(cstring);
       logfile(command);
       ui->progressBar->setHidden(true);
       return;
      }

   mount_system("rw");

   cstring = getadb() + " shell su -c "+busypath+"busybox tar xf /sdcard/ssh.tar -C /data";
   command=RunProcess(cstring);

   // logfile(cstring);
   logfile(command);

cstring = getadb() + " shell su -c rm /sdcard/ssh.tar";
command=RunProcess(cstring);

// logfile(cstring);
logfile(command);


cstring = getadb() + " shell su -c /data/jocala/ssh/setupssh";
command=RunProcess(cstring);

// logfile(cstring);
logfile(command);



cstring = getadb() + " shell ls /data/jocala/ssh/sshstart";
command=RunProcess(cstring);
// logfile(cstring);
logfile(command);

if (command.contains("No such file or directory"))
   { QMessageBox::critical(
                this,
                "",
                "SSH not installed");
    logfile("ssh check not passed");

   }

else

   { QMessageBox::information(
                this,
                "",
                "SSH installed");
    logfile("ssh check passed");
    // logfile(cstring);
    logfile(command);

       }

nMilliseconds = rtimer.elapsed();
logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );

ui->progressBar->setHidden(true);
mount_system("ro");

}

*/


////////////////////////////////////////////////////
void MainWindow::on_actionUninstall_SSH_triggered()
{

   return;

    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

   // if (!isConnected && !isusb)
        //  on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }


     if (!check_dep_menu())
         {
           QMessageBox::critical(0,"","Not supported on this device.");
           return;
          }


   if (!is_su())
      { QMessageBox::critical(
            this,
            "",
            "Root required!");
         return;
   }





   QString cstring;
   QString command;

   cstring = getadb() + " shell su -c /data/jocala/ssh/sshstop";
   command=RunProcess(cstring);
   // logfile(cstring);
   logfile(command);;


   if (command.contains("not found"))
      { QMessageBox::critical(
                   this,
                   "",
                   "SSH not installed");
       logfile("ssh check");
       // logfile(cstring);
       logfile(command);
       mount_system("ro");
       return;
      }


   logfile("ssh uninstallation query");

   QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "", "Uninstall SSH?",
                                   QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::No)
        {logfile("ssh uninstall cancelled");
          return;}


   mount_system("rw");



       logfile("uninstall ssh");

       cstring = getadb() + " shell su -c /data/jocala/ssh/rmssh";
       command=RunProcess(cstring);

       cstring = getadb() + " shell su -c rm -r /data/jocala/";
       command=RunProcess(cstring);



       cstring = getadb() + " shell sshstatus";
       command=RunProcess(cstring);




       if (command.contains("not found"))
          { QMessageBox::critical(
                       this,
                       "",
                       "SSH uninstalled");
           logfile("ssh check");
           // logfile(cstring);
           logfile(command);




          }


     mount_system("ro");

}



////////////////////////////////////////////////

void MainWindow::on_actionDownload_Kodi_triggered()
{
    logfile("opening video help");
    kodiDialog kodidialog;
    kodidialog.setModal(true);
    kodidialog.exec();
}

/////////////////////////////////////////////

void MainWindow::on_editRecord_clicked()
{

    int row;
      description = ui->deviceBox->currentText();

     if (!description.isEmpty())
      {


         QString lookup=daddr;

          if(!isusb)
           lookup=lookup+":"+port;

         isConnected=find_daddr(lookup);

       // if (!isConnected && !isusb)
           //   on_connButton_clicked();



         row = ui->deviceBox->currentIndex();
         getRecord(description);
         dataentry(0);
         loaddevicebox();
         ui->deviceBox->setCurrentIndex(row);
     }




}


////////////////////////////////////////////////////////////
void MainWindow::on_actionInstall_Stock_Recovery_triggered()
{

// fix



    QString cstring;
    QString command;
    QString fileName;

    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

    // if (!isConnected && !isusb)
        //  on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }


     if (!check_dep_menu())
         {
           QMessageBox::critical(0,"","Not supported on this device.");
           return;
          }



   if (!is_su())
      { QMessageBox::critical(
            this,
            "",
            "Root required!");
         return;
   }


   if (!is_busybox())
   {
       QMessageBox::critical(this,"","System tools not installed");
       logfile("system tools not installed");
       return;
   }






   logfile("stock recovery installation starts");


    QElapsedTimer rtimer;
     int nMilliseconds;

    rtimer.start();

    logfile("recovery installation started");

          fileName = QFileDialog::getOpenFileName(this,
          "Choose Stock Recovery Image", stkrecoverydir, tr("Files (*.img)"));

          if (!fileName.isEmpty() )
          {

      QMessageBox::StandardButton reply;
         reply = QMessageBox::question(this, "", "Install Stock Recovery?\n\n"+fileName,
                                      QMessageBox::Yes|QMessageBox::No);
         if (reply == QMessageBox::No)
           {logfile("recovery installation cancelled");
             return;}


     ui->progressBar->setHidden(false);
     ui->progressBar->setValue(0);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
    timer->start(tsvalue);

        logfile("pushing "+fileName+" to /sdcard/");
        cstring = getadb() + " push "  + '"' +   fileName + '"'   + " /sdcard/recovery.img";
        command=RunProcess(cstring);

        // logfile(cstring);
        logfile(command);

        if (!command.contains("bytes"))
        {
          logfile("pushing "+fileName+" to /sdcard/ failed. Cancelling firmware installation");
           return;
        }



    cstring=getadb() + " shell su -c  dd if=/sdcard/recovery.img of=/dev/block/platform/msm_sdcc.1/by-name/recovery";
    command=RunProcess(cstring);
    // logfile(cstring);
    logfile(command);



 if (!command.contains("bytes transferred"))
 {
   logfile("recovery installation failed");
   // logfile(cstring);
   logfile(command);
   QMessageBox::critical(this,"","Error: "+command);

 }


     cstring = getadb() + " shell rm /sdcard/recovery.img";
     command=RunProcess(cstring);
     // logfile(cstring);
     logfile(command);

   nMilliseconds = rtimer.elapsed();
   logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );
   ui->progressBar->setHidden(true);

   QMessageBox::information(this,"","New Recovery Installed");


    }

}

////////////////////////////////////////////////////
void MainWindow::on_actionInstall_Samba_triggered()
{

// fix

    QString cstring;
    QString command;


    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

   // if (!isConnected && !isusb)
        //  on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }






   if (!is_su())
      { QMessageBox::critical(
            this,
            "",
            "Root required!");
         return;
   }


   cstring = getadb() + " shell ls "+busypath+"mntdrives.sh";
   command=RunProcess(cstring);

   // logfile(cstring);
   logfile(command);

     if (command.contains("No such file or directory"))
       { logfile("system tools not installed!");
         QMessageBox::critical( this,"","System Tools not installed!");
         return;
     }


   QElapsedTimer rtimer;
   int nMilliseconds;
   rtimer.start();


   QMessageBox::StandardButton reply;
         reply = QMessageBox::question(this, "Samba", "Install Samba?",
            QMessageBox::Yes|QMessageBox::No);
         if (reply == QMessageBox::No)
         return;


         ui->progressBar->setHidden(false);
         ui->progressBar->setValue(0);


         QTimer *timer = new QTimer(this);
         connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
         timer->start(tsvalue);

    logfile("starting samba install");

    QString busybox2 = adbdir+"samba.tar";

        QFile Fout2(busybox2);

       if(!Fout2.exists())
          {

            QMessageBox::critical(
             this,
             tr("adbLink"),
              busybox2+" not found.");
            logfile(busybox2+" not found.");
            ui->progressBar->setHidden(true);
             return;
           }





              cstring = getadb() + " push "+busybox2+ " /data/local/tmp/";
              command=RunProcess(cstring);


              if (!command.contains("bytes"))
                 { QMessageBox::critical(
                              this,
                              "",
                              "samba install failed");
                  logfile("samba install failed ");
                  // logfile(cstring);
                  logfile(command);
                  ui->progressBar->setHidden(true);
                  return;
                 }

      mount_system("rw");



            cstring = getadb() + " shell su -c "+busypath+"tar xf /data/local/tmp/samba.tar -C /data/data";
            command=RunProcess(cstring);

            // logfile(cstring);
            logfile(command);


            cstring = getadb() + " shell su -c ln -s /data/data/com.funkyfresh.samba/files/samba "+busypath+"samba";
            command=RunProcess(cstring);

            // logfile(cstring);
            logfile(command);

            cstring = getadb() + " shell su -c ln -s /data/data/com.funkyfresh.samba/files/smb.conf "+busypath+"smb.conf";
            command=RunProcess(cstring);

            // logfile(cstring);
            logfile(command);
            cstring = getadb() + " shell su -c rm /data/local/tmp/samba.tar";
            command=RunProcess(cstring);


         QMessageBox::information( this,"","Samba installed");
         logfile("samba installed");
         ui->progressBar->setHidden(false);


mount_system("ro");



nMilliseconds = rtimer.elapsed();
logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );

ui->progressBar->setHidden(true);


}

/////////////////////////////////////////////////////
void MainWindow::on_actionUninstall_Samba_triggered()
{

// fix


    QString cstring;
    QString command;


    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

    // if (!isConnected && !isusb)
         // on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }





   if (!is_su())
      { QMessageBox::critical(
            this,
            "",
            "Root required!");
         return;
   }



cstring = getadb() + " shell ls "+busypath+"mntdrives.sh";
command=RunProcess(cstring);

// logfile(cstring);
logfile(command);

  if (command.contains("No such file or directory"))
    { logfile("System Tools required");
      QMessageBox::critical( this,"","System Tools not installed!");
      return;
  }

  cstring = getadb() + " shell ls /data/data/com.funkyfresh.samba/files/jocala.txt";
  command=RunProcess(cstring);

  // logfile(cstring);
  logfile(command);

    if (command.contains("No such file or directory"))
      { logfile("System Tools required");
        QMessageBox::critical( this,"","Samba not installed!");
        return;
    }


   QElapsedTimer rtimer;
   int nMilliseconds;
   rtimer.start();


   QMessageBox::StandardButton reply;
         reply = QMessageBox::question(this, "Samba", "Uninstall Samba?",
            QMessageBox::Yes|QMessageBox::No);
         if (reply == QMessageBox::No)
         return;


         ui->progressBar->setHidden(false);
         ui->progressBar->setValue(0);


         QTimer *timer = new QTimer(this);
         connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
         timer->start(tsvalue);


      mount_system("rw");


      cstring = getadb() + " shell ls /data/data/com.funkyfresh.samba/files/jocala.txt";
      command=RunProcess(cstring);

      // logfile(cstring);
      logfile(command);


        if (command.contains("No such file or directory"))
          { logfile("System Tools required");
            QMessageBox::critical( this,"","Samba not installed!");
            return;
          }
        else
          {


            cstring = getadb() + " shell "+busypath+"samba stop";
            command=RunProcess(cstring);

            // logfile(cstring);
            logfile(command);

            cstring = getadb() + " shell su -c rm -r "+busypath+"samba";
            command=RunProcess(cstring);

            // logfile(cstring);
            logfile(command);

            cstring = getadb() + " shell su -c rm -r /data/data/com.funkyfresh.samba";
            command=RunProcess(cstring);

            // logfile(cstring);
            logfile(command);
          }




         QMessageBox::information( this,"","Samba uninstalled!");
         logfile("samba uninstalled!");
         ui->progressBar->setHidden(false);


mount_system("ro");



nMilliseconds = rtimer.elapsed();
logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );

ui->progressBar->setHidden(true);



}


////////////////////////////////////////////////////
void MainWindow::on_actionInstallBootmenu_triggered()
{

// fix


    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

    // if (!isConnected && !isusb)
       //   on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }


     if (!check_dep_menu())
         {
           QMessageBox::critical(0,"","Not supported on this device.");
           return;
          }



   if (!is_su())
      { QMessageBox::critical(
            this,
            "",
            "Root required!");
         return;
   }






 QString bootmenu = adbdir+"bootmenu.img";


  if (!fileExists(bootmenu))
  { QMessageBox::critical(
               this,
               "",
               "bootmenu.img not found!");
   logfile("bootmenu.img not found!");
   return;
  }



 QString cstring = getadb() + " shell ls /system/boot/";
 QString command=RunProcess(cstring);
 bool agree;

if (!command.contains("No such file or directory"))
  {

    { QMessageBox::critical(
                 this,
                 "",
                 "Boot Menu already installed");

     logfile("Boot Menu already installed");
     // logfile(cstring);
     logfile(command);
     return;
    }
}


/*

#!/system/bin/sh
mount -o remount,rw /system
mkdir /system/boot
dd if=/dev/block/platform/msm_sdcc.1/by-name/boot of=/system/boot/boot.img
cp /system/boot/boot.img /system/boot/original.img
mount -o remount,ro /system
dd if=/sdcard/bootmenu.img of=/dev/block/platform/msm_sdcc.1/by-name/boot
rm /sdcard/bootmenu.img
bytes transferred
 */



    bootmenuDialog dialog;
    dialog.setModal(true);

    if(dialog.exec() == QDialog::Accepted)
    {

       agree=dialog.bagreeBox();

       if (!agree)
           return;



       cstring = getadb() + " push " + bootmenu + " /sdcard/";
       command=RunProcess(cstring);

       if (!command.contains("bytes"))
          { QMessageBox::critical(
                       this,
                       "",
                       "Copy of Boot Menu to /sdcard failed");

           logfile("Copy of Boot Menu to /sdcard failed");
           // logfile(cstring);
           logfile(command);
           return;
          }



       // logfile(cstring);
       logfile(command);

       mount_system("rw");

       cstring = getadb() +" shell su -c mkdir -p /system/boot";
       command=RunProcess(cstring);

       // logfile(cstring);
       logfile(command);

        cstring = getadb() +" shell su -c dd if=/dev/block/platform/msm_sdcc.1/by-name/boot of=/system/boot/boot.img";
        command=RunProcess(cstring);

        // logfile(cstring);
        logfile(command);

        if (!command.contains("bytes transferred"))
           { QMessageBox::critical(
                        this,
                        "",
                        "dd process failed - kernel not copied to /system/boot");

            logfile("dd process failed - kernel not copied to /system/boot");
            mount_system("ro");
            return;
           }


        cstring = getadb() +" shell su -c cp /system/boot/boot.img /system/boot/original.img";
        command=RunProcess(cstring);

        // logfile(cstring);
        logfile(command);

        cstring = getadb() +" shell su -c dd if=/sdcard/bootmenu.img of=/dev/block/platform/msm_sdcc.1/by-name/boot";
        command=RunProcess(cstring);

        // logfile(cstring);
        logfile(command);

        if (!command.contains("bytes transferred"))
           { QMessageBox::critical(
                        this,
                        "",
                        "dd process failed - bootmenu not installed");

            logfile("dd process failed - bootmenu not installed");
            mount_system("ro");
            return;

        }

        QMessageBox::information(
                       this,
                      "",
                       "Bootmenu installed.");

          mount_system("ro");


    }


    cstring = getadb() +" shell rm /sdcard/bootmenu.img";
    command=RunProcess(cstring);



}

//////////////////////////////////////////////////////////
void MainWindow::on_actionUninstall_Boot_Menu_triggered()
{







    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

    // if (!isConnected && !isusb)
         // on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }


     if (!check_dep_menu())
         {
           QMessageBox::critical(0,"","Not supported on this device.");
           return;
          }


   if (!is_su())
      { QMessageBox::critical(
            this,
            "",
            "Root required!");
         return;
   }






 QString cstring = getadb() + " shell ls /system/boot/original.img";
 QString command=RunProcess(cstring);
 bool uagree;


if (command.contains("No such file or directory"))
  {

    { QMessageBox::critical(
                 this,
                 "",
                 "Original kernel not found!");

     // logfile(cstring);
     logfile(command);
     return;
    }
}


    unbootDialog dialog;
    dialog.setModal(true);

    if(dialog.exec() == QDialog::Accepted)
    {

       uagree=dialog.uagreeBox();

       if (!uagree)
           return;


       cstring = getadb() +" shell su -c dd if=/system/boot/original.img  of=/dev/block/platform/msm_sdcc.1/by-name/boot";
       command=RunProcess(cstring);

       // logfile(cstring);
       logfile(command);

       if (!command.contains("bytes transferred"))
          { QMessageBox::critical(
                       this,
                       "",
                       "dd process failed - kernel not copied to system");

           logfile("dd process failed - kernel not copied to system");
           mount_system("ro");
           return;




       }

       QMessageBox::information(
                      this,
                     "",
                      "Bootmenu uninstalled.");

        mount_system("ro");
    }


}



////////////////////////////////////////////////////////
void MainWindow::external_thumb()
{


    if (!isConnected)
       { QMessageBox::critical(
             this,
             tr("adbLink"),
             tr("Device not connected"));
          return;
    }


    QString cstring;
    QString command;

    QString root = externalLocation;
    externalLocation=externalLocation + "Android/data/";

    cstring = getadb() +" shell ls "+root;
    command=RunProcess(cstring);

    if (command.contains("No such file or directory"))
      {

            QMessageBox::critical(
                         this,
                         tr("adbLink"),
                         tr("Root path missing"));

                 // logfile(cstring);
                 logfile(command);

                return;

       }



    int i =  filepath.indexOf(".");
    QString hidden = filepath.mid(i);


    QString l1 = "<advancedsettings>";
    QString l2 = "  <pathsubstitution>";
    QString l3 = "    <substitute>";
    QString l4 = "       <from>special://profile/Thumbnails/</from>";
    QString l5 = "        <to>"+externalLocation+xbmcpackage+"/Thumbnails/</to>";
    QString l6 = "     </substitute>";
    QString l7 = "   </pathsubstitution>";
    QString l8 = "</advancedsettings>";



    QString mvpath;
    QString mcpath = "/sdcard/Android/data/"+xbmcpackage+filepath;


    cstring = getadb() + " shell ls "+mcpath;

    command=RunProcess(cstring);

    if (command.contains("No such file or directory"))
     {

        QMessageBox::critical(
                    this,
                   "",
                    "Internal Kodi directory missing");
                    return;
    }



    cstring = getadb() +" shell ls "+externalLocation+ xbmcpackage +"/Thumbnails";
    command=RunProcess(cstring);

    if (command.contains("No such file or directory"))
      {
       mvpath = externalLocation+"mcfiles/"+hidden;
       }

       else
       {
        mvpath = externalLocation+"mcfiles/";
       }



        cstring = getadb() +" shell ls "+mvpath+"/Thumbnails";
        command=RunProcess(cstring);

        if (!command.contains("No such file or directory"))
          {
             QMessageBox::critical(
                         this,
                         tr("adbLink"),
                         tr("Thumnails already moved"));

                 // logfile(cstring);
                 logfile(command);

                return;
      }

// reset mvpath.

 mvpath = externalLocation+"mcfiles/"+hidden;


QMessageBox::StandardButton reply1;
reply1 = QMessageBox::question(this, "", "Move Thumbnails to external storage?",
                            QMessageBox::Yes|QMessageBox::No);
if (reply1 == QMessageBox::No)
 {
   return;}


QElapsedTimer rtimer;
int nMilliseconds;
rtimer.start();

              QString filename1 = "advancedsettings.xml";
              QString filename2 = adbdir+filename1;

              cstring = getadb() + " shell ls "+mcpath+"/userdata/"+filename1;
              command=RunProcess(cstring);

              // logfile(cstring);
              logfile(command);

               if (!command.contains("No such file or directory"))
                  {
                   logfile("advancedsettings.xml exists");

                   QMessageBox::StandardButton reply;
                    reply = QMessageBox::question(this, "XML", "advancedsettings.xml exists. Overwrite?\n(will backup original)",
                                                  QMessageBox::Yes|QMessageBox::No);
                    if (reply == QMessageBox::No) {
                        logfile("abort xml write");
                        return;
                       } else {

                       cstring = getadb() + " shell mv "+mcpath+"/userdata/"+filename1+" "+mcpath+"/userdata/"+filename1+".backup";
                       command=RunProcess(cstring);
                       // logfile(cstring);
                       logfile(command);



                    }
                   }  // end if exists





    QFile file(filename2);


    if(!file.open(QFile::WriteOnly))
         {
           logfile("error creating advancedsettings.xml.");
           QMessageBox::critical(this,"","Unknown error creating xml file!");
            return;
          }

           QTextStream out(&file);

           out  << l1 << endl;
           out  << l2 << endl;
           out  << l3 << endl;
           out  << l4 << endl;
           out  << l5 << endl;
           out  << l6 << endl;
           out  << l7 << endl;
           out  << l8 << endl;


           file.flush();
           file.close();



    ui->progressBar->setHidden(false);
    ui->progressBar->setValue(0);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
    timer->start(tsvalue);

    cstring = getadb() +" shell mkdir -p "+externalLocation+xbmcpackage;
    command=RunProcess(cstring);

    // logfile(cstring);
    logfile(command);

    cstring = getadb() +" shell cp -R /sdcard/Android/data/"+xbmcpackage+filepath+"/userdata/Thumbnails " + externalLocation+xbmcpackage;
    command=RunProcess(cstring);


    // logfile(cstring);
    logfile(command);


    cstring = getadb() +" shell ls "+externalLocation+ xbmcpackage +"/Thumbnails";
    command=RunProcess(cstring);

    if (command.contains("No such file or directory"))
      {
        QMessageBox::critical(this,"","Error copying Thumbnails. See Log.");
        return;
       }




    cstring = getadb() + " push "+filename2+ " "+mcpath+"/userdata/"+filename1;
    command=RunProcess(cstring);

    // logfile(cstring);
    logfile(command);


    if (!command.contains("bytes"))
        {
          // logfile(cstring);
          logfile(command);
          logfile("error pushing xml script to device!");
          QMessageBox::critical(this,"","Error pushing xml from PC to device!");
          return;
        }

    cstring = getadb() +" shell rm -r /sdcard/Android/data/"+xbmcpackage+filepath+"/userdata/Thumbnails";
    command=RunProcess(cstring);
    // logfile(cstring);
    logfile(command);


   if (fileExists(filename2))
     QFile::remove(filename2);

   nMilliseconds = rtimer.elapsed();
   logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


  ui->progressBar->setHidden(true);



  QMessageBox::information(
                 this,
                "",
                 "Thumbnails moved to external storage");

}



////////////////////////////////////////////////////////
void MainWindow::internal_thumb()
{


    if (!isConnected)
       { QMessageBox::critical(
             this,
             tr("adbShield"),
             tr("Device not connected"));
          return;
    }


    QString cstring;
    QString command;
    QString mvpath;
    QString userdatapath = "/sdcard/Android/data/"+xbmcpackage+filepath+"/userdata/";

    QString root = externalLocation;
    externalLocation=externalLocation + "Android/data/";

    cstring = getadb() +" shell ls "+root;
    command=RunProcess(cstring);

    if (command.contains("No such file or directory"))
      {

            QMessageBox::critical(
                         this,
                         tr("adbLink"),
                         tr("Root path missing"));

                 // logfile(cstring);
                 logfile(command);

                return;

       }



    int i =  filepath.indexOf(".");
    QString hidden = filepath.mid(i);



       cstring = getadb() +" shell ls "+externalLocation+xbmcpackage+"/Thumbnails";
       command=RunProcess(cstring);

       if (command.contains("No such file or directory"))
         {
           QMessageBox::critical(this,"","Thumbnails not found.");
           return;
          }

          else
          {
           mvpath = externalLocation+xbmcpackage;
          }




    cstring = getadb() + " shell ls "+userdatapath;

    command=RunProcess(cstring);

    if (command.contains("No such file or directory"))
     {

        QMessageBox::critical(
                    this,
                   "",
                    "userdata directory missing");
                    return;
    }


QMessageBox::StandardButton reply1;
reply1 = QMessageBox::question(this, "", "Move Thumbnails to internal storage?",
                            QMessageBox::Yes|QMessageBox::No);
if (reply1 == QMessageBox::No)
 {
   return;}


QElapsedTimer rtimer;
int nMilliseconds;
rtimer.start();

              QString filename1 = "advancedsettings.xml";
              QString filename2 = adbdir+filename1;

              cstring = getadb() + " shell ls "+userdatapath+filename1;
              command=RunProcess(cstring);

              // logfile(cstring);
              logfile(command);

               if (!command.contains("No such file or directory"))
                  {
                   logfile("advancedsettings.xml exists. renamed.");



                       cstring = getadb() + " shell mv "+userdatapath+filename1+" "+userdatapath+"advancedsettings.backup";
                       command=RunProcess(cstring);
                       // logfile(cstring);
                       logfile(command);


                   }  // end if exists


    ui->progressBar->setHidden(false);
    ui->progressBar->setValue(0);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
    timer->start(tsvalue);


    cstring = getadb() +" shell cp -R "+mvpath+"/Thumbnails "+userdatapath;
    command=RunProcess(cstring);


    // logfile(cstring);
    logfile(command);


    cstring = getadb() + " shell ls "+userdatapath+"/Thumbnails";
    command=RunProcess(cstring);

    if (!command.contains("No such file or directory"))
     {
        cstring = getadb() +" shell rm -r "+mvpath;
        command=RunProcess(cstring);
        // logfile(cstring);
        logfile(command);

    }

   if (fileExists(filename2))
     QFile::remove(filename2);

   nMilliseconds = rtimer.elapsed();
   logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


  ui->progressBar->setHidden(true);



  QMessageBox::information(
                 this,
                "",
                 "Thumbnails moved to internal storage\nadvancedsettings.xml renamed.");

}



////////////////////////////////////////////////////////
void MainWindow::data_external()
{


    if (!isConnected)
       { QMessageBox::critical(
             this,
             tr("adbShield"),
             tr("Device not connected"));
          return;
    }

    QString cstring;
    QString command;

    QString mcfiles=xbmcpackage+"/files/";
    QString root = externalLocation;
    externalLocation=externalLocation + "Android/data/";

    //QMessageBox::critical(0,"",root);

    cstring = getadb() +" shell ls "+root;
    command=RunProcess(cstring);

    if (command.contains("No such file or directory"))
      {

            QMessageBox::critical(
                         this,
                         tr("adbFiles"),
                         tr("Root path missing"));

                 // logfile(cstring);
                 logfile(command);

                return;

       }

    int i =  filepath.indexOf(".");
    QString hidden = filepath.mid(i);

   cstring = getadb() +" shell ls /sdcard/xbmc_env.properties";
   command=RunProcess(cstring);

    if (!command.contains("No such file or directory"))
       {

          QMessageBox::critical(
                this,
                 tr("adbLink"),
                   tr("xbmc_env.properties already exists!"));

                // logfile(cstring);
                 logfile(command);

               return;

               }

    cstring = getadb() +" shell ls "+externalLocation+"/mcfiles/"+hidden;
    command=RunProcess(cstring);

    if (!command.contains("No such file or directory"))
      {

            QMessageBox::critical(
                         this,
                         tr("adbFiles"),
                         tr("Data found at external location. Already moved?"));

                 // logfile(cstring);
                 logfile(command);

                return;

       }

    QMessageBox::StandardButton reply1;
       reply1 = QMessageBox::question(this, "", "Move Kodi data to "+externalLocation+"?",
                                    QMessageBox::Yes|QMessageBox::No);
       if (reply1 == QMessageBox::No)
         {
           return;}

logfile("Moving kodi data to external storage");

   QElapsedTimer rtimer;
   int nMilliseconds;
   rtimer.start();

    ui->progressBar->setHidden(false);
    ui->progressBar->setValue(0);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
    timer->start(tsvalue);

    cstring = getadb() +" shell mkdir -p "+externalLocation+mcfiles;
    command=RunProcess(cstring);

   // cstring = getadb() +" shell cp -R /sdcard/Android/data/"+xbmcpackage+"/files/"+hidden + " /"+ externalLocation+mcfiles;

    cstring = getadb() +" shell cp -R /sdcard/Android/data/"+xbmcpackage + " /"+ externalLocation+"/";

    command=RunProcess(cstring);

    // logfile(cstring);
    logfile(command);


    data_root = root;
    updateRoot();

    cstring = getadb() + " shell echo xbmc.data="+externalLocation+mcfiles+ " > /sdcard/xbmc_env.properties";
    command=RunProcess(cstring);

    // logfile(cstring);
    logfile(command);

    cstring = getadb() +" shell rm -r /sdcard/Android/data/"+xbmcpackage+"/files/";
    command=RunProcess(cstring);

    // logfile(cstring);
    logfile(command);

  ui->progressBar->setHidden(true);

  nMilliseconds = rtimer.elapsed();
  logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


  QMessageBox::information(
                 this,
                "",
                 "Data moved to external storage");

}

/////////////////////////////////////////////////////////
void MainWindow::data_internal()
{

    if (!isConnected)
       { QMessageBox::critical(
             this,
             tr("adbLink"),
             tr("Device not connected"));
          return;
    }


    // /mnt/shell/emulated
    // /storage/usbdrive

    QString cstring;
    QString command;
    QString mcfiles= xbmcpackage +"/files/";
    QString root = externalLocation;
    externalLocation=externalLocation + "Android/data/";

    int i =  filepath.indexOf(".");
    QString hidden = filepath.mid(i);


    cstring = getadb() +" shell ls "+root;
    command=RunProcess(cstring);

    if (command.contains("No such file or directory"))
      {

            QMessageBox::critical(
                         this,
                         tr("adbFiles"),
                         tr("Root path missing"));

                 // logfile(cstring);
                 logfile(command);

                return;

       }



    cstring = getadb() +" shell ls "+externalLocation+mcfiles+hidden;
    command=RunProcess(cstring);

    if (command.contains("No such file or directory"))
      {

            QMessageBox::critical(0,"","Kodi data not found   "+cstring);

                 // logfile(cstring);
                 logfile(command);

                return;

       }




    cstring = getadb() +" shell ls /sdcard/Android/data/"+xbmcpackage+filepath;
    command=RunProcess(cstring);

    if (!command.contains("No such file or directory"))
      {

            QMessageBox::critical(0,"","Kodi data has already been restored");

                 // logfile(cstring);
                 logfile(command);

                return;

       }


    QMessageBox::StandardButton reply1;
       reply1 = QMessageBox::question(this, "", "Move Kodi data to internal storage?",
                                    QMessageBox::Yes|QMessageBox::No);
       if (reply1 == QMessageBox::No)
         {
           return;}

logfile("Moving kodi data to internal storage");

       QElapsedTimer rtimer;
       int nMilliseconds;
       rtimer.start();

       ui->progressBar->setHidden(false);
       ui->progressBar->setValue(0);



       QTimer *timer = new QTimer(this);
       connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
       timer->start(tsvalue);

      // cstring = getadb() +" shell rm -r /sdcard/Android/data/"+xbmcpackage+"/files/"+hidden;
       cstring = getadb() +" shell rm -r /sdcard/Android/data/"+xbmcpackage;
       command=RunProcess(cstring);

       // logfile(cstring);
       logfile(command);

       // cstring = getadb() +" shell cp -R "+externalLocation+mcfiles+hidden + " /sdcard/Android/data/"+xbmcpackage+"/files/";
       cstring = getadb() +" shell cp -R "+externalLocation+"/"+xbmcpackage + " /sdcard/Android/data/";
       command=RunProcess(cstring);

       // logfile(cstring);
       logfile(command);

       cstring = getadb() +" shell ls /sdcard/Android/data/"+xbmcpackage+filepath;
       command=RunProcess(cstring);

       if (!command.contains("No such file or directory"))
         {


           cstring = getadb() + " shell rm /sdcard/xbmc_env.properties";
           command=RunProcess(cstring);
           // logfile(cstring);
           logfile(command);

           cstring = getadb() +" shell rm -r "+externalLocation+xbmcpackage;
           command=RunProcess(cstring);
           // logfile(cstring);
           logfile(command);

           data_root="/sdcard/";
           updateRoot();

           QMessageBox::information(this,"","Data moved to internal storage");

       }


       else
       {
           QMessageBox::critical(this,"","Error moving data to internal storage");

       }


     ui->progressBar->setHidden(true);
     nMilliseconds = rtimer.elapsed();
     logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );





}


///////////////////////////////////////////////////////
void MainWindow::on_actionMove_Restore_Data_triggered()

{


    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

   // if (!isConnected && !isusb)
        //  on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }


    QString cstring = getadb() + " shell ps | grep "+xbmcpackage;
    QString command=RunProcess(cstring);


    if (command.contains(xbmcpackage))
       { QMessageBox::critical(this,"","Cannot move data while\n"+xbmcpackage+" is running!");
         return;
    }


    //cstring=getadb()+" shell /data/local/tmp/adblink/find /storage/ -type d -maxdepth 2 -perm 0771";
    //command=RunProcess(cstring);



    dataDialog dialog;

    dialog.setadb_data(getadb());

   dialog.setadb_dir(adbdir);

     dialog.setModal(true);

    if(dialog.exec() == QDialog::Accepted)
    {

        externalLocation = dialog.externalLocation();

        if(!externalLocation.startsWith("/"))
           externalLocation.prepend("/");

        if(!externalLocation.endsWith("/"))
           externalLocation.append("/") ;

        // updateLocation();

        int x = dialog.returnval2();

      switch(x){

      case 1:
      data_external();
      break;

      case 2:
      data_internal();
      break;

      case 3:
       external_thumb();
      break;

      case 4:
       internal_thumb();
      break;


      default:
       data_external();
      break;
      }




    }

}


//////////////////////////////////////////
void MainWindow::on_fdellButton_2_clicked()
{
    ui->customdir->setText("");
}

///////////////////////////////////////////////////
void MainWindow::on_actionSplash_Screen_triggered()
{
    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

    // if (!isConnected && !isusb)
         // on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }


    is_package(xbmcpackage);

   if (!is_packageInstalled)
      { QMessageBox::critical(
            this,
            "",
            xbmcpackage+" not installed");
         return;
   }

QString cstring;
QString command;

QString mcpath = "";
QString adpath="/Android/data/"+xbmcpackage+filepath;
QString root1="/sdcard/";
QString root2= "/storage/extUsb/";
QString root3= "/storage/sdcard1/";
QString root4=  "/storage/usbotg/";
QString root5= "/storage/usbdisk/";


cstring = getadb() + " shell ls "+root1+adpath;
command=RunProcess(cstring);
if (!command.contains("No such file or directory"))
{
   mcpath=root1+adpath;
}

cstring = getadb() + " shell ls "+root2+adpath;
command=RunProcess(cstring);
if (!command.contains("No such file or directory"))
{
   mcpath=root2+adpath;
}

cstring = getadb() + " shell ls "+root3+adpath;
command=RunProcess(cstring);
if (!command.contains("No such file or directory"))
{
   mcpath=root3+adpath;
}


cstring = getadb() + " shell ls "+root4+adpath;
command=RunProcess(cstring);
if (!command.contains("No such file or directory"))
{
   mcpath=root4+adpath;
}


cstring = getadb() + " shell ls "+root5+adpath;
command=RunProcess(cstring);
if (!command.contains("No such file or directory"))
{
   mcpath=root5+adpath;
}


   mcpath=mcpath+"/media";


   cstring = getadb() + " shell ls "+mcpath;

   command=RunProcess(cstring);

   if (command.contains("No such file or directory"))
    {
       QMessageBox::critical(
                   this,
                  "",
                   "Destination path missing\n"+mcpath);
                    logfile("missing path: "+mcpath);
                    return;

   }



QElapsedTimer rtimer;
int nMilliseconds;
rtimer.start();



 QString fileName = QFileDialog::getOpenFileName(this,
 "Choose splash screen file", splashdir, tr("Files (*.png)"));

 if (!fileName.isEmpty() )
 {




     QMessageBox::StandardButton reply;
       reply = QMessageBox::question(this, "Push", fileName+" selected. Continue?",
           QMessageBox::Yes|QMessageBox::No);
       if (reply == QMessageBox::Yes) {


           cstring = getadb() + " push "+'"'+fileName+'"'+ " "+mcpath+"/splash.png";

           command=RunProcess(cstring);

           // logfile(cstring);
           logfile(command);

           nMilliseconds = rtimer.elapsed();
           logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );



           if (command.contains("bytes"))


           {

               QMessageBox::information(
                           this,
                          "",
                          "Splash screen installed." );
           }
               else

           {

               QMessageBox::critical(
                           this,
                           "",
                        "Splash screen installation failed.");}


   }

}

}

////////////////////////////////////////

void MainWindow::on_doConsole_clicked()
{

    // set PATH=%PATH%;C:\xampp\php

    logfile("detaching console process");

     QString cstring = "";


     if (os == 1)

        {

        QString commstr = adbdir+"cpath.bat";
        QFile file(commstr);

            if(!file.open(QFile::WriteOnly |
                          QFile::Text))
            {
                logfile("error creating cpath.bat!");
                QMessageBox::critical(this,"","Error creating bat file!");
                return;
            }



            QTextStream out(&file);
            out  << "set PATH=%PATH%;"+QDir::currentPath()+";"<< endl;



            file.flush();
            file.close();

            cstring = "cmd /k " +QDir::currentPath()+"/cpath.bat";
            QProcess::startDetached(cstring);



     }

     QString pathdir = QCoreApplication::applicationDirPath() +"/adbfiles";

       if (os == 2 || os == 0)
         {

           QString commstr = adbdir+"cpath.sh";


           QFile file(commstr);

               if(!file.open(QFile::WriteOnly |
                             QFile::Text))
               {
                   logfile("error creating cpath!");
                   QMessageBox::critical(this,"","Error creating sh file!");
                   return;
               }



               QTextStream out(&file);
                out  << "#!/bin/sh" << endl;
                out  << "export PATH="+pathdir+":$PATH" << endl;
                out  << "/bin/sh" << endl;


               file.flush();
               file.close();


               cstring = "chmod 0755 " + commstr ;
               QString command=RunProcess(cstring);



       }


       if (os == 2)
        {
       QString cstring = "open -a Terminal.app "+adbdir+"cpath.sh";
       // logfile(cstring);
       QProcess::startDetached(cstring);
        }




       if (os == 0)
        {
           // cstring = "x-terminal-emulator --working-directory="+adbdir+"/adbfiles";
            cstring = "gnome-terminal --working-directory="+adbdir+ " -x "+adbdir+"cpath.sh";
           QProcess::startDetached(cstring);

         }


}


////////////////////////////////////////

void MainWindow::on_killServer_clicked()
{
    QElapsedTimer rtimer;
    int nMilliseconds;
    rtimer.start();


    QString cstring = adb + "  disconnect "+daddr+":"+port ;
    QString command=RunProcess(cstring);

    isConnected=false;

    //ui->device_connected->setText(devstr2);
     ui->update_status->setText("");

    kill_server();

    if (serverRunning)
      ui->server_running->setText(adbstr1);
    else
     ui->server_running->setText(adbstr2);

  ui->listDevices->clear();
  ui->listDevicesStatus->clear();

    nMilliseconds = rtimer.elapsed();
    logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


}



///////////////////////////////////////////////////
void MainWindow::on_refreshConnectedDevices_clicked()
{
    int i;
    QString isdevice;
    QString usbid;
    QString cstring = "";
    QString command = "";
    QString litem;


     ui->listDevices->clear();
     ui->listDevicesStatus->clear();

     cstring = adb + " devices";
     command=RunProcess(cstring);

        if (command.contains("device"))
           {
              //logfile("device(s) found");
              //logfile(command);

              serverRunning=true;
              ui->server_running->setText(adbstr1);



              QFile file21(adbdir+"temp.txt");

                if(!file21.open(QFile::WriteOnly))
                  {
                     QMessageBox::critical(0, "","Error creating daddr file!\n",QMessageBox::Cancel);
                      // logfile(cstring);
                      logfile(command);
                      logfile("error creating "+adbdir+ "device file");
                      return;
                  }

                QTextStream out1(&file21);
                out1  << command << endl;

                file21.flush();
                file21.close();



                QString tmpstr2 = adbdir+"temp.txt";
                QString fline2;

                   QFile file32(tmpstr2);
                     if (!file32.open(QIODevice::ReadOnly | QIODevice::Text))
                       {QMessageBox::critical(0,"","Error reading file!");
                          return; }

                     QTextStream in1(&file32);
                      while (!in1.atEnd())
                       {

                        fline2 = in1.readLine();

                          if (!fline2.isEmpty()  &&  (!fline2.contains("List of devices") &&
                                 (!fline2.contains("* daemon"))))

                           {


                              i =  fline2.indexOf("\t");

                              usbid =fline2.mid(0,i);
                              isdevice = fline2.mid(i+1);


                              if (isdevice.contains("unauthorized"))
                                  QMessageBox::critical(0,"","Device unauthorized\n\nPress 'Refresh ADB' or see help topic 'Device unauthorized' ");

                              if (isdevice.contains("offline"))
                                  QMessageBox::critical(0,"","Device offline\n\nPress 'Refresh ADB' or see help topic 'Device Offline' ");



                              is_busybox();
                              logfile("device:"+usbid);



                              litem = litem+isdevice;
                              ui->listDevices->addItem(usbid);
                               ui->listDevicesStatus->addItem(isdevice);
                          }

                      }

            file32.close();


            QFile::remove(tmpstr2);

        }


        delay(3);

}



///////////////////////////////////////////////
void MainWindow::on_listDevices_doubleClicked()
    {


    // check for port, bail if so.
    QString checktype = ui->listDevices->currentItem()->text();
      if (checktype.contains(":"))
        {  QMessageBox::critical(
                      this,
                     "",
                      "Not a USB device!");
            return;
      }



    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(0, "", "Create new record with this ID?",
          QMessageBox::Yes|QMessageBox::No);

      if (reply == QMessageBox::No)
        return;



        blank_entry_form();
        isusb=true;
       daddr = ui->listDevices->currentItem()->text();
       dataentry(1);
       loaddevicebox();
     }

//////////////////////////////////////////
void MainWindow::on_newRecord_clicked()
{



  logfile("go to dataentry -- new record");

  blank_entry_form();
  dataentry(1);
  loaddevicebox();

}


//////////////////////////////////////////////////
void MainWindow::dataentry(int flag)
{

// flag = 0 edit record
// flag = 1 new record

  ui->deviceBox->currentIndex();



logfile("opening preferences dialog");

    QString cstring;
    QString command;
    QString oldpass;
    QString olddaddr;
    QString olddescription;
    QString pkg;
    QString device_name;

    // data_root = sshpassword;

    olddaddr = daddr;
    sshcheck = false;
    mountcheck = false;
    updatecheck = true;
    olddescription=description;

    bool sshstate;
    bool updatestate;
    bool mountstate;


  if (is_su() && isConnected)
   {

       // check mount status set toggle value
        cstring = getadb() + " shell ls /system/etc/init.d/02mntdrives";
        command=RunProcess(cstring);



     if (command.contains("No such file or directory"))
         mountcheck = false;
      else
      mountcheck = true;
  }

  else mountcheck = false;

   mountstate = mountcheck;


   if (is_su() && isConnected)
    {




        // check ssh boot status set toggle value
         cstring = getadb() + " shell ls /system/etc/init.d/03sshd";
         command=RunProcess(cstring);



      if (command.contains("No such file or directory"))
          sshcheck = false;
       else
       sshcheck = true;
   }

   else sshcheck = false;

    sshstate = sshcheck;

       check_update_status();
       updatestate = updatecheck;






       // QMessageBox::critical(this,"",filepath);

    // bool currentupdate = updatecheck;

    preferencesDialog dialog;

    dialog.setPackagename(xbmcpackage);
    dialog.setPulldir(pulldir);

    dialog.setftvUpdate(updatecheck);
    dialog.setsshBoot(sshcheck);
    dialog.setmountBoot(mountcheck);

    dialog.setversioncheck(versioncheck);
    dialog.setversionLabel(version);
    dialog.setdevicename( is_amazon());

    dialog.setdescription(description);
    dialog.setfilepath(filepath);
    dialog.setdataroot(data_root);
    dialog.setdeviceindex(ui->deviceBox->currentIndex());


    dialog.setadb_pref(getadb());




    if (isusb)
        dialog.setport("");
      else
        dialog.setport(port);

    dialog.setdaddr(daddr);


    dialog.setisusb(isusb);
    dialog.setModal(true);


    if(dialog.exec() == QDialog::Accepted)
    {



    int x = dialog.returnval1();

//    QString s  = QString::number(x);
//    QMessageBox::critical(this,"",s);

    xbmcpackage = dialog.xbmcpackageName();
    pulldir = dialog.pulldir();

    updatecheck = dialog.updatecheck();
    sshcheck = dialog.sshcheck();
    mountcheck = dialog.mountcheck();

    versioncheck = dialog.versioncheck();

    description = dialog.description();
    data_root = dialog.data_root();

    // sshpassword = dialog.data_root();
    filepath = dialog.filepath();

    port = dialog.port();

    daddr = dialog.daddr();

    isusb = dialog.isusb();


    if (versioncheck)
        checkversion = 1;
    else
        checkversion = 0;

    if (x == 1 && flag == 1)
    {logfile("go insert a record");
      insertDevice();
    }

    if (x == 1 && flag == 0)
           {
             logfile("Saving Device Record");
              updateDevice(olddescription);

           }  // end x1




    if (is_su() && isConnected )  // superuser block
    {



        if (is_os5())
            {
           pkg="com.amazon.device.software.ota";
            }

            else
            {
            pkg="com.amazon.dcp";
             }




        if (updatestate != updatecheck)
            {
             logfile("Amazon update state toggled");


         if (updatecheck)  // turn updates on
                    {

                      if (amazon_updates("enable"))
                        {
                          logfile("Amazon updates on");
                          cstring = getadb() + " shell pm list packages -d";
                          command=RunProcess(cstring);

                          // logfile(cstring);
                          logfile(command);



                          if (!command.contains(pkg))
                            {
                              //ui->update_status->setText(amazon_update1);

                            }

                          else { QMessageBox::critical(this,"","Problem: upsdates not enabled!");
                                  logfile("Problem: updates not enabled!");
                                  //ui->update_status->setText(amazon_update0);
                               }

                        }  //  if (amazon_updates("enable"))



             }  // if (updatecheck)


         if (!updatecheck)  // turn updates off
              {

                if (amazon_updates("disable"))
                              {
                               logfile("Amazon updates off, updates disabled");
                               cstring = getadb() + " shell pm list packages -d";
                               command=RunProcess(cstring);

                               // logfile(cstring);
                               logfile(command);

                               //if (command.contains(pkg))
                               //ui->update_status->setText(amazon_update0);

                           }
                         else
                            { QMessageBox::critical(this,"","Problem: updates not disabled!");
                               logfile("Problem: updates not disabled!");
                               //ui->update_status->setText(amazon_update1);
                             }

             }
         }


      }

}

    cstring = getadb() + " shell "+busypath+"find /system/xbin/ -name su";
    command=RunProcess(cstring);

    if(!command.contains("/system/xbin/su"))
     return;


    cstring = getadb() + " shell ls "+busypath+"mntdrives.sh";
    command=RunProcess(cstring);
    if (command.contains("No such file or directory"))
    {
        QMessageBox::critical(this,"","System tools not installed.");
        return;
    }

      if (mountcheck != mountstate)
          {
             logfile("Mount at boot toggled");




             if (!mountcheck )
                     {
                      logfile ("Remove init.d/02mntdrives");

                      //

                      mount_system("rw");

                      cstring = getadb() + " shell ls /system/etc/init.d/04mntshares";
                      command=RunProcess(cstring);

                      if (command.contains("No such file or directory"))
                           {
                              cstring = getadb() + " shell su -c rm /system/etc/init.d/01sleep";
                              command=RunProcess(cstring);
                            }



                             cstring = getadb() + " shell su -c rm /system/etc/init.d/02mntdrives";
                             command=RunProcess(cstring);

                             mount_system("ro");

                             // logfile(cstring);
                             logfile(command);

                             mount_system("ro");

                             // logfile(cstring);
                             logfile(command);
                             logfile("USB drive is not persistent");


             }  // rm mount at boot




             if (mountcheck )  // start mount at boot
                   {
                     logfile ("Create init.d/02mntdrives");


                     mount_system("rw");


                             cstring = getadb() + " shell su -c cp " + busypath+"01sleep /system/etc/init.d";
                             command=RunProcess(cstring);

                             if (!command.isEmpty())
                                  {
                                    // logfile(cstring);
                                    logfile(command);
                                    logfile("file copy error, adbfiles to system/etc");
                                     mount_system("ro");
                                     return;
                                   }

                             cstring = getadb() + " shell su -c cp " + busypath+"02mntdrives /system/etc/init.d";
                             command=RunProcess(cstring);

                             if (!command.isEmpty())
                                  {
                                    // logfile(cstring);
                                    logfile(command);
                                    logfile("file copy error, adbfiles to /system/etc/init.d");
                                     mount_system("ro");
                                     return;
                                   }


                   } // mount at boot



  }



 }


////////////////////////////////////////
void MainWindow::on_delRecord_clicked()
{

    description = ui->deviceBox->currentText();

    if (!description.isEmpty())
     {

    QString descrip = description;

    QMessageBox::StandardButton reply;
     reply = QMessageBox::question(0, "", " Delete "+descrip+"?",
             QMessageBox::Yes|QMessageBox::No);
       if (reply == QMessageBox::No)
        {
          return;
         }

       deleteRecord(descrip);
       loaddevicebox();


       logfile(descrip+ " is deleted");
  }
}


void MainWindow::on_actionView_Log_triggered()
{


    //logfile("opening adblog dialog");

     adblogDialog dialog;
     dialog.setModal(true);
     dialog.exec();


}


///////////////////////////////////////

void MainWindow::on_logButton_clicked()
{
    on_actionView_Log_triggered();
}

//////////////////////////////////////////////////
void MainWindow::on_actionRoot_device_triggered()
{
  QMessageBox::critical(0,"","Rooting no longer supported.");

  return;

    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

    // if (!isConnected && !isusb)
        //  on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }



    QMessageBox::StandardButton reply;
     reply = QMessageBox::question(0, "", "This a depreciated feature since firmware 51.1.3.0 and above can't be rooted at this time. Additionally, the Stick has never been rooted. Continue?",
             QMessageBox::Yes|QMessageBox::No);
       if (reply == QMessageBox::No)
        {
           return;
         }




    QString rootfile1 = adbdir+"tr.apk";
    QString rootfile2 = adbdir+"su.apk";

    bool file1 = false;
    bool file2 = false;



                       QElapsedTimer rtimer;
                       int nMilliseconds;
                       rtimer.start();



                       QFile Fout1(rootfile1);

                       if(!Fout1.exists())
                       {

                           QMessageBox::critical(
                              this,
                              tr("adbLink"),
                              rootfile1+" not found.");
                              logfile(rootfile1+" not found.");

                              return;
                       }


                       QFile Fout2(rootfile2);

                       if(!Fout2.exists())
                       {

                           QMessageBox::critical(
                              this,
                              tr("adbLink"),
                              rootfile2+" not found.");
                              logfile(rootfile2+" not found.");
                              return;
                       }

                             ui->progressBar->setHidden(false);
                             ui->progressBar->setValue(0);

                             QTimer *timer = new QTimer(this);
                             connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
                             timer->start(tsvalue);

                             QString cstring = getadb() + " install -r "+rootfile1;

                           QString command=RunProcess(cstring);

                             if (!command.contains("Success"))
                                {
                                 // logfile(cstring);
                                 logfile(command);
                                 QMessageBox::information(
                                             this,
                                             "",
                                             "tr.apk install failed");
                                  ui->progressBar->setHidden(true);
                                  return;
                                }

                             else
                                 file1 = true;

                             // logfile(cstring);
                             logfile(command);

                             cstring = getadb() + " install -r "+rootfile2;

                             command=RunProcess(cstring);

                                    ui->progressBar->setHidden(true);

                                    if (!command.contains("Success"))
                                       {
                                        // logfile(cstring);
                                        logfile(command);
                                        QMessageBox::information(
                                                    this,
                                                    "",
                                                    "su.apk install failed");

                                       }
                                    else
                                   file2 = true;

                                    // logfile(cstring);
                                    logfile(command);

if (file1 && file2)
{

 QMessageBox::information( this,"","Root software installed.\nRun towelroot on the LinkTV\n to finish rooting process.");
 logfile("Root software installed.\nRun towelroot on the LinkTV\n to finish rooting process.");

 nMilliseconds = rtimer.elapsed();
 logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


}

}



///////////////////////////////////////////

void MainWindow::on_cacheButton_clicked()

{


    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);


    if (!isConnected)
          { QMessageBox::critical(0,"",devstr2);
             return;
          }




logfile("opening cache dialog");

if (data_root.isEmpty())
    data_root="/sdcard/";

QString cstring;
QString command;
QString hidden;
QString xpath = "";
QString mcpath=data_root+ "/Android/data/"+xbmcpackage+filepath;
xpath = mcpath+"/userdata/";

cstring = getadb() + " shell ls "+mcpath;

command=RunProcess(cstring);

if (command.contains("No such file or directory"))
{
   QMessageBox::critical(
               this,
              "",
               "Destination path missing");
               return;
}

   cacheDialog dialog;


    dialog.setcbuffermode(buffermode);
    dialog.setcbuffersize(buffersize);
    dialog.setcbufferfactor(bufferfactor);

    dialog.setModal(true);


    if(dialog.exec() == QDialog::Accepted)
    {

 int x = dialog.returncval1();


    buffermode = dialog.cbuffermode();
    buffersize = dialog.cbuffersize();
    bufferfactor = dialog.cbufferfactor();




    if (x == 2)
          {


   logfile("write advancedsettings.xml");


         QString str1;
         str1.setNum(buffermode-1);

         cstring = getadb() + " shell ls "+mcpath;


              QString filename1 = "advancedsettings.xml";
              QString filename2 = adbdir+filename1;



             cstring = getadb() + " shell ls "+mcpath;
             command=RunProcess(cstring);
              if (command.contains("No such file or directory"))
                      {
                         QMessageBox::critical(this,"","Destination path missing");
                          return;
                     }



                     cstring = getadb() + " shell ls "+xpath+filename1;
                     command=RunProcess(cstring);

                     // logfile(cstring);
                     logfile(command);

                      if (!command.contains("No such file or directory"))
                         {
                          logfile("advancedsettings.xml exists");

                          QMessageBox::StandardButton reply;
                           reply = QMessageBox::question(this, "XML", "advancedsettings.xml exists. Overwrite?\n(will backup original)",
                                                         QMessageBox::Yes|QMessageBox::No);
                           if (reply == QMessageBox::No) {
                               logfile("abort xml write");
                               return;
                              } else {
                              logfile("continue xml write");
                              logfile("backup advancedsettings.xml");
                              cstring = getadb() + " shell cp "+xpath+filename1+" "+xpath+filename1+".old";
                              command=RunProcess(cstring);
                              }
                          }  // end if exists



          QString line1 ="<advancedsettings>";
          QString line2 ="  <network>";
          QString line3 ="    <buffermode>"+str1+"</buffermode>";
          QString line4 ="    <cachemembuffersize>"+buffersize+"</cachemembuffersize>";
          QString line5 ="    <readbufferfactor>"+bufferfactor+"</readbufferfactor>";
          QString line6 ="  </network>";
          QString line7 ="</advancedsettings>";

          QFile file(filename2);


          if(!file.open(QFile::WriteOnly))
                {
                  logfile("error creating advancedsettings.xml.");
                  QMessageBox::critical(this,"","Unknown error creating xml file!");
                   return;
                 }

                  QTextStream out(&file);

                  out  << line1 << endl;
                  out  << line2 << endl;
                  out  << line3 << endl;
                  out  << line4 << endl;
                  out  << line5 << endl;
                  out  << line6 << endl;
                  out  << line7 << endl;

                  file.flush();
                  file.close();

                  cstring = getadb() + " push "+filename2+ " "+xpath+filename1;
                  command=RunProcess(cstring);

                   if (!command.contains("bytes"))
                      {
                        // logfile(cstring);
                        logfile(command);
                        logfile("error pushing xml script to device!");
                        QMessageBox::critical(this,"","Error pushing xml from PC to device!");
                        return;
                      }
                    else {
                       QMessageBox::information(this,"","advancedsettings.xml written");
                   }



           }


  }  //end accepted


} // end cache


////////////////////////////////////////////

void MainWindow::on_splashButton_clicked()
{
    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

    // if (!isConnected && !isusb)
         // on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }


    is_package(xbmcpackage);

   if (!is_packageInstalled)
      { QMessageBox::critical(
            this,
            "",
            xbmcpackage+" not installed");
         return;
   }

   if (data_root.isEmpty())
       data_root="/sdcard/";

  QString cstring;
  QString command;
  QString hidden;
  QString xpath = "";
  QString mcpath=data_root+ "/Android/data/"+xbmcpackage+filepath;

  mcpath=mcpath+"/media";

  cstring = getadb() + " shell ls "+mcpath;

  command=RunProcess(cstring);

  if (command.contains("No such file or directory"))
   {
      QMessageBox::critical(
                  this,
                 "",
                  "Destination path missing: "+mcpath);
                  return;
  }





QElapsedTimer rtimer;
int nMilliseconds;
rtimer.start();



 QString fileName = QFileDialog::getOpenFileName(this,
 "Choose splash screen file", splashdir, tr("Files (*.png)"));

 if (!fileName.isEmpty() )
 {


     QMessageBox::StandardButton reply;
       reply = QMessageBox::question(this, "Push", fileName+" selected. Continue?",
           QMessageBox::Yes|QMessageBox::No);
       if (reply == QMessageBox::Yes) {


           cstring = getadb() + " push "+'"'+fileName+'"'+ " "+mcpath+"/splash.png";

           command=RunProcess(cstring);

           // logfile(cstring);
           logfile(command);

           nMilliseconds = rtimer.elapsed();
           logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );



           if (command.contains("bytes"))


           {

               QMessageBox::information(
                           this,
                          "",
                          "Splash screen installed." );
           }
               else

           {

               QMessageBox::critical(
                           this,
                           "",
                        "Splash screen installation failed.");}


   }

}

}

void MainWindow::on_mvdataButton_clicked()
{
    on_actionMove_Restore_Data_triggered();

}



void MainWindow::on_actionInstall_FireStarter_triggered()
{
    logfile("firestarter function entered");

    QString command;
    QString cstring;
    QString lookup=daddr;
    QString package = "de.belu.firestarter";

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

   // if (!isConnected && !isusb)
      //    on_connButton_clicked();

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }


   QString fireapk = adbdir+"firestarter.apk";
   QString firesettings = adbdir+"FireStarterBackup.zip";

  QFile Fout1(fireapk);
   if(!Fout1.exists())
    {
      QMessageBox::critical(this,"",fireapk+" not found.");
       logfile(fireapk+" not found.");
       return;
   }

   QFile Fout2(firesettings);
    if(!Fout2.exists())
     {
      logfile(firesettings+" not found.");
    }



    QElapsedTimer rtimer;
    int nMilliseconds;
    rtimer.start();




    logfile("opening firestarter dialog");

     firestarterDialog dialog;

     dialog.setModal(true);

     if(dialog.exec() == QDialog::Accepted)
     {


     int x = dialog.firestarter();

       if (x==1)
        {

         ui->progressBar->setHidden(false);
         ui->progressBar->setValue(0);

         QTimer *timer = new QTimer(this);
         connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
         timer->start(tsvalue);

          cstring = getadb() + " install -r " + '"'+ adbdir+"firestarter.apk";
          command=RunProcess(cstring);

          // logfile(cstring);
          logfile(command);

          if (command.contains("Success"))

          {
              QMessageBox::information(this,"","FireStarter Installed");
          }
             else
          {
              QMessageBox::critical(this,"","FireStarter Install failed");
              ui->progressBar->setHidden(true);
              return;
          }

          cstring = getadb() + " push "+ firesettings + " /sdcard/";
          command=RunProcess(cstring);

          // logfile(cstring);
          cstring = getadb() + " shell ls /sdcard/FireStarterBackup.zip";
          command=RunProcess(cstring);


          if (command.contains("No such file or directory"))
           {

              logfile("FireStarter settings file not copied!");
              QMessageBox::critical(this,"","FireStarter settings file not copied!\nManually set up FireStarter\nSee Help.");

          }




          nMilliseconds = rtimer.elapsed();
          logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );


          ui->progressBar->setHidden(true);



       }

  } // end of install


}

void MainWindow::on_keypadButton_clicked()
{
    if (!isConnected)
          { QMessageBox::critical(0,"",devstr2);
             return;
          }

     QString cstring = getadb() + " shell input keyevent ";
     keyboardDialog dialog;
     dialog.setdaddressLabel(cstring);
     dialog.exec();

}



/////////////////////////////////////////
void MainWindow::on_cifsonButton_clicked()
{
    QString lookup=daddr;
    QString command;
    QString cstring;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }



     if (!is_su())
        { QMessageBox::critical(
              this,
              "",
              "Root required!");
           return;
     }


     if(!is_system_tools())
     {
         QMessageBox::critical(0,"","System Tools not installed");
        return;
       }




         cstring = getadb() + " shell su -c ls "+busypath+"samba";
         command=RunProcess(cstring);
         // logfile(cstring);

         if (command.contains("No such file or directory"))
          {
             QMessageBox::critical(0,"","Samba not installed");
             return;
         }

         cstring = getadb() + " shell su -c ps | grep smbd";
         command=RunProcess(cstring);
         // logfile(cstring);

         if (command.contains("com.funkyfresh.samba/files/smbd"))
          {
             return;
         }


         cstring = getadb() + " shell su -c "+busypath+"samba start";
         command=RunProcess(cstring);
         logfile(command);

         // logfile(cstring);
         cstring = getadb() + " shell su -c ps | grep smbd";
         command=RunProcess(cstring);


         if (command.contains("com.funkyfresh.samba/files/smbd"))
          {

             logfile("Samba stopped");
             QMessageBox::information(this,"","Samba started");

         }

         else

         {

            logfile("Samba not started");
            QMessageBox::critical(this,"","Samba not started. See log.");

        }

}


///////////////////////////////////////

bool MainWindow::check_dep_menu()
{

    QString cstring = getadb() + " shell ls /system/xbin/su";
    QString command=RunProcess(cstring);


    if(!command.contains("No such file or directory"))
     {

      cstring = getadb() + " shell cat /system/build.prop";
      command=RunProcess(cstring);

      if (command.contains("ro.product.board=MSM8960"))
          return true;

      }

     return false;

}



///////////////////////////////////////////
void MainWindow::on_cifsoffButton_clicked()
{

    QString lookup=daddr;
    QString command;
    QString cstring;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }



     if (!is_su())
        { QMessageBox::critical(
              this,
              "",
              "Root required!");
           return;
     }


     if(!is_system_tools())
     {
         QMessageBox::critical(0,"","System Tools not installed");
        return;
       }

     cstring = getadb() + " shell su -c ls "+busypath+"samba";
     command=RunProcess(cstring);
     // logfile(cstring);

     if (command.contains("No such file or directory"))
      {
         QMessageBox::critical(0,"","Samba not installed");
         return;
     }


     cstring = getadb() + " shell su -c ps | grep smbd";
     command=RunProcess(cstring);
     // logfile(cstring);

     if (!command.contains("com.funkyfresh.samba/files/smbd"))
      {
         return;
     }

   //grep smbd
    //com.funkyfresh.samba/files/smbd

    cstring = getadb() + " shell su -c "+busypath+"samba stop";
    command=RunProcess(cstring);
    logfile(command);

    // logfile(cstring);
    cstring = getadb() + " shell su -c ps | grep smbd";
    command=RunProcess(cstring);


    if (!command.contains("com.funkyfresh.samba/files/smbd"))
     {

        logfile("Samba stopped");
        QMessageBox::information(this,"","Samba stopped");

    }

    else

    {

       logfile("Samba not closed!");
       QMessageBox::critical(this,"","Samba still running");

   }



}


/////////////////////////////////////////////////////////////

void MainWindow::on_actionInstall_AFTV_Recovery_triggered()

{

    QString cstring;
    QString command;
    QString fileName;

    QString lookup=daddr;

     if(!isusb)
      lookup=lookup+":"+port;

    isConnected=find_daddr(lookup);

     if (!isConnected)
           { QMessageBox::critical(0,"",devstr2);
              return;
           }



   if (!is_su())
      { QMessageBox::critical(
            this,
            "",
            "Root required!");
         return;
   }


   if (!is_system_tools())
   {
       QMessageBox::critical(this,"","System Tools not installed");
       logfile("System Tools not installed");
       return;
   }



   cstring = getadb() + " shell cat /system/build.prop";
   command=RunProcess(cstring);
       if (!command.contains("ro.board.platform=mt8173"))
           {
             QMessageBox::critical(this,"","Not supported for this device.");
           return;
        }


       QMessageBox::StandardButton reply;
        reply = QMessageBox::question(0, "", "Install Custom Recovery?\nWarning: this will void your warranty.\nResults are not guaranteed.\nProceed at your own risk.",
                QMessageBox::Yes|QMessageBox::No);
          if (reply == QMessageBox::No)
           {
              return;
           }



   logfile("v2 recovery installation starts");


    QElapsedTimer rtimer;
     int nMilliseconds;

    rtimer.start();

    logfile("recovery installation started");

          fileName = QFileDialog::getOpenFileName(this,
          "Choose recovery image", hdir, tr("Files (*.zip)"));

          if (!fileName.isEmpty() )
          {

      QMessageBox::StandardButton reply;
         reply = QMessageBox::question(this, "", "Install 4K Recovery?\n\n"+fileName,
                                      QMessageBox::Yes|QMessageBox::No);
         if (reply == QMessageBox::No)
           {logfile("recovery installation cancelled");
             return;}


         QFileInfo fi(fileName);
         QString name = fi.fileName();


     ui->progressBar->setHidden(false);
     ui->progressBar->setValue(0);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
    timer->start(tsvalue);

     QString c1 = "Extracting unzip";
     QString c2 = "Remounting /system read-write";
     QString c3 = "Extracting";
     QString c4 = "Remounting /system read-only";

     cstring = getadb() + " push "+fileName+" /sdcard/";
     command=RunProcess(cstring);

        logfile(cstring);
        logfile(command);

       cstring = getadb() + " shell su -c sh /sdcard/"+name;
       command=RunProcess(cstring);

       logfile(cstring);
       logfile(command);

    // QMessageBox::information(this,"",command);

       int c=0;
       nMilliseconds = rtimer.elapsed();
       logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );
       ui->progressBar->setHidden(true);


       if(command.contains(c1))
       {
          c++;
       }



       if(command.contains(c2))
       {
           c++;
       }

       if(command.contains(c3))
        {
           c++;

       }


       if(command.contains(c4))
       {
           c++;
       }




      if(c==4)
         QMessageBox::information(this,"","Done.");
       else
          QMessageBox::critical(this,"","Error: see log.");

      cstring = getadb() + " shell rm /sdcard/"+name;
      command=RunProcess(cstring);
      logfile(command);


   nMilliseconds = rtimer.elapsed();
   logfile("process time duration: "+ QString::number(nMilliseconds/1000)+ " seconds" );
   ui->progressBar->setHidden(true);


    }

}
