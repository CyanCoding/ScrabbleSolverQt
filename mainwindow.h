#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>       // std::vector
#include <future>       // std::future
#include <unordered_set>    // std::unordered_set

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    struct xy { // Used for storing two-dimensional information in an array
        int x, y;
    };

private slots:
    void on_pushButton_clicked();
    void on_actionClear_board_triggered();
    void on_previousButton_clicked();
    void on_nextButton_clicked();

    void on_prune_clicked();

private:
    Ui::MainWindow *ui;

    std::future<std::vector<std::unordered_set<QString>>> dict_async;   // Async for reading dictionary words
    std::vector<std::unordered_set<QString>> dictionary;                // The vector that dict_async reads into
    std::vector<std::vector<std::vector<QString>>> all_boards;          // Every board we've found
    unsigned long board_number;                                         // The number of allBoards to access
};
#endif // MAINWINDOW_H
