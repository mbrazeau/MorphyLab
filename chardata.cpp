#include "chardata.h"

CharData::CharData() : AbstractPhyData()
{
    StateData state0;
    StateData state1;

//    state0.setLabel("State_0");
//    state1.setLabel("State_0");
//    m_States.insert({'0', state0});
//    m_States.insert({'1', state1});
}

std::string CharData::displayText() const
{
    return m_Description;
}
