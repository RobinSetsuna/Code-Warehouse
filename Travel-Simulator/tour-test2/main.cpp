#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setAutoFillBackground(true);
    w.writeFile("\nmain window start.");
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":///image/bg.jpg")));
    w.setPalette(palette);
    w.clean();
    w.show();
    w.getText();

    return a.exec();
}




