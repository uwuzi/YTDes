#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineHistory>

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

private:
    Ui::MainWindow *ui;
    QWebEngineView* webView;
    const char* defaultSite;
    void loadPage();
    void webviewLoading(int progress);
    void webviewLoaded();
    void toggleSubscriptionView();
};

#endif // MAINWINDOW_H
