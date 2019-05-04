#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow (parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{

}

void MainWindow::on_pushButton_clicked()
{
    QString text = ui->programText->toPlainText();
    Scaner* sc = new Scaner(text.toStdString().c_str());
    LEX l = "";
    int lex = 199;
    lex = sc->doScan(l);
    QMessageBox messageBox;
    messageBox.setText(QString::number(lex));
    messageBox.exec();
}
