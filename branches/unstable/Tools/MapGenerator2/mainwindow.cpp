#include <QDomDocument>
#include <QFile>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tile.h"

#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    refreshMap();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::getTileTypes() {
    PhysicsType *pType;
    GraphicsType *gType;
    QDomDocument doc;
    QFile file("types.xml");
    if (!file.open(QIODevice::ReadOnly)) {
        cerr << "Cannot open file" << endl;
        return;
    }
    if (!doc.setContent(&file)) {
        cerr << "Unusable file" << endl;
        file.close();
        return;
    }
    file.close();
    QDomElement types_e = doc.documentElement();
    if (types_e.tagName() != "types") {
        cerr << "Not a types element" << endl;
        return;
    }
    QDomNode typeList_n = types_e.firstChild();
    while (!typeList_n.isNull()) {
        QDomElement typeList_e = typeList_n.toElement();
        if (typeList_e.isNull()) {
            continue;
        }
        if (typeList_e.tagName() == "physics") {
            QDomNode physics_n = typeList_e.firstChild();
            while (!physics_n.isNull()) {
                QDomElement physics_e = physics_n.toElement();
                if (physics_e.isNull()) {
                    physics_n = physics_n.nextSibling();
                    continue;
                }
                if (physics_e.tagName() != "physics_type") {
                    continue;
                }
                pType = new PhysicsType;
                pType->hit = physics_e.attribute("hit").toStdString();
                pType->name = physics_e.attribute("name").toStdString();
                physicsTypes.push_back(pType);
            }
        } else if (typeList_e.tagName() == "graphics") {
            QDomNode gSrc_n = typeList_e.firstChild();
            while (!gSrc_n.isNull()) {
                QDomElement gSrc_e = gSrc_n.toElement();
                if (gSrc_e.isNull()) {
                    gSrc_n = gSrc_n.nextSibling();
                    continue;
                }
                if (gSrc_e.tagName() != "src") {
                    continue;
                }
                QDomNode gFile_n = gSrc_e.firstChild();
                while (!gFile_n.isNull()) {
                    QDomElement gFile_e = gFile_n.toElement();
                    if (gFile_e.isNull()) {
                        gFile_n = gFile_n.nextSibling();
                        continue;
                    }
                    if (gFile_e.tagName() != "file") {
                        continue;
                    }
                    QDomNode gType_n = gFile_e.firstChild();
                    while (!gType_n.isNull()) {
                        QDomElement gType_e = gType_n.toElement();
                        if (gType_e.isNull()) {
                            gType_n = gType_n.nextSibling();
                            continue;
                        }
                        if (gType_e.tagName() != "graphics_type") {
                            continue;
                        }
                        gType = new GraphicsType;
                        gType->src = gSrc_e.attribute("value").toStdString();
                        gType->filename = gFile_e.attribute("filenae").toStdString();
                        gType->fileWidth = gFile_e.attribute("width").toStdString();
                        gType->fileHeight = gFile_e.attribute("height").toStdString();
                        gType->name = gType_e.attribute("name").toStdString();
                        gType->x = gType_e.attribute("x").toStdString();
                        gType->y = gType_e.attribute("y").toStdString();
                        graphicsTypes.push_back(gType);
                    }
                }
            }
        }
    }
}

void MainWindow::refreshMap() {
    Tile *tile;
    int num_x = ui->grid_width->value();
    int num_y = ui->grid_height->value();
    tiles = (Tile**)malloc(sizeof(Tile*) * num_x * num_y);
    for (int x=0; x < num_x; ++x) {
        for (int y=0; y < num_y; ++y) {
            tile = new Tile(x, y);      // create new tile
            tiles[(num_x*y)+x] = tile;  // store tile pointer for later
            ui->map->addWidget(tile, y, x); // grid's x,y coords are backwards, DO NOT CHANGE!!!
            connect(ui->reset, SIGNAL(clicked()), tile, SLOT(reset()));
            connect(ui->clear, SIGNAL(clicked()), tile, SLOT(clear()));
            connect(this, SIGNAL(apply(int, int, int)), tile, SLOT(apply(int, int, int)));
        }
    }
    // TODO: populate physics & graphics dropdowns
}

void MainWindow::apply() {
    emit apply(ui->physics->currentIndex(), ui->graphics->currentIndex(), ui->rotation->currentIndex());
}

void MainWindow::save() {
    QDomDocument doc("Map");
    QDomElement map = doc.createElement("map");
    map.setAttribute("height", ui->grid_height->value());
    map.setAttribute("width", ui->grid_width->value());
    map.setAttribute("tileSize", ui->tile_size->value());
    for (int i=0; i < (ui->grid_width->value() * ui->grid_height->value()); ++i) {
        if (tiles[i]->exists()) {
            map.appendChild(tiles[i]->xml(doc));
        }
    }
    doc.appendChild(map);
    cout << doc.toString().toStdString() << endl;
}
