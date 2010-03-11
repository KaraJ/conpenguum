import sys
from PyQt4 import QtGui, QtCore
import random

width = int(sys.argv[1])
height = int(sys.argv[2])

physics_types = [
    {
        'name': 'Space',
        'description': 'Nothing here',
        'args': None
    },
    {
        'name': 'wall',
        'description': 'You will bounce off this',
        'args': {
            'hit': 'bounce'
        }
    }
]
graphics_types = [
    {
        'name': 'Space',
        'description': 'Nothing here',
        'args': None
    },
    {
        'name': 'straight',
        'description': 'You will bounce off this',
        'args': {
            'src': 'global',
            'filename': 'map_textures.bmp',
            'blh': '0/19',
            'blv': '0/10',
            'trh': '1/19',
            'trv': '1/10'
        }
    },
    {
        'name': 'corner',
        'description': 'You will bounce off this',
        'args': {
            'src': 'global',
            'filename': 'map_textures.bmp',
            'blh': '1/19',
            'blv': '0/10',
            'trh': '2/19',
            'trv': '1/10'
        }
    },
    {
        'name': 'intersection',
        'description': 'You will bounce off this',
        'args': {
            'src': 'global',
            'filename': 'map_textures.bmp',
            'blh': '2/19',
            'blv': '0/10',
            'trh': '3/19',
            'trv': '1/10'
        }
    },
]


class Tile(QtGui.QLabel):
    def __init__(self, x, y, physics=None, graphics=None, rotation=None, parent=None):
        super(QtGui.QLabel, self).__init__(parent)
        self.selected = False
        self.x = x
        self.y = y
        self.physics = physics
        self.graphics = graphics
        self.rotation = rotation
        self.update()

    def mousePressEvent(self, event):
        self.selected = not self.selected
        self.update()

    def update(self, data=None):
        if self.selected:
            selected = 'selected'
        else:
            selected = 'n_selected'
        if self.physics > 0 or self.graphics > 0:
            exists = 'exists'
        else:
            exists = 'n_exists'
        self.setPixmap(QtGui.QPixmap("icons/map_tiles/%s-%s.png" % (exists, selected)))

    def xml_open(self):
        return "<tile x='%s' y='%s'>" % (self.x, self.y)

    def xml_close(self):
        return "</tile>"

    def xml_physics(self):
        if self.physics == 0:
            return ''
        args = physics_types[self.physics]['args']
        return "<physics %s />" % ' '.join("%s='%s'" % (key, args[key]) for key in args.keys())

    def xml_graphics(self):
        if self.graphics == 0:
            return ''
        args = graphics_types[self.graphics]['args']
        args['rotation'] = self.rotation
        return "<graphics %s />" % ' '.join("%s='%s'" % (key, args[key]) for key in args.keys())


class MapWidget(QtGui.QWidget):
    def __init__(self, width, height, parent=None):
        super(QtGui.QWidget, self).__init__(parent)

        self.height = height
        self.width = width
        self.currentPhysics = 0
        self.currentGraphics = 0
        self.currentGraphicsRotation = 0

        self.grid = QtGui.QGridLayout(self)
        self.grid.setSpacing(0)

        self.map = [[Tile(x, y) for x in range(width)] for y in range(height)]
        print width
        print self.width
        print len(self.map[0])
        print height
        print self.height
        print len(self.map)
        for y in range(height):
            for x in range(width):
                self.grid.addWidget(self.map[y][x], y, x)

    def reset(self):
        for row in self.map:
            for tile in row:
                tile.physics = None
                tile.graphics = None
                tile.update()

    def clear(self):
        for row in self.map:
            for tile in row:
                tile.selected = False
                tile.update()

    def setCurrentPhysics(self, physics):
        self.currentPhysics = physics

    def setCurrentGraphics(self, graphics):
        self.currentGraphics = graphics

    def setCurrentGraphicsRotation(self, rotation):
        self.currentGraphicsRotation = rotation

    def apply(self):
        # get settings
        physics = self.currentPhysics
        graphics = self.currentGraphics
        rotation = self.currentGraphicsRotation
        for row in self.map:
            for tile in row:
                if tile.selected:
                    tile.physics = physics
                    tile.graphics = graphics
                    tile.rotation  = rotation
        self.clear()

    def indent(self, level, spacer='    '):
        return ''.join(spacer for x in range(level))

    def save(self):
        filename = QtGui.QFileDialog.getSaveFileName(self, 'Save File', '~/')
        f = open(filename, 'w')
        f.write("<?xml version='1.0' encoding='UTF-8'?>\n")
        f.write("<map height='%d' width='%d' tile_height='%d' tile_width='%d'>\n" % (
            self.height,
            self.width,
            10,
            10
        ))
        for row in self.map:
            for tile in row:
                if tile.physics > 0 or tile.graphics > 0:
                    f.write("%s%s\n" % (self.indent(1), tile.xml_open()))
                    if tile.physics > 0:
                        f.write("%s%s\n" % (self.indent(2), tile.xml_physics()))
                    if tile.graphics > 0:
                        f.write("%s%s\n" % (self.indent(2), tile.xml_graphics()))
                    f.write("%s%s\n" % (self.indent(1), tile.xml_close()))
        f.write("</map>")
        f.close()


class Window(QtGui.QMainWindow):
    def __init__(self, parent=None):
        super(QtGui.QWidget, self).__init__(parent)
        self.setWindowIcon(QtGui.QIcon('icon.png'))
        self.resize(250, 150)
        self.setWindowTitle('Map Generator')
        self.statusBar().showMessage('Welcome')

        ### Contents
        map = MapWidget(width, height)
        mapBoxWidget = QtGui.QWidget()

        self.physics_label = QtGui.QLabel("Physics:");
        self.physics_selector = QtGui.QComboBox()
        for type in physics_types:
            self.physics_selector.addItem(type['name'])
        self.physics_selector.show()
        self.physics_box =QtGui.QHBoxLayout()
        self.physics_box.addWidget(self.physics_label)
        self.physics_box.addWidget(self.physics_selector)
        self.connect(self.physics_selector, QtCore.SIGNAL("activated(int)"), map.setCurrentPhysics)

        self.graphics_label = QtGui.QLabel("Graphics")
        self.graphics_selector = QtGui.QComboBox()
        for type in graphics_types:
            self.graphics_selector.addItem(type['name'])
        self.graphics_selector.show()
        self.graphics_rotate_selector = QtGui.QComboBox()
        for rot in range(4):
            self.graphics_rotate_selector.addItem("%d degrees" % (rot*90))
        self.graphics_rotate_selector.show()
        self.graphics_box = QtGui.QHBoxLayout()
        self.graphics_box.addWidget(self.graphics_label)
        self.graphics_box.addWidget(self.graphics_selector)
        self.graphics_box.addWidget(self.graphics_rotate_selector)
        self.connect(self.graphics_selector, QtCore.SIGNAL("activated(int)"), map.setCurrentGraphics)
        self.connect(self.graphics_rotate_selector, QtCore.SIGNAL("activated(int)"), map.setCurrentGraphicsRotation)

        mapBox = QtGui.QVBoxLayout(mapBoxWidget)
        mapBox.addWidget(map)
        mapBox.addLayout(self.physics_box)
        mapBox.addLayout(self.graphics_box)
        mapBox.addStretch()

        hbox = QtGui.QHBoxLayout()
        hbox.addWidget(mapBoxWidget)
        hbox.addStretch()

        hboxWidget = QtGui.QWidget()
        hboxWidget.setLayout(hbox)

        self.setCentralWidget(hboxWidget)

        ### Toolbar
        self.quitButton = QtGui.QAction('Quit', self)
        self.quitButton.setShortcut('Ctrl+Q')
        self.connect(self.quitButton, QtCore.SIGNAL('triggered()'), QtCore.SLOT('close()'))

        self.applyButton = QtGui.QAction('Apply', self)
        self.applyButton.setShortcut('Ctrl+A')
        self.connect(self.applyButton, QtCore.SIGNAL('triggered()'), map.apply)

        self.saveButton = QtGui.QAction('Save', self)
        self.saveButton.setShortcut('Ctrl+S')
        self.connect(self.saveButton, QtCore.SIGNAL('triggered()'), map.save)

        self.clearButton = QtGui.QAction('Clear', self)
        self.clearButton.setShortcut('Ctrl+C')
        self.connect(self.clearButton, QtCore.SIGNAL('triggered()'), map.clear)

        self.resetButton = QtGui.QAction('Reset', self)
        self.resetButton.setShortcut('Ctrl+R')
        self.connect(self.resetButton, QtCore.SIGNAL('triggered()'), map.reset)

        self.toolbar = self.addToolBar('tools')
        self.toolbar.addAction(self.applyButton)
        self.toolbar.addAction(self.saveButton)
        self.toolbar.addAction(self.clearButton)
        self.toolbar.addAction(self.resetButton)
        self.toolbar.addAction(self.quitButton)

        self.show()


app = QtGui.QApplication(sys.argv)
window = Window()
sys.exit(app.exec_())
