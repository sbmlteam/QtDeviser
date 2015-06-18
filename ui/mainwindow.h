#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class FormDeviserPackage;
class FormDeviserVersion;
class FormDeviserEnum;
class FormDeviserMapping;
class FormDeviserClass;
class FormDeviserPlugin;

class DeviserPackage;
class DeviserBase;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void showAbout();
    void addClass();
    void addEnum();
    void addPlugin();
    void addVersion();
    void editPreferences();
    void fixErrors();
    void generate();
    void newModel();
    void openFile();
    void openFile(const QString&);
    void saveFile();
    void saveFileAs();
    void saveAsFile(QString);
    void showUML();
    void validateDescription();

    void updateUI();

private slots:
    void on_treeWidget_itemSelectionChanged();

private:
    Ui::MainWindow *ui;

    FormDeviserPackage* ctrlPackage;
    FormDeviserVersion* ctrlVersion;
    FormDeviserEnum* ctrlEnum;
    FormDeviserMapping* ctrlMapping;
    FormDeviserClass* ctrlClass;
    FormDeviserPlugin* ctrlPlugin;

    DeviserPackage* model;
    DeviserBase* currentElement;

    QString fileName;

};

#endif // MAINWINDOW_H
