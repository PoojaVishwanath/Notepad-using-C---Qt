#include <QApplication>
#include "notepad.h"
#include "replacewidget.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Notepad note;
    note.show();

    return app.exec();
}
