#include "qdownloader.h"
#include <QApplication>
#include <QLabel>
#include <QPixmap>
#include <QTime>
#include <QSettings>
#include <QPushButton>
#include <QGraphicsOpacityEffect>
#include <QGraphicsColorizeEffect>
#include <QPropertyAnimation>

bool fileExistsi(QString path) {
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}

QDownloader::QDownloader(QObject *parent) :
    QObject(parent)
{
    manager = new QNetworkAccessManager;
}

QDownloader::~QDownloader()
{
    manager->deleteLater();
}

void QDownloader::setFile(QString fileURL, QString filepatch, QProgressBar *progressBar, QLabel *domlound, QLabel *proh, QLabel *logo, QWidget *ggopp, MainWindow *qms)
{
    QString filePath = fileURL;
    prohi = proh;
    logoi = logo;
    qmsi = qms;
    prohi->hide();
    domlound->hide();
    ggoppi = ggopp;
    QStringList filePathList = filePath.split('/');
    QString fileName = filePathList.at(filePathList.count() - 1);
    saveFilePath = QString(filepatch + "/" + fileName);
    QNetworkRequest request;
    request.setUrl(QUrl(fileURL));
    reply = manager->get(request);
    filePathi = filepatch;
    file = new QFile;
    file->setFileName(saveFilePath);
    file->open(QIODevice::WriteOnly);
    progressBari = progressBar;
    domloundi = domlound;
    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(onDownloadProgress(qint64,qint64)));
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(onFinished(QNetworkReply*)));
    connect(reply,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
    connect(reply,SIGNAL(finished()),this,SLOT(onReplyFinished()));
    progressBar->show();
}

void QDownloader::onDownloadProgress(qint64 bytesRead,qint64 bytesTotal)
{
    qDebug(QString::number(bytesRead).toLatin1() +" - "+ QString::number(bytesTotal).toLatin1());


    qDebug()<< progressBari->value();
    progressBari->setMaximum(bytesTotal);
    progressBari->setValue(bytesRead);
}

void delayp( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

void QDownloader::onFinished(QNetworkReply * reply)
{
    switch(reply->error())
    {
    case QNetworkReply::NoError:
    {
        qDebug("file is downloaded successfully.");
        QString zipFilePath = saveFilePath;

        QString outputDir = filePathi;
        QStringList filePathList = zipFilePath.split('/');
        QString fileName = filePathList.at(filePathList.count() - 1);
        QString sgas = "tar -xf "+zipFilePath+" -C "+outputDir;
        QByteArray ba = sgas.toLocal8Bit();
        const char *c_str2 = ba.data();
        // Create the unzip command
        system(c_str2);

        QGraphicsColorizeEffect *eEffect= new QGraphicsColorizeEffect(ggoppi);
        ggoppi->setGraphicsEffect(eEffect);

        QPropertyAnimation *paAnimation = new QPropertyAnimation(eEffect,"color");
        paAnimation->setStartValue(QColor(0, 0, 0));
        paAnimation->setEndValue(QColor(68, 68, 68));
        paAnimation->setDuration(2000);
        paAnimation->start();

        QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(this);
        progressBari->setGraphicsEffect(opacityEffect);
        logoi->setGraphicsEffect(opacityEffect);
        QPropertyAnimation *animation = new QPropertyAnimation(opacityEffect, "opacity");
        animation->setDuration(1000); // Animation duration in milliseconds
            // Make the button transparent before showing it
        animation->setStartValue(1.0); // Fully transparent
        animation->setEndValue(0.0); // Destination position// Easing curve for smooth movement

        // Start the animation
        animation->start();

        connect(paAnimation, &QPropertyAnimation::finished, qmsi, &MainWindow::startapp);



    }
    default:{
        qDebug(reply->errorString().toLatin1());
    };
    }

    if(file->isOpen())
    {
        file->close();
        file->deleteLater();
    }
}

void QDownloader::onReadyRead()
{
    file->write(reply->readAll());
}

void QDownloader::onReplyFinished()
{

    file->close();
    file->deleteLater();

}
