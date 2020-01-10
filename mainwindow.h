#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineHistory>
#include <QListWidget>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QDialog>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "channel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);

private slots:
    void on_subscriptionsButton_clicked();
    void on_addChannelButton_clicked();
    void on_addChannelInput_returnPressed();
    void on_channelList_itemEntered(QListWidgetItem *item);
    void on_channelList_itemDoubleClicked(QListWidgetItem *item);
    void on_removeButton_clicked();
    void on_homeButton_clicked();
    void on_settingsButton_clicked();
    void on_backButton_clicked();
    void on_forwardButton_clicked();

    void on_downloadButton_clicked();

private:
    Ui::MainWindow *ui;
    QWebEngineView* webView;
    std::vector<Channel*> savedChannelVec;
    QString confFileName;
    const char* defaultSite;
    const unsigned int MAX_USERNAME_LENGTH = 32;

    QString getUsername();
    void readConfFile();
    void writeToConfFile(Channel& c);
    void removeFromConfFile(Channel* c);
    void removeFromChannelList(int n);
    void toggleSubscriptionView();
    bool saveChannel(const QString& name);
    bool checkStringBlank(const QString& name);
    void loadFromChannelList(unsigned int index);
};

#endif // MAINWINDOW_H
