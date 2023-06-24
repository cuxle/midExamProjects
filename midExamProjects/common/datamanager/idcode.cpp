#include "idcode.h"

IDCode::IDCode()
{

}

IDCode::IDCode(const IDCode &other) {
    this->code = other.code;
    this->id = other.id;
}

bool IDCode::operator== (const IDCode &idcode) const{
    return id.compare(idcode.id) == 0 && code.compare(idcode.code) == 0;
}

IDCode& IDCode::operator= (const IDCode& rhs) {
    id = rhs.id;
    code = rhs.code;
    return *this;
}
