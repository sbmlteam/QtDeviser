#ifndef DIALOGUML_H
#define DIALOGUML_H

#include <QDialog>

namespace Ui {
class DialogUML;
}

class MainWindow;
class QGraphicsScene;
class QNetworkReply;
class QNetworkAccessManager;
class QResizeEvent;
class QWheelEvent;

class DialogUML : public QDialog
{
  Q_OBJECT

public:
  explicit DialogUML(QWidget *parent = 0);
  ~DialogUML();

  void loadYuml(const QString& yuml);
  void exportImage(const QString& filename, const QString& extension);

public slots:
  void updateGraph();
  void saveAs();
  void styleChanged();
  void fitChanged();
  void downloadFinished(QNetworkReply *reply);
  void downloadImageFinished(QNetworkReply *reply);

protected:
  virtual void resizeEvent(QResizeEvent * event);

private:
  Ui::DialogUML *ui;
  QGraphicsScene* mpScene;
  QNetworkAccessManager* mpManager;
  QNetworkAccessManager* mpDownloadManager;
  QString mCurrent;
  QString mFileName;
};

#endif // DIALOGUML_H
