#ifndef FIRESTARTERDIALOG_H
#define FIRESTARTERDIALOG_H

#include <QDialog>

namespace Ui {
class firestarterDialog;
}

class firestarterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit firestarterDialog(QWidget *parent = 0);
    ~firestarterDialog();

public:
    int firestarter();

private slots:
    void on_donate_clicked();

    void on_pushButton1_clicked();


private:
    Ui::firestarterDialog *ui;
};

#endif // FIRESTARTERDIALOG_H
