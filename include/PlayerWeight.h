#ifndef PLAYER_WEIGHT_H
#define PLAYER_WEIGHT_H

#include <string>

#include "ui_gui.h"

#include <QMainWindow>
 
namespace Ui {
    class MainWindow;
}
 
class PlayerMainWindow : public QMainWindow
{
    Q_OBJECT
 
public:
    explicit PlayerMainWindow(QWidget *parent = 0);
    ~PlayerMainWindow();
 
private:
    Ui::MainWindow *ui;
    QString chordsPath_;
    QImage* pChordsImage_ = nullptr;

    int openImage();
 
private slots:
    void openFile();
 
};

#endif //PLAYER_WEIGHT_H