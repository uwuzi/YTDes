#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    defaultSite("https://www.youtube.com")
{
    ui->setupUi(this);
    webView = new QWebEngineView(ui->webviewFrame);
    webView->load(QUrl(defaultSite));
    toggleSubscriptionView();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);
    webView->resize(ui->webviewFrame->size());
}

void MainWindow::toggleSubscriptionView()
{
#if 1
    if (ui->subscriptionList->isHidden()) {
        ui->subscriptionList->show();
        ui->addChannelButton->show();
        ui->addChannelInput->show();
    }
    else {
        ui->subscriptionList->hide();
        ui->addChannelButton->hide();
        ui->addChannelInput->hide();
    }
#endif
}

void MainWindow::on_subscriptionsButton_clicked()
{
    toggleSubscriptionView();
}










