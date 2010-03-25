#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDomDocument>
#include <string>
#include <vector>
#include "tile.h"

using namespace std;

typedef struct {
    QString name;
    QString hit;
} PhysicsType;

typedef struct {
    QString name;
    QString src;
    QString filename;
    int x;
    int y;
    int fileWidth;
    int fileHeight;
} GraphicsType;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    Tile **tiles;
    vector<PhysicsType*> physicsTypes;
    vector<GraphicsType*> graphicsTypes;
    void getTileTypes();
public slots:
    void refreshMap();
    void apply();
    void save();
signals:
    void apply(int, int, int);
};

#endif // MAINWINDOW_H
