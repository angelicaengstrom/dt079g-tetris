#include <QApplication> //Hanterar widgets, event hanterare, musrörelser och våra fönster
#include "window.h"

int main(int argc, char *argv[]) //All exekvation sker här
{
    QApplication a(argc, argv);
    Window w;
    //Öppnar själva rutan till widgeten
    w.show();

    return QApplication::exec();
}
