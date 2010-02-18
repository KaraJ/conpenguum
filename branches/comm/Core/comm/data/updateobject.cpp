#include "updateobject.h"

using std::vector;

bool UpdateObject::serialize(char* buffer, size_t buffSize)
{
    std::vector<BYTE> data(10);
    data[0] = (BYTE)rotation_;
    data[1] = (BYTE)pos_.x();
    data[2] = (BYTE)pos_.y();
    return true;
}
