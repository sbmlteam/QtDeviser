#include "ui/mainwindow.h"
#include <QApplication>

#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Deviser Edit");
    a.setApplicationDisplayName("Deviser Edit");
    MainWindow w;

    for (int i = 1; i < argc; ++i)
      if (QFile(argv[i]).exists())
        w.openFile(argv[i]);

    w.show();

    return a.exec();
}
