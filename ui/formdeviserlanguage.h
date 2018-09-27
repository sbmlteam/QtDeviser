#ifndef FORMDEVISERLANGUAGE_H
#define FORMDEVISERLANGUAGE_H

#include <QWidget>

class DeviserLanguage;
class QSortFilterProxyModel;
class LanguageVersionModel;
class DependencyModel;

namespace Ui {
  class FormDeviserLanguage;
  }

class FormDeviserLanguage : public QWidget
{
  Q_OBJECT

public:
  explicit FormDeviserLanguage(QWidget *parent = 0);
  ~FormDeviserLanguage();

  void initializeFrom(DeviserLanguage* language);

public slots:
  void isPackageToggled();
  void markupNameChanged(QString);
  void prefixChanged(QString);
  void documentClassChanged(QString);
  void baseClassChanged(QString);
  void libraryNameChanged(QString);
  void majorChanged(QString);
  void minorChanged(QString);
  void revisionChanged(QString);
  void annotationElementNameChanged(QString);
  void listOfNameChanged(QString);
  void addVersion();
  void delVersion();
  void addDependency();
  void delDependency();

private:
  Ui::FormDeviserLanguage *ui;
  DeviserLanguage* mLanguage;

  DependencyModel* mpDependencies;
  QSortFilterProxyModel* mpDependenciesFilter;

  LanguageVersionModel* mpVersions;
  QSortFilterProxyModel* mpVersionsFilter;

  bool mbInitializing;
};

#endif // FORMDEVISERLANGUAGE_H
