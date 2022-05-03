#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
#include <QUrl>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, &QNetworkAccessManager::finished, this, &Widget::uploadFinished);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_selectFileButton_clicked()
{
    m_fileName = QFileDialog::getOpenFileName(this, "Get Any File");
    ui->fileNameLineEdit->setText(m_fileName);
}

void Widget::on_uploadButton_clicked()
{
    m_file = new QFile(m_fileName);

    QFileInfo fileInfo(*m_file);
    QUrl url(ui->uploadUrlLineEdit->text() + fileInfo.fileName());
    url.setUserName("login");
    url.setPassword("password");
    url.setPort(21);

    if (m_file->open(QIODevice::ReadOnly))
    {
        QNetworkReply *reply = m_manager->put(QNetworkRequest(url), m_file);
        connect(reply, &QNetworkReply::uploadProgress, this, &Widget::uploadProgress);
    }

}

void Widget::uploadFinished(QNetworkReply *reply)
{
    if (!reply->error())
    {
        m_file->close();
        m_file->deleteLater();
        reply->deleteLater();
    }
}

void Widget::uploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    ui->progressBar->setValue(100 * bytesSent/bytesTotal);
}
