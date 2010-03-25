#ifndef TILE_H
#define TILE_H

#include <QDomDocument>
#include <QPushButton>
#include <sstream>

class Tile : public QPushButton
{
Q_OBJECT
private:
    int x;
    int y;
    int physics;
    int graphics;
    int rotation;
    void apply();
    void init();
public:
    explicit Tile(QWidget *parent = 0);
    Tile(int, int);
    int getX();
    int getY();
    int getPhysics();
    int getGraphics();
    int getRotation();
    bool exists();
signals:

public slots:
    void update();
    void reset();
    void toggle();
    void apply(int, int, int);
    void print();
    void clear();
};

#endif // TILE_H
