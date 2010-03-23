#include "tile.h"
#include <QPixmap>
#include <sstream>
#include <qpalette.h>
#include <iostream>
#include <QDomDocument>
using namespace std;

Tile::Tile(QWidget *parent): QPushButton(parent), x(0), y(0), physics(0), graphics(0) {
    init();
}

Tile::Tile(int _x, int _y): QPushButton(), x(_x), y(_y), physics(0), graphics(0){
    init();
}

void Tile::init() {
    connect(this, SIGNAL(clicked()), this, SLOT(update()));
    setCheckable(true);
    setAutoFillBackground(true);
    setFixedWidth(10);
    setFixedHeight(10);
    update();
}


void Tile::apply(int _physics, int _graphics, int _rotation) {
    if (isChecked()) {
        physics = _physics;
        graphics = _graphics;
        rotation = _rotation;
        clear();
        update();
    }
}

void Tile::clear() {
    setChecked(false);
    update();
}

void Tile::update() {
    if (exists()) {
        setStyleSheet("background-color:red;");
    } else {
        setStyleSheet("background-color:pink;");
    }
}

void Tile::print() {
    std::cout << "Tile " << x << "x" << y << " -> physics:" << physics << ", graphics:" << graphics << "&" << rotation << std::endl;
}

void Tile::reset() {
    setChecked(false);
    physics = 0;
    graphics = 0;
    rotation = 0;
    update();
}

void Tile::toggle() {
    setChecked(!isChecked());
    update();
}

bool Tile::exists() {
    return (physics > 0 || graphics > 0);
}

int Tile::getX() {
    return x;
}

int Tile::getY() {
    return y;
}

QDomElement Tile::xml(QDomDocument &doc) {
    QDomElement tileElement = doc.createElement("tile");
    tileElement.setAttribute("x", x);
    tileElement.setAttribute("y", y);

    if (physics > 0) {
        QDomElement physicsElement = doc.createElement("physics");
        physicsElement.setAttribute("hit", "bounce");
        tileElement.appendChild(physicsElement);
    }

    if (graphics > 0) {
        QDomElement graphicsElement = doc.createElement("graphics");
        graphicsElement.setAttribute("source", "global");
        graphicsElement.setAttribute("filename", "map_textures.bmp");
        tileElement.appendChild(graphicsElement);
    }

    return tileElement;
}
