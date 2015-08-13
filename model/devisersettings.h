#ifndef DEVISERSETTINGS_H
#define DEVISERSETTINGS_H

#include <QObject>
#include <QString>

class DeviserSettings : public QObject
{
  Q_OBJECT
public:
  explicit DeviserSettings(QObject *parent = 0);

  static DeviserSettings* getInstance();

  static QString getSettingsFile();

  QString getPythonInterpreter() const;
  void setPythonInterpreter(const QString &pythonInterpreter);

  QString getDeviserRepository() const;
  void setDeviserRepository(const QString &deviserRepository);

  QString getDefaultOutputDir() const;
  void setDefaultOutputDir(const QString &defaultOutputDir);

  QString getSbmlPkgSpecDir() const;
  void setSbmlPkgSpecDir(const QString &sbmlPkgSpecDir);

  QString getMikTexBinDir() const;
  void setMikTexBinDir(const QString &mikTexBinDir);

  QString getLibSBMLSourceDir() const;
  void setLibSBMLSourceDir(const QString &libSBMLSourceDir);

  QString getCompiler() const;
  void setCompiler(const QString &compiler);

  QString getCmakeExecutable() const;
  void setCmakeExecutable(const QString &cmakeExecutable);

  QString getDependencySourceDir() const;
  void setDependencySourceDir(const QString &dependencySourceDir);

  QString getSwigExecutable() const;
  void setSwigExecutable(const QString &swigExecutable);

  QString getPythonIncludes() const;
  void setPythonIncludes(const QString &pythonIncludes);

  QString getPythonLib() const;
  void setPythonLib(const QString &pythonLib);

  void loadSettings(const QString& settingsFile);
  void saveSettings();

  int getWidth() const;
  void setWidth(int width);

  int getHeight() const;
  void setHeight(int height);

  QString getVsBatchFile() const;
  void setVsBatchFile(const QString &vsBatchFile);

signals:

public slots:

protected:
  static DeviserSettings* mpInstance;

  QString mPythonInterpreter;
  QString mDeviserRepository;
  QString mDefaultOutputDir;
  QString mSbmlPkgSpecDir;
  QString mMikTexBinDir;
  QString mLibSBMLSourceDir;
  QString mCompiler;
  QString mCmakeExecutable;
  QString mDependencySourceDir;
  QString mSwigExecutable;
  QString mPythonIncludes;
  QString mPythonLib;
  QString mVsBatchFile;


  int mWidth;
  int mHeight;

private:

  static void removeInstance();

};

#endif // DEVISERSETTINGS_H
