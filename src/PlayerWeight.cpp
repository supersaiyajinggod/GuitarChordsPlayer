#include <iostream>

#include <QtWidgets/qfiledialog.h>
#include <QMessageBox>

#include "PlayerWeight.h"


PlayerMainWindow::PlayerMainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
}
 
PlayerMainWindow::~PlayerMainWindow()
{
    delete ui;
}

void PlayerMainWindow::openFile() {
    chordsPath_ = QFileDialog::getOpenFileName(
        this, ("Open Chords File"), QDir::currentPath(), "Chords ( *.png )");
    if (chordsPath_.isEmpty()) {
        return;
    }

    std::string chordsFile = chordsPath_.toStdString();
    std::cout << chordsFile << std::endl;

    openImage();
}

int PlayerMainWindow::openImage() {
    if (pChordsImage_ != nullptr) {
        delete pChordsImage_;
        pChordsImage_ = nullptr;
        pChordsImage_ = new QImage(chordsPath_); 
        std::cout << "load success! 111111111" << std::endl;
    } else {
        pChordsImage_ = new QImage(chordsPath_); 
        std::cout << "load success! 222222222" << std::endl;
        std::cout << "pChordsImage_->byteCount(): " << pChordsImage_->byteCount() << std::endl;
        // return false;
    }

    QPixmap pixmap(QPixmap::fromImage(*pChordsImage_));
    pixmap.scaled(QSize(ui->label->width(),ui->label->height()),Qt::KeepAspectRatioByExpanding);
    // ui->label->resize(pChordsImage_->width(),pChordsImage_->height());
    ui->label->setPixmap(pixmap);
    std::cout << "ui set success! 3333333" << std::endl;

    return true;
}