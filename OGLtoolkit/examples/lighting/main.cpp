#include <QApplication>
#include <iostream>
#include "QtView.h"


int main(int argc, char *argv[]) {
        QApplication app(argc, argv);

        QtView view;
        view.show();


        return app.exec();
}

