#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}





class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

class MyClass;

private slots:

    void on_actionAbout_triggered();

    void on_connButton_clicked();

    void TimerEvent();

    void readInc();

    void on_sideload_Button_clicked();

    void on_disButton_clicked();

    void on_actionQuit_triggered();

    void on_uninstall_Button_clicked();

    void on_actionHelp_triggered();

    void on_backupButton_clicked();

    void on_fpushButton_clicked();

    void on_fpullButton_clicked();

    void on_restoreButton_clicked();

    void on_pushRemote_clicked();

    void on_adbshellButton_clicked();


    void delay(int secs);

   void insertDevice();

   void createTables();


   QString getadb();

   void delayTimer(int rdelay);

   QString RunProcess(QString cstring);

   void rotate_logfile();

   void logfile(QString line);

   void rebootDevice(QString reboot);

   bool fileExists(QString path);

   bool is_busybox();


    QString strip (QString str);

    void blank_entry_form();

    void kill_server();

   void start_server();


   bool is_package(QString package);

   int getShareCount();

   int getRows();


    bool find_daddr(QString);



    void updateRoot();

    void updateDevice(QString olddescription);


    void getRecord(QString descrip);

    void on_actionReboot_triggered();



    void deleteRecord(QString descrip);



    void open_pref_database();

    bool isConnectedToNetwork();

    void addcolumn1();

    void on_actionRecovery_triggered();




    void on_fdellButton_clicked();



    void on_donate_clicked();

    void get_data();

    void onReqCompleted();

    void on_actionDownload_Kodi_triggered();

    void on_editRecord_clicked();




    void dataentry(int flag);

    void data_external();

    void data_internal();

    void external_thumb();

    void internal_thumb();
    void loaddevicebox();

    void on_fdellButton_2_clicked();

    //void on_actionSplash_Screen_triggered();

    void on_doConsole_clicked();

    void on_killServer_clicked();

    void on_refreshConnectedDevices_clicked();


   void on_listDevices_doubleClicked();

   void on_newRecord_clicked();


   void on_delRecord_clicked();

   void on_logButton_clicked();

   void on_cacheButton_clicked();

   void on_splashButton_clicked();

   void on_mvdataButton_clicked();

   void on_keypadButton_clicked();

   void on_actionView_Kodi_Log_triggered();

private:
    Ui::MainWindow *ui;



};

#endif // MAINWINDOW_H
