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
    confFileName = "/home/tekipaki/.config/ytdconf";
    readConfFile();
    toggleSubscriptionView();
}

MainWindow::~MainWindow()
{
    for (unsigned int i = 0; i < savedChannelVec.size(); i++) {
        free(savedChannelVec.at(i));
    }
    delete ui;
}

void MainWindow::readConfFile()
{
    QTextStream out(stdout);
    QFile file(confFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        out << "FUCK!!!" << endl;
        return;
    }
    QString line;
    while (!file.atEnd()) {
        line = file.readLine();
        if (line.front().isSpace()) {
           continue;
        }
        Channel *channel = new Channel;
        channel->nickname = line;
        line = file.readLine();
        channel->url.setUrl(line);
        savedChannelVec.push_back(channel);
    }
    for (unsigned int i = 0; i < savedChannelVec.size(); i++) {
        ui->channelList->addItem(savedChannelVec.at(i)->nickname);
    }
}

void MainWindow::writeToConfFile(Channel& c)
{
    QFile file(confFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //out << "FUCK!!!" << endl;
        return;
    }
    QString name = c.nickname;
    QString url = c.url.url();
    //file.write(c.nickname);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);
    webView->resize(ui->webviewFrame->size());
}

void MainWindow::toggleSubscriptionView()
{
#if 1
    if (ui->channelList->isHidden()) {
        ui->channelList->show();
        ui->addChannelButton->show();
        ui->addChannelInput->show();
    }
    else {
        ui->channelList->hide();
        ui->addChannelButton->hide();
        ui->addChannelInput->hide();
    }
#endif
}

bool MainWindow::checkStringBlank(const QString& name) {
    for (int i = 0; i < name.count(); i++) {
        if (name.at(i) != ' ') {
            return 0;
        }
    }
    return 1;
}

bool MainWindow::saveChannel(const QString& name)
{
    if (name.isNull() || name.isEmpty() || checkStringBlank(name)) {
        ui->addChannelInput->clear();
        return 0;
    }

    for (int i = 0; i < ui->channelList->count(); i++) {
        if (name == ui->channelList->itemAt(0,i)->text()) {
            ui->addChannelInput->clear();
            return 0;
        }
    }
    Channel *newChannel = new Channel;
    newChannel->nickname = name.trimmed();
    newChannel->url = webView->url();
    savedChannelVec.push_back(newChannel);
    ui->channelList->addItem(newChannel->nickname);
    ui->addChannelInput->clear();
    return 1;
}

//bool MainWindow::removeChannel(const)

void MainWindow::on_subscriptionsButton_clicked()
{
    toggleSubscriptionView();
}

void MainWindow::on_addChannelButton_clicked()
{
    saveChannel(ui->addChannelInput->text());
}

void MainWindow::on_addChannelInput_returnPressed()
{
    saveChannel(ui->addChannelInput->text());
}

void MainWindow::loadFromChannelList(int index)
{
    webView->load(savedChannelVec.at(index)->url);
    toggleSubscriptionView();
}

void MainWindow::on_channelList_itemEntered(QListWidgetItem *item)
{
    loadFromChannelList(ui->channelList->currentRow());
}

void MainWindow::on_channelList_itemDoubleClicked(QListWidgetItem *item)
{
    loadFromChannelList(ui->channelList->currentRow());
}






