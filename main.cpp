#include "ui/mainwindow.h"
#include "deviser-version.h"
#include "model/devisersettings.h"

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

  QString openFileName(QString::null);

  for (int i = 1; i < argc; ++i)
  {
    QString current(argv[i]);

    if (current == "--version")
    {
      std::cout << "DeviserEdit " << DEVISER_DOTTED_VERSION << std::endl;
      return 0;
    }

    if (current.toLower() == "--havelanguage")
    {
      DeviserSettings::setHaveLanguage(true);
    }

    if (QFile(current).exists())
      openFileName = current;

  }

  MainWindow w;
  if (!openFileName.isNull())
    w.openFile(openFileName);

  w.show();

  return a.exec();
}
