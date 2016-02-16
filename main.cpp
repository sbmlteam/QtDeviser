#include "ui/mainwindow.h"
#include "deviser-version.h"

#include <QApplication>

#include <QFile>
#include <QTextCodec>
#include <QProcess>
#include <QMetaType>

#include <iostream>

int main(int argc, char *argv[])
{
  qRegisterMetaType<QProcess::ExitStatus>("QProcess::ExitStatus");

  QApplication a(argc, argv);
  a.setApplicationName("Deviser Edit");

#if QT_VERSION > 0x050000
  a.setApplicationDisplayName("Deviser Edit");
#endif

  MainWindow w;

  for (int i = 1; i < argc; ++i)
  {
    QString current(argv[i]);

    if (current == "--version")
    {
      std::cout << "DeviserEdit " << DEVISER_DOTTED_VERSION << std::endl;
      return 0;
    }

    if (QFile(current).exists())
      w.openFile(current);
  }

  w.show();

  return a.exec();
}
