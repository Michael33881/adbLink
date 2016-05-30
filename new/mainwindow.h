#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>

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

    void check_update_status();

    void load_filemanager(QString dir);

    void pull_single_file(QString filestring);

   bool check_dep_menu();

   void getpackage();

    bool find_daddr(QString);

    void on_actionReboot_triggered();

    void on_actionRecovery_triggered();

    void on_screenshotButton_clicked();

    void on_actionInstall_busybox_triggered();

    void on_actionUninstall_Busybox_triggered();

    void on_fdellButton_clicked();

    void on_actionFirmware_install_triggered();

    void on_mntButton_clicked();

    void on_umntButton_clicked();

    void on_rwButton_clicked();

    void on_roButton_clicked();

    void on_donate_clicked();

    void get_data();

    void onReqCompleted();

    void on_actionCredits_triggered();

    void on_actionInstall_Recovery_triggered();

    void on_actionInstall_SSH_triggered();

    void on_actionUninstall_SSH_triggered();

    void on_puttyButton_clicked();

    void on_sftpButton_clicked();

    void deleteRecord(QString descrip);

    void on_actionSwap_data_triggered();

    void on_actionUnlock_Bootloader_triggered();


    QString getadb();

    void delay(int secs);

    bool fileExists(QString path);

    void delayTimer(int rdelay);

    QString RunProcess(QString cstring);

    void rotate_logfile();

    void logfile(QString line);

    void rebootDevice(QString reboot);

    bool mount_system(QString mnt);

    bool mount_root(QString mnt);

    bool is_su();

    bool is_busybox();

    bool is_system_tools();

    QString is_amazon();

     QString strip (QString str);

     void blank_entry_form();

     void kill_server();

    void start_server();

    bool is_os5();

    bool is_package(QString package);

    bool amazon_updates(QString onoff);

    int getShareCount();

     int getRows();

    void createTables();

    void insertDevice();

    void insertShare();

    void  updateDevice(QString olddescription);

    void updateRoot();

    void getRecord(QString descrip);

    void updateShares();

    void  readShares();

    void on_actionMount_CIFS_triggered();


    void on_actionDownload_Kodi_triggered();

    void on_editRecord_clicked();

    void on_actionInstall_Stock_Recovery_triggered();

    void on_actionInstall_Samba_triggered();

    void on_actionUninstall_Samba_triggered();

    void on_actionInstallBootmenu_triggered();

    void on_actionUninstall_Boot_Menu_triggered();

    void dataentry(int flag);

    void data_external();

    void data_internal();

    void external_thumb();

    void internal_thumb();
    void loaddevicebox();

    void on_actionMove_Restore_Data_triggered();

    void on_actionSplash_Screen_triggered();

    void on_doConsole_clicked();

    void on_killServer_clicked();

    void on_refreshConnectedDevices_clicked();


   void on_listDevices_doubleClicked();

   void on_newRecord_clicked();


   void on_delRecord_clicked();

   void on_logButton_clicked();

   void on_actionRoot_device_triggered();

   void on_cacheButton_clicked();

   void on_splashButton_clicked();

   void on_mvdataButton_clicked();

   void on_actionInstall_FireStarter_triggered();

   void on_keypadButton_clicked();

  // void on_pushButton_toggled(bool checked);

   void on_cifsonButton_clicked();

   void on_cifsoffButton_clicked();

   void on_Install_v2Recovery_triggered();

   void on_actionView_Kodi_log_triggered();



   void on_directoryWidget_doubleClicked(const QModelIndex &index);

   void on_dirbackButton_clicked();

   void on_customdirButton_clicked();

    void writeConfig();

    void addcolumn1();

    void open_pref_database();

   void on_directoryWidget_clicked(const QModelIndex &index);

   void on_fm_delButton_clicked();

   void on_fm_pullButton_clicked();

   void on_fm_pushButton_clicked();

   void on_fm_mkdirButton_clicked();

   bool isConnectedToNetwork();

   void on_treeView_doubleClicked(const QModelIndex &index);

private:
   QFileSystemModel *dirmodel;


private:
    Ui::MainWindow *ui;



};

#endif // MAINWINDOW_H
