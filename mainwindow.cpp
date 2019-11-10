#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    //defaultSite("https://www.youtube.com");
    defaultSite("https://invidio.us")
{
    ui->setupUi(this);
    this->setWindowTitle("YTDes");
    QIcon qIcon;
    qIcon.addFile("/home/tekipaki/Programming/qt-projects/ytd/assets/burger-icon.png");
    this->setWindowIcon(qIcon);
    webView = new QWebEngineView(ui->webviewFrame);
    webView->load(QUrl(defaultSite));
    confFileName = "/home/tekipaki/.config/ytdconf";
    readConfFile();
    //ui->channelList->setMaximumWidth(100);
    ui->channelList->setAlternatingRowColors(1);
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
        channel->nickname = line.remove(QRegExp("\\n"));
        line = file.readLine();
        channel->url.setUrl(line.remove(QRegExp("\\n")));
        savedChannelVec.push_back(channel);
    }
    for (unsigned int i = 0; i < savedChannelVec.size(); i++) {
        ui->channelList->addItem(savedChannelVec.at(i)->nickname);
    }
    //ui->channelList->setSortingEnabled(1);
    //ui->channelList->sortItems(Qt::SortOrder::AscendingOrder);
    file.close();
}

void MainWindow::writeToConfFile(Channel& c)
{
    QFile file(confFileName);
    if (!file.open(QIODevice::Append | QIODevice::Text)){
            return;
    }
    file.write(c.nickname.toUtf8());
    file.write("\n");
    file.write(c.url.url().toUtf8());
    file.write("\n");
    file.close();
}

void MainWindow::removeFromConfFile(Channel* c)
{
    QFile f(confFileName);
    if(f.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QString s;
        QTextStream t(&f);
        while(!t.atEnd()) {
            QString line = t.readLine();
            if(!line.contains(c->nickname) && !line.contains(c->url.toString())) {
                s.append(line + "\n");
            }
        }
    f.resize(0);
    t << s;
    f.close();
    }
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
        ui->removeButton->show();
    }
    else {
        ui->channelList->hide();
        ui->addChannelButton->hide();
        ui->addChannelInput->hide();
        ui->removeButton->hide();
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
    writeToConfFile(*newChannel);
    return 1;
}

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

void MainWindow::loadFromChannelList(unsigned int index)
{
    webView->load(savedChannelVec.at(index)->url);
    toggleSubscriptionView();
}

void MainWindow::on_channelList_itemEntered(QListWidgetItem *item)
{
    loadFromChannelList(static_cast<unsigned int> (ui->channelList->currentRow()));
}

void MainWindow::on_channelList_itemDoubleClicked(QListWidgetItem *item)
{
    loadFromChannelList(static_cast<unsigned int> (ui->channelList->currentRow()));
}

void MainWindow::on_removeButton_clicked()
{
    int n = ui->channelList->currentRow();
    if (n > -1) {
        removeFromConfFile(savedChannelVec.at(n));
        ui->channelList->takeItem(n);
        savedChannelVec.erase(savedChannelVec.begin()+n);
    }
}

void MainWindow::on_homeButton_clicked()
{
    webView->load(QUrl(defaultSite));
    //webView->load(QUrl("https://invidio.us"));
}

void MainWindow::on_settingsButton_clicked()
{
#if 0
    QWidget *wdg = new QWidget;
    QListWidget *listWidget = new QListWidget;
    QPushButton *pb = new QPushButton;
    listWidget->setParent(wdg);
    pb->setParent(wdg);
    /*
    listWidget->layout()->activate();
    wdg->layout()->addWidget(listWidget);
    */
    wdg->show();
    //hide();
#endif
}

void MainWindow::on_backButton_clicked()
{
    webView->back();
}

void MainWindow::on_forwardButton_clicked()
{
    webView->forward();
}

void MainWindow::on_downloadButton_clicked()
{
    pid_t pid = fork();
    if (pid == 0) {
        QString cmd = "youtube-dl -o '~/%(title)s.%(ext)s' ";
        cmd.append(webView->url().toString());
        system(cmd.toStdString().c_str());
    }
    //qDebug() <<  currentUrl << endl;
    //qDebug() <<  cmd << endl;
}































