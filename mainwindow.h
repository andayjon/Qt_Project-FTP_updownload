#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ftp_client.h"
#include "myftpmanager.h"
#include <QMainWindow>
#include <QDialog>
#include <QFileDialog>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

typedef struct
{
    QString downfile_path = "";
    QString upfile_path = "";
    QString user = "user";
    QString passwd = "123456";
}Server_Info_st;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pButton5_clicked();

    void on_pButton1_clicked();

    void on_pButton3_clicked();

    void on_pButton4_clicked();

private:
    Ui::MainWindow *ui;
    Server_Info_st serverInfo;
    QNetworkReply *m_reply;
    QNetworkAccessManager *m_manager;
    QFile *m_file;
    FtpClient ftp_client;
    MyFtpManager ftp_manager;

private slots:
    void slot_readContent();
    void slot_replyFinished(QNetworkReply*);
    void slot_loadError(QNetworkReply::NetworkError);
    void slot_loadProgress(qint64,qint64);

    void on_comBox_currentIndexChanged(int index);
};

#endif // MAINWINDOW_H
