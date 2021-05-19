#include <iostream>

#include <QtWidgets/qfiledialog.h>
#include <QMessageBox>
#include <QAbstractScrollArea>
#include <QScrollBar>

#include "PlayerWeight.h"


PlayerMainWindow::PlayerMainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    pTimer = new QTimer(this);

    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(pTimer, &QTimer::timeout, [&](){
        if (!pause)
            ui->scrollArea->verticalScrollBar()->setValue(++i_ > 0 ? i_ : 0);
        // ui->scrollArea->verticalScrollBar()->setValue(!pause ? (i_ > 0 ? ++i_ : 0) : (i_ > 0 ? i_ : 0));
    });
}
 
PlayerMainWindow::~PlayerMainWindow()
{
    delete ui;
}

void PlayerMainWindow::keyPressEvent(QKeyEvent * event) {
    switch (event->key()) {
        case Qt::Key_Space:
            pause = !pause;
            break;
        default:
            break;
    }
}

void PlayerMainWindow::openFile() {
    chordsPath_ = QFileDialog::getOpenFileName(
        this, ("Open Chords File"), QDir::currentPath()+"/../chords/");
    if (chordsPath_.isEmpty()) {
        return;
    }

    std::string chordsFile = chordsPath_.toStdString();
    std::cout << chordsFile  << " " << chordsFile.find('.') << std::endl;
    auto totalTime = chordsFile.substr(chordsFile.find('.') - 4, 4);
    auto totalTimeInt = std::atoi(totalTime.c_str());
    const auto min = totalTimeInt / 100;
    const auto second = (totalTimeInt- min * 100) % 60;
    std::cout << "Total time: " << totalTime << " $$" << min << " ##" << second << std::endl;

    if (openImage()) {
        if (pTimer != nullptr) {
            pTimer->stop();
            pTimer->start((min * 60 + second) * 1000 / pChordsImage_->height());
            i_ = -200;
        }
    }
}

bool PlayerMainWindow::openImage() {
    if (pChordsImage_ != nullptr) {
        delete pChordsImage_;
        pChordsImage_ = nullptr;
        pChordsImage_ = new QImage(chordsPath_); 
    } else {
        pChordsImage_ = new QImage(chordsPath_); 
        std::cout << "pChordsImage_->byteCount(): " << pChordsImage_->height() << std::endl;
        // return false;
    }

    QPixmap pixmap(QPixmap::fromImage(*pChordsImage_));
    // pixmap.scaled(QSize(ui->label->width(),ui->label->height()),Qt::KeepAspectRatioByExpanding);
    // ui->scrollAreaWidgetContents->setMinimumSize(QSize(400, 400));
    ui->label->setPixmap(pixmap);
    ui->label->resize(pChordsImage_->width(),pChordsImage_->height());

    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
    // ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->verticalScrollBar()->maximum()/2);
    // std::cout << "!!!!!" << ui->scrollArea->verticalScrollBar()->maximum() << std::endl;

    pause = false;

    return true;
}