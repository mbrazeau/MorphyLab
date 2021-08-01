#ifndef CHARDATA_H
#define CHARDATA_H

#include <string>
#include <map>

#include "abstractphydata.h"
#include "statedata.h"

class CharData : public AbstractPhyData
{
public:
    CharData();
    ~CharData() {}


    std::string  displayText() const override;
    int          uniqueID;
    void         describeChar(std::string charDescript);
    void         addState(char token, std::string stateName);
    char         getStateToken(std::string stateName);
    std::string &getStateName(char token);
    bool         isIncluded();
    void         include(bool inclusion);

private:

    bool m_labelInputMode;

    std::string m_Description;
    std::map<char, StateData> m_States;
    std::string m_Notes;

};

#endif // CHARDATA_H
