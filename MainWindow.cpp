#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow (parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString text = ui->programText1->toPlainText();
    Scaner *sc = new Scaner(text.toStdString().c_str());
    Parser *parser = new Parser(sc);
    Interpret *interpret = new Interpret(parser);
    LoadConnector *loadConnector = new LoadConnector(interpret);
    ui->mainGlScene->setLoadConnector(loadConnector);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btnStartStopClicked()
{
    QMessageBox messageBox;
    messageBox.setText("STARTSTOP");
    messageBox.exec();
}

void MainWindow::btnCompileClicked()
{
    QString text = ui->programText1->toPlainText();
    Scaner *sc = new Scaner(text.toStdString().c_str());
    Parser *pars = new Parser(sc);
    LEX l = "";
    int lex = 199;
    lex = sc->doScan(l);
    /*QMessageBox messageBox;
    messageBox.setText(QString::number(lex) + "   " + l);
    messageBox.exec();*/


}
void MainWindow::btnStopClicked()
{
    QMessageBox messageBox;
    messageBox.setText("STOP");
    messageBox.exec();
}
void MainWindow::btnStartClicked()
{
    /*QMessageBox messageBox;
    messageBox.setText("START");
    messageBox.exec();*/

}
void MainWindow::btnOpenNewClicked()
{
    QMessageBox messageBox;
    messageBox.setText("OpenNew");
    messageBox.exec();
}

void MainWindow::btnActivateClicked()
{
    QMessageBox messageBox;
    messageBox.setText("ACTIVATE");
    messageBox.exec();
}

