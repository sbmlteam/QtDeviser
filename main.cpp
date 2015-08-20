#include "ui/mainwindow.h"
#include <QApplication>

#include <QFile>
#include <QTextCodec>
#include <QProcess>
#include <QMetaType>

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
    if (QFile(argv[i]).exists())
      w.openFile(argv[i]);

  w.show();

  return a.exec();
}
