#ifndef QDOWNLOADER_H
#define QDOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QStringList>
#include <QDir>
#include <QProgressBar>
#include <QProcess>
#include <QLabel>
#include "mainwindow.h"
class QDownloader : public QObject
{
    Q_OBJECT
public:
    explicit QDownloader(QObject *parent = 0);
    virtual ~QDownloader();
    void setFile(QString fileURL, QString filepatch, QProgressBar *progressBar, QLabel *domlound, QLabel *proh, QLabel *logo, QWidget *ggopp, MainWindow *qms);

private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QFile *file;
    QProgressBar *progressBari;
    QLabel *domloundi;
    QString saveFilePath;
    QString filePathi;
    QLabel *prohi;
    QLabel *logoi;
    QWidget *ggoppi;
    MainWindow *qmsi;
private slots:
    void onDownloadProgress(qint64,qint64);
    void onFinished(QNetworkReply*);
    void onReadyRead();
    void onReplyFinished();
};

#endif // QDOWNLOADER_H
