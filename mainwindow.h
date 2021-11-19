#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>       // std::vector
#include <future>       // std::future

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    std::future<std::vector<QString>> dict_async;   // Async for reading dictionary words
    std::vector<QString> dictionary;                // The vector that dict_async reads into
};
#endif // MAINWINDOW_H
