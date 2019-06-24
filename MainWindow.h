#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "interpreter/scaner/scaner.h"
#include "interpreter/parser/parser.h"
#include "interpreter/interpret.h"

namespace Ui {
    class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void btnStopClicked();
    void btnStartStopClicked();
    void btnStartClicked();
    void btnOpenNewClicked();
    void btnCompileClicked();
    void btnActivateClicked();


private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
