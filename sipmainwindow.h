#ifndef SIPMAINWINDOW_H
#define SIPMAINWINDOW_H

#include <QMainWindow>
#include "ExosipServer.h"

namespace Ui {
class SIPMAINWINDOW;
}

class SIPMAINWINDOW : public QMainWindow
{
    Q_OBJECT

public:
    explicit SIPMAINWINDOW(QWidget *parent = nullptr);
    ~SIPMAINWINDOW();

private slots:
    void on_btnPlayBack_clicked();

    void on_btnPlay_clicked();

    void on_btnLeft_clicked();

    void on_btnPause_clicked();

    void on_btnFastPlay_clicked();

    void on_btnSlowPlay_clicked();

    void on_btnLive_clicked();

    void on_btnUp_clicked();

    void on_btnDown_clicked();

    void on_btnRight_clicked();

    void on_btnZoomLarge_clicked();

    void on_btnZoomLittle_clicked();

    void on_btnStop_clicked();

    void on_btnRecord_clicked();

    void on_btnStopRecord_clicked();

    void on_btnSearchRecord_clicked();

    void on_btnSetGuard_clicked();

    void on_btnAlarm_clicked();

    void on_btnResetGuard_clicked();

    void on_btnResetAlarm_clicked();

    void on_btnCatalog_clicked();

    void on_btnDeviceInfo_clicked();

    void on_btnDeviceStart_clicked();

    void on_btnKeepLive_clicked();

    void on_btnDeviceStatus_clicked();

    void on_btnRegist_clicked();

    void on_btnCancleRegist_clicked();

    void on_btnBye_clicked();

    void on_btnDownload_clicked();

    void on_btnSendDevInfo_clicked();

private:
    Ui::SIPMAINWINDOW *ui;
    ExosipServer *server = nullptr;
};

#endif // SIPMAINWINDOW_H
