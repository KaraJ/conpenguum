#include "qtxmlparse.h"
#include <qiodevice.h>
#include <qdatastream.h>
#define EXPLOSION 0
#define EXHAUST 1
/*------------------------------------------------------------------------
-- FUNCTION NAME: QtXmlParse()
--
-- FUNCTION PURPOSE: Constructor.
--
-- DESIGNER: Jordan Lewis
--
-- PROGRAMMER: Jordan Lewis
--
-- DATE: March. 2nd, 2010
-------------------------------------------------------------------------*/
QtXmlParse::QtXmlParse()
{
}
/*------------------------------------------------------------------------
-- FUNCTION NAME: ReadAnimationVector()
--
-- FUNCTION PURPOSE: reads animation vector from xml file..
--
-- RETURN VALUE: vector of animation images.
--
-- DESIGNER: Jordan Lewis
--
-- PROGRAMMER: Jordan Lewis
--
-- DATE: March. 2nd, 2010
-------------------------------------------------------------------------*/
std::vector<Image> QtXmlParse::ReadAnimationVector(AnimationType animation, std::string file)
{
    QDomDocument doc("animationDoc");
    QFile q_File(file.c_str());
    QDomElement docElement;
    std::vector<Image> vec;
    QXmlInputSource * src;
    int offsetX, offsetY;
    std::string textur_Link, desc;
    Image img;


    // open file for transfer into QDomDocument
    if(!q_File.open(QIODevice::ReadOnly))
    {
        return vec; // error display message
    }

    if(!doc.setContent(&q_File))
    {
        q_File.close();
        return vec;
    }

    q_File.close();

    // now time to read in animation images
    docElement = doc.documentElement();
    QDomNode node = docElement.firstChild();
    QDomNodeList nodeList;
    QString str;
    QDomElement element = node.toElement();
    QDomNode next;
    // getting path to texture.
    while(strcmp(node.nodeName().toStdString().c_str(), "link") != 0){node = node.nextSibling();}
    element = node.toElement();
    img.setLink(element.text().toStdString());

    // if we are looking for ships iterate to the begining where direction can be captured.
    if(animation == Ship)
    {
        // looking for frame portion
        while(strcmp(node.nodeName().toStdString().c_str(), "frame") != 0){node = node.nextSibling();}
        //node = node.firstChild();
        next = node.nextSibling();
        element = node.toElement();
        node = element.firstChild();

    }
    while(!node.isNull())
    {
        switch(animation)
        {
        case Explosion:
            {
                // looking for frame portion
                while(strcmp(node.nodeName().toStdString().c_str(), "frame") != 0){node = node.nextSibling();}
                //node = node.firstChild();
                next = node.nextSibling();
                element = node.toElement();
                node = element.firstChild();

                // skip to relevant info
                while(strcmp(element.nodeName().toStdString().c_str(), "direction") != 0){
                    element = node.nextSiblingElement();
                    //node = element;
                }

                node = element.firstChild();

                // get image values.
                while(strcmp(element.nodeName().toStdString().c_str(), "left") != 0){
                    element = node.nextSiblingElement();
                }
                img.setLeftOffSet(atof(element.text().toStdString().c_str()));

                // getting bottom offset.
                while(strcmp(node.nodeName().toStdString().c_str(), "bottom") != 0){node = node.nextSibling();}
                element = node.toElement();
                img.setBottomOffSet(atof(element.text().toStdString().c_str()));

                // getting right offset.
                while(strcmp(node.nodeName().toStdString().c_str(), "right") != 0){node = node.nextSibling();}
                element = node.toElement();
                img.setRightOffSet(atof(element.text().toStdString().c_str()));

                // getting top offset.
                while(strcmp(node.nodeName().toStdString().c_str(), "top") != 0){node = node.nextSibling();}
                element = node.toElement();
                img.setTopOffSet(atof(element.text().toStdString().c_str()));

                vec.push_back(img);
                break;
            }
        case Exhaust:
            {
                break;
            }
        case Ship:
            {

                // skip to relevant info
                while(strcmp(node.nodeName().toStdString().c_str(), "direction") != 0){node = node.nextSibling();}
                next = node.nextSibling();
                element = node.toElement();
                node = element.firstChild();
                //next = node.nextSibling().nextSibling(); // set for next iteration.
                img.setDirection(atoi(element.attributes().namedItem("id").toElement().text().toStdString().c_str()));
                //node = element.firstChild();
                element = node.toElement();

                // get image values.
                while(strcmp(element.nodeName().toStdString().c_str(), "left") != 0){
                    element = node.nextSiblingElement();
                }
                img.setLeftOffSet(atof(element.text().toStdString().c_str()));

                // getting bottom offset.
                while(strcmp(node.nodeName().toStdString().c_str(), "bottom") != 0){node = node.nextSibling();}
                element = node.toElement();
                img.setBottomOffSet(atof(element.text().toStdString().c_str()));

                // getting right offset.
                while(strcmp(node.nodeName().toStdString().c_str(), "right") != 0){node = node.nextSibling();}
                element = node.toElement();
                img.setRightOffSet(atof(element.text().toStdString().c_str()));

                // getting top offset.
                while(strcmp(node.nodeName().toStdString().c_str(), "top") != 0){node = node.nextSibling();}
                element = node.toElement();
                img.setTopOffSet(atof(element.text().toStdString().c_str()));

                vec.push_back(img);
                break;
            }
        }

        node = next; // go to next frame package in XML.

    }

    return vec;

}
