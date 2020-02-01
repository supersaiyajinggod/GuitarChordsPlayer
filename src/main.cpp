#include <QtWidgets/qapplication.h>

#include "PlayerWeight.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    PlayerMainWindow* pPlayerMainWindow = new PlayerMainWindow();

    pPlayerMainWindow->show();

    return app.exec();
}