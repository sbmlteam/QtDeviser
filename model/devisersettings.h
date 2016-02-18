#ifndef DEVISERSETTINGS_H
#define DEVISERSETTINGS_H

#include <QObject>
#include <QColor>
#include <QString>
#include <QStringList>

class DeviserSettings : public QObject
{
  Q_OBJECT
public:
  explicit DeviserSettings(QObject *parent = 0);  

  static DeviserSettings* getInstance();

  static QString getSettingsFile();

  const QString& getPythonInterpreter() const;
  void setPythonInterpreter(const QString &pythonInterpreter);

  const QString& getDeviserRepository();
  void setDeviserRepository(const QString &deviserRepository);

  const QString& getDefaultOutputDir() const;
  void setDefaultOutputDir(const QString &defaultOutputDir);

  const QString& getSbmlPkgSpecDir();
  void setSbmlPkgSpecDir(const QString &sbmlPkgSpecDir);

  const QString& getMikTexBinDir() const;
  void setMikTexBinDir(const QString &mikTexBinDir);

  const QString& getLibSBMLSourceDir() const;
  void setLibSBMLSourceDir(const QString &libSBMLSourceDir);

  const QString& getCompiler() const;
  void setCompiler(const QString &compiler);

  const QString& getCmakeExecutable() const;
  void setCmakeExecutable(const QString &cmakeExecutable);

  const QString& getDependencySourceDir();
  void setDependencySourceDir(const QString &dependencySourceDir);

  const QString& getSwigExecutable() const;
  void setSwigExecutable(const QString &swigExecutable);

  const QString& getPythonIncludes() const;
  void setPythonIncludes(const QString &pythonIncludes);

  const QString& getPythonLib() const;
  void setPythonLib(const QString &pythonLib);

  void loadSettings(const QString& settingsFile);
  void saveSettings();

  int getWidth() const;
  void setWidth(int width);

  int getHeight() const;
  void setHeight(int height);

  const QString& getVsBatchFile() const;
  void setVsBatchFile(const QString &vsBatchFile);

  QStringList& getRecentFiles();
  void addRecentFile(const QString& filename);
  void removeRecentFile(const QString& filename);

  QStringList& getUserDefinedTypes();
  void addType(const QString& type);
  void removeType(const QString& type);

  bool getUseSVG() const;
  void setUseSVG(bool useSVG);

  bool getFitUML() const;
  void setFitUML(bool fitUML);

  QColor getValidationColor() const;
  void setValidationColor(const QColor& validationColor);

signals:

public slots:

protected:

  /**
   * save the settings file under the given name
   */
  void saveSettings(const QString& fileName);

  /**
   * detect a directory with specified name around the executable
   */
  static QString detectDir(const QString& name);

  /**
   * detect an executable in the path (non-windows only)
   */
  static QString detectExecutable(const QString& name);

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
  QStringList mRecentFiles;
  QStringList mUserDefinedTypes;

  bool mFitUML;
  bool mUseSVG;

  int mWidth;
  int mHeight;

  QColor mValidationColor;

private:

  static void removeInstance();

};

#endif // DEVISERSETTINGS_H
