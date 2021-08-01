#include "statedata.h"

StateData::StateData() : AbstractPhyData()
{

}

void StateData::setLabel(std::string labelText)
{
    m_Label = labelText;
}

std::string StateData::displayText() const
{
    return m_Label;
}
