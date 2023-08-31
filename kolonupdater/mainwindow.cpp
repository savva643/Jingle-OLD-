#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPropertyAnimation>
#include <QGraphicsColorizeEffect>
#include <QMovie>
#include <QThread>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkReply>
#include "qdownloader.h"
#include <QProcess>
QLabel *my_label;
void delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->progressBar->setStyleSheet(
        "QProgressBar {"
        "   border: 1px #FFFFFF;"
        "   border-radius: 4px;"
        "   text-align: center;"
        "   background-color: transparent;"
        "   font: 900 22pt 'Segoe UI;'"
        "}"
        "QProgressBar::chunk {"
        "   background-color: #FFFFFF;"
        "   width: 1px;"
        "   border-radius: 4px;"
        "   margin: -0.1px;"
        "   border: 1px transparent;"
        "}"
        "QProgressBar::subcontrol:groove {"
        "   background: transparent;"
        "}"
        "QProgressBar::chunk::subcontrol {"
        "   color: white;"
        "}"
        "QProgressBar::subcontrol:text {"
        "   top: -3px;"
        "   position: relative;"
        "   color: white;"
        "}"
        );
    ui->progressBar->hide();

    QProcess p;
    p.start("pkill kompotkol.exe");

    QByteArray arr;

    arr = p.readAllStandardOutput();
    qDebug()<<arr;

    my_label = new QLabel(this);
    my_label->setGeometry(0,290,321,260);
    my_label->setStyleSheet("background-color: transparent;");
    QMovie *moviei = new QMovie(":/new/prefix1/image/loading.gif");
    moviei->setScaledSize(my_label->size());
    my_label->setMovie(moviei);
    moviei->start();
    ui->label_2->hide();
    ui->label->hide();
    my_label->hide();
    QMovie *movie = new QMovie(":/new/prefix1/image/kompot.gif");
    movie->setScaledSize(ui->label_2->size());
    QLabel *processLabel = ui->label_2;
    processLabel->setMovie(movie);
    movie->start();
    QGraphicsColorizeEffect *eEffect= new QGraphicsColorizeEffect(ui->widget);
    ui->widget->setGraphicsEffect(eEffect);

    QPropertyAnimation *paAnimation = new QPropertyAnimation(eEffect,"color");
    paAnimation->setEndValue(QColor(0, 0, 0));
    paAnimation->setStartValue(QColor(68, 68, 68));
    paAnimation->setDuration(2000);
    paAnimation->start();

    QTimer::singleShot(1000, this, &MainWindow::dsre);




}

void MainWindow::dsre()
{
    ui->label_2->show();
    ui->label->show();
    my_label->show();
    QGraphicsOpacityEffect *opacityEffect;
    opacityEffect = new QGraphicsOpacityEffect(this);
    ui->label_2->setGraphicsEffect(opacityEffect);
    QPropertyAnimation *animation = new QPropertyAnimation(opacityEffect, "opacity");
    animation->setDuration(1000); // Animation duration in milliseconds
        // Make the button transparent before showing it
    animation->setStartValue(0.0); // Fully transparent
    animation->setEndValue(1.0); // Destination position// Easing curve for smooth movement

    // Start the animation
    animation->start();


    QGraphicsOpacityEffect *opacityEffecti;
    opacityEffecti = new QGraphicsOpacityEffect(this);
    ui->label->setGraphicsEffect(opacityEffecti);
    QPropertyAnimation *animationi = new QPropertyAnimation(opacityEffecti, "opacity");
    animationi->setDuration(1000); // Animation duration in milliseconds
        // Make the button transparent before showing it
    animationi->setStartValue(0.0); // Fully transparent
    animationi->setEndValue(1.0); // Destination position// Easing curve for smooth movement

    // Start the animation
    animationi->start();


    QGraphicsOpacityEffect *opacityEffecte;
    opacityEffecte = new QGraphicsOpacityEffect(this);
    my_label->setGraphicsEffect(opacityEffecte);
    QPropertyAnimation *animatione = new QPropertyAnimation(opacityEffecte, "opacity");
    animatione->setDuration(1000); // Animation duration in milliseconds
        // Make the button transparent before showing it
    animatione->setStartValue(0.0); // Fully transparent
    animatione->setEndValue(1.0); // Destination position// Easing curve for smooth movement

    // Start the animation
    animatione->start();


    QTimer::singleShot(1000, this, &MainWindow::ftrgft);
}
void MainWindow::ftrgft()
{
    QString filePath = QDir::currentPath();
    qDebug() << filePath;
    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkRequest req( QUrl( QString("http://kompot.fun/kolversion.php") ) );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called
    if (reply->error() == QNetworkReply::NoError) {
        //success
        ui->label->setText("Получение информации");
        QString filik = "http://kompot.fun/software/jungle.zip";
        QDownloader *qte = new QDownloader();

        filePath.replace("/updater","/");
        qte->setFile(filik, filePath, ui->progressBar, ui->label, my_label, ui->label_2, ui->widget, this);
        delete reply;
    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
    }

}
MainWindow::~MainWindow()
{
    delete ui;
}

