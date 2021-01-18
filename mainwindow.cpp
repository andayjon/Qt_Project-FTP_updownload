#include "mainwindow.h"
#include "ui_mainwindow.h"

const char  *user = "user";
const char *passwd = "123456000";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ftp_client = new FtpClient(this);
    ui->pButton3->setEnabled(false);
    ui->pButton4->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//选择本地保存路径
void MainWindow::on_pButton1_clicked()
{
    QString rs = QFileDialog::getSaveFileName(this, "save file dialog", "/home/zld/Downloads", "*.*");
    ui->lEdit2->setText(rs);
    if(!ui->lEdit2->text().isEmpty() && ui->lEdit2->text().contains(".")) {
        ui->pButton3->setEnabled(true);
    }else {
        ui->pButton3->setEnabled(false);
    }
}
//退出按钮
void MainWindow::on_pButton5_clicked()
{
    close();
}
//下载文件
void MainWindow::on_pButton3_clicked()
{
    /*
    m_file = new QFile(ui->lEdit2->text());
    if(!m_file->open(QIODevice::WriteOnly)){
        QMessageBox::information(NULL, tr("Information"), tr("Error saving file path locally!"), QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    m_manager = new QNetworkAccessManager(this);
    m_manager->setNetworkAccessible(QNetworkAccessManager::Accessible);
    QUrl url(ui->comBox->currentText()+ui->lEdit1->text());
    qDebug()<<tr("url = %1").arg(url.toString())<<endl;
    if(ui->comBox->currentIndex() == 2) {
        url.setPort(21);
        url.setUserName("zhang");
        url.setPassword("zhang123456");
        qDebug()<<tr("--->>>Connect FPT Server:39.102.43.157<<<---")<<endl;
    }else {
        url.setPort(21);
        url.setUserName(serverInfo.user);
        url.setPassword(serverInfo.passwd);
    }

    QNetworkRequest request(url);
    m_reply = m_manager->get(request);
    qDebug()<<tr("--->>>Debug1<<<---")<<endl;
    ui->progressBar->setValue(0);
    ui->progressBar->show();
    qDebug()<<tr("--->>>Debug2<<<---")<<endl;
//    connect((QObject *)reply, &QNetworkReply::readyRead, this, &MainWindow::slot_readContent);
//    connect(accessManager, &QNetworkAccessManager::finished, this, &MainWindow::slot_replyFinished);
//    connect(reply, &QNetworkReply::error, this, &MainWindow::slot_loadError);
//    connect(reply, &QNetworkReply::downloadProgress, this, &MainWindow::slot_loadProgress);
    connect((QObject *)m_reply, SIGNAL(readyRead()), this, SLOT(slot_readContent()));
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_replyFinished(QNetworkReply*)));
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(slot_loadError(QNetworkReply::NetworkError)));
    connect(m_reply, SIGNAL(downloadProgress(qint64 ,qint64)), this, SLOT(slot_loadProgress(qint64 ,qint64)));
    qDebug()<<tr("--->>>Debug3<<<---")<<endl;
    */

    if(ui->comBox->currentIndex() == 1) {
        ftp_client.FtpSetUserInfor("zhang", "zhang123456");
        ftp_client.FtpSetHostPort(ui->comBox->currentText());
        //ftp_client.FtpGet(ui->lEdit1->text(), ui->lEdit2->text());

        ftp_manager.setHost(ui->comBox->currentText());
        ftp_manager.setPort(21);
        ftp_manager.setUserName("zhang");
        ftp_manager.setPassword("zhang123456");

    }else {
        ftp_client.FtpSetUserInfor("user", "123456");
        ftp_client.FtpSetHostPort(ui->comBox->currentText());
        //ftp_client.FtpGet(ui->lEdit1->text(), ui->lEdit2->text());

        ftp_manager.setHost(ui->comBox->currentText());
        ftp_manager.setPort(21);
        ftp_manager.setUserName("user");
        ftp_manager.setPassword("123456");
    }
    ui->progressBar->setValue(0);
    QNetworkReply *pReply = ftp_manager.get(ui->lEdit1->text(), ui->lEdit2->text());
    connect(pReply, SIGNAL(downloadProgress(qint64,qint64)), SLOT(slot_loadProgress(qint64,qint64)));

}
//上传文件
void MainWindow::on_pButton4_clicked()
{

}
//下载时向本地文件写入数据
void MainWindow::slot_readContent()
{
    m_file->write(m_reply->readAll());
    qDebug()<<tr("--->>>Debug4<<<---")<<endl;
    m_reply->deleteLater();
    m_file->flush();
    m_file->close();
}
//删除指针，更新和关闭文件
void MainWindow::slot_replyFinished(QNetworkReply *)
{
    if(m_reply->error() == QNetworkReply::NoError) {
//        m_reply->deleteLater();
//        m_file->flush();
//        m_file->close();
        qDebug()<<tr("--->>>Debug5<<<---")<<endl;
    }else {
        QMessageBox::critical(NULL, tr("Error"), "Failed!!!");
    }
}
//更新进度条
void MainWindow::slot_loadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    qDebug()<<tr("loaded %1 of %2").arg(bytesSent).arg(bytesTotal)<<endl;
    ui->progressBar->setMaximum(bytesTotal); //最大值
    ui->progressBar->setValue(bytesSent);  //当前值

}
//传输中的错误输出
void MainWindow::slot_loadError(QNetworkReply::NetworkError)
{
    qDebug()<<"Error: "<<m_reply->error();
}

void MainWindow::on_comBox_currentIndexChanged(int index)
{
    if(index == 1) {
        ui->lEdit1->setText("test.txt");
    }else {
        ui->lEdit1->setText("update_info.txt");
    }
}
