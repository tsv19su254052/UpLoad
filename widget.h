#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <QFile>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_selectFileButton_clicked();
    void on_uploadButton_clicked();
    void uploadFinished(QNetworkReply *reply);
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);

private:
    Ui::Widget *ui;
    QNetworkAccessManager *m_manager;
    QString m_fileName;
    QFile *m_file;
};

#endif // WIDGET_H
