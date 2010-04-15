#ifndef QTXMLPARSE_H
#define QTXMLPARSE_H
#include "QtXmlParse_global.h"
#include "Animation.h"
#include "../../Core/resourceMgr/resourceEnums.h"

/*------------------------------------------------------------------------
-- CLASS NAME: QtXmlParse
--
-- CLASS PURPOSE: Parse animation xml files for dat load.
--
-- DESIGNER: Jordan Lewis
--
-- PROGRAMMER: Jordan Lewis
--
-- DATE: March. 2nd, 2010
-------------------------------------------------------------------------*/
class QTXMLPARSESHARED_EXPORT QtXmlParse {
public:
    QtXmlParse();
    std::vector<Image> ReadAnimationVector(std::string file);

};

#endif // QTXMLPARSE_H
