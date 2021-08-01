#ifndef STATEDATA_H
#define STATEDATA_H

#include <string>

#include "abstractphydata.h"

class StateData : public AbstractPhyData
{
public:
    StateData();
    ~StateData(){};

    void         setSymbol(char c);
    char         symbol();
    void         setLabel(std::string label);
    void         label();
    std::string  displayText() const override;

private:
    char        m_Symbol;
    std::string m_Label;
    std::string m_ImagePath;
};

#endif // STATEDATA_H
