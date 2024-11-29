#include "application.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
        MainWindow w;
    Application b(&w);

    w.show();
    return a.exec();
}
