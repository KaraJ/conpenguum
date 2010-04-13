#include "main.h"

#include <Phonon/MediaObject>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Tuxspace");
    Phonon::MediaObject *music = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource("/root/Music/Alive.wav"));
    //music->play();
    Q_INIT_RESOURCE(menuitems);
    Panel *panel = new Panel();
    panel->setFocus();
    panel->show();

    return app.exec();
}
