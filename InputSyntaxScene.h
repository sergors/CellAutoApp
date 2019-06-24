#ifndef INPUTSYNTAXSCENE_H
#define INPUTSYNTAXSCENE_H

#include <QTabWidget>

class InputSyntaxScene : public QTabWidget
{
    Q_OBJECT

public:
    InputSyntaxScene(QWidget *parent);
    void loadFromFile(char* fileName);
    char* getTextFromTab(int tabNumber);
};

#endif // INPUTSYNTAXSCENE_H
