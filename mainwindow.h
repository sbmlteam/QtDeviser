#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class FormDeviserPackage;
class FormDeviserVersion;
class FormDeviserEnum;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    FormDeviserPackage* ctrlPackage;
    FormDeviserVersion* ctrlVersion;
    FormDeviserEnum* ctrlEnum;
};

#endif // MAINWINDOW_H
