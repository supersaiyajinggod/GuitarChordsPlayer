#ifndef PLAYER_WEIGHT_H
#define PLAYER_WEIGHT_H

#include <string>

#include "ui_gui.h"

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>
 
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
    void keyPressEvent(QKeyEvent * event);

    Ui::MainWindow *ui;
    QString chordsPath_;
    QImage * pChordsImage_ = nullptr;
    QTimer * pTimer = nullptr;

    bool openImage();

    int i_ = 0;
    bool pause = false;
    
 
private slots:
    void openFile();
 
};

#endif //PLAYER_WEIGHT_H