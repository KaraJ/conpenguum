#include <QDomDocument>
#include <QFile>
#include <sstream>
#include <QFileDialog>
#include <iostream>
#include <QTextStream>
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
    getTileTypes();
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

    // Read physics types
    QDomNodeList physics_l = types_e.elementsByTagName("physics");
    for (int pi=0; pi < physics_l.count(); ++pi) {
        QDomElement physics_e = physics_l.item(pi).toElement();
        QDomNodeList pType_list = physics_e.elementsByTagName("physics_type");
        for (int pti=0; pti < pType_list.count(); ++pti) {
            QDomElement pType_e = pType_list.item(pti).toElement();
            pType = new PhysicsType;
            pType->hit  = pType_e.attribute("hit");
            pType->name = pType_e.attribute("name");
            physicsTypes.push_back(pType);
            ui->physics->addItem(pType->name, QVariant());
        }
    }

    // Read graphics types
    QDomNodeList graphics_l = types_e.elementsByTagName("graphics");
    for (int gi=0; gi < graphics_l.count(); ++gi) {
        QDomElement graphics_e = graphics_l.item(gi).toElement();
        QDomNodeList gSrc_l = graphics_e.elementsByTagName("src");
        for (int gsi=0; gsi < gSrc_l.count(); ++gsi) {
            QDomElement gSrc_e = gSrc_l.item(gsi).toElement();
            QDomNodeList gFile_l = gSrc_e.elementsByTagName("file");
            for (int gfi=0; gfi < gFile_l.count(); ++gfi) {
                QDomElement gFile_e = gFile_l.item(gfi).toElement();
                QDomNodeList gType_l = gFile_e.elementsByTagName("graphics_type");
                for (int gti=0; gti < gType_l.count(); ++gti) {
                    QDomElement gType_e = gType_l.item(gti).toElement();
                    gType = new GraphicsType;
                    gType->src        = gSrc_e.attribute("value");
                    gType->filename   = gFile_e.attribute("filename");
                    gType->fileWidth  = gFile_e.attribute("width").toInt();
                    gType->fileHeight = gFile_e.attribute("height").toInt();
                    gType->name       = gType_e.attribute("name");
                    gType->x          = gType_e.attribute("x").toInt();
                    gType->y          = gType_e.attribute("y").toInt();
                    graphicsTypes.push_back(gType);
                    ui->graphics->addItem(gType->name, QVariant());
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
    stringstream sString;
    map.setAttribute("height", ui->grid_height->value());
    map.setAttribute("width", ui->grid_width->value());
    map.setAttribute("tileSize", ui->tile_size->value());
    for (int i=0; i < (ui->grid_width->value() * ui->grid_height->value()); ++i) {
        if (tiles[i]->exists()) {
            QDomElement tile_e = doc.createElement("tile");
            tile_e.setAttribute("x", tiles[i]->getX());
            tile_e.setAttribute("y", tiles[i]->getY());

            if (tiles[i]->getPhysics() > 0) {
                QDomElement physics_e = doc.createElement("physics");
                PhysicsType *pType = physicsTypes[tiles[i]->getPhysics()-1];
                physics_e.setAttribute("hit", pType->hit);
                tile_e.appendChild(physics_e);
            }

            if (tiles[i]->getGraphics() > 0) {
                QDomElement graphics_e = doc.createElement("graphics");
                GraphicsType *gType = graphicsTypes[tiles[i]->getGraphics()-1];
                graphics_e.setAttribute("source", gType->src);
                graphics_e.setAttribute("filename", gType->filename);
                graphics_e.setAttribute("rotation", tiles[i]->getRotation());
                // Bottom Left Horizontal
                sString.str("");
                sString << gType->x << "/" << gType->fileWidth;
                graphics_e.setAttribute("blh", QString(sString.str().c_str()));
                // Bottom Left Vertical
                sString.str("");
                sString << gType->y << "/" << gType->fileHeight;
                graphics_e.setAttribute("blv", QString(sString.str().c_str()));
                // Top Right Horizontal
                sString.str("");
                sString << gType->x+1 << "/" << gType->fileWidth;
                graphics_e.setAttribute("trh", QString(sString.str().c_str()));
                // Top Right Vertical
                sString.str("");
                sString << gType->y+1 << "/" << gType->fileHeight;
                graphics_e.setAttribute("trv", QString(sString.str().c_str()));
                tile_e.appendChild(graphics_e);
            }
            map.appendChild(tile_e);
        }
    }
    doc.appendChild(map);
    QFile file(QFileDialog::getSaveFileName(this, tr("Save Map File"), "./map.xml", tr("XML (*.xml)")));

    if(!file.open(QIODevice::WriteOnly)) {
      cerr << "Failed to open file." << endl;
      return;
    }
    QTextStream fileStream(&file);
    fileStream << doc.toString() << endl;
    file.close();
    cout << doc.toString().toStdString() << endl;
}
