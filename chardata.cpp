#include "chardata.h"

CharData::CharData() : AbstractPhyData()
{

}

std::string CharData::displayText() const
{
    return m_Description;
}

