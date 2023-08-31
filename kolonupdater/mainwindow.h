#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDir>
#include <QProcess>
#include <QCoreApplication>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void dsre();
    void ftrgft();

public slots:
    void delayi( int millisecondsToWait )
    {
        QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
        while( QTime::currentTime() < dieTime )
        {
            QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
        }
    }
    void startAsyncTask()
    {
        // Simulating an async task using a QTimer
        QTimer::singleShot(1000, this, &MainWindow::asyncTaskFinished);
    }
    void startapp(){
        QString filePath = QDir::currentPath();
         filePath.replace("/updater","/");
        QProcess::startDetached(filePath+"/kompotkol.exe", QStringList() << "any_argument");
        this->close();
    }

signals:
    void asyncTaskFinished();
};
#endif // MAINWINDOW_H
