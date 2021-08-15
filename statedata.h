#ifndef STATEDATA_H
#define STATEDATA_H

#include <string>
#include <vector>

#include "abstractphydata.h"
class CharData;

class StateData : public AbstractPhyData
{
public:
    StateData();
    ~StateData(){};

    std::string  displayText() const override;
    void         setSymbol(char c);
    char         symbol();
    void         setLabel(std::string label);
    void         label();

private:
    char                    m_Symbol;
    std::string             m_Label;
    std::string             m_ImagePath;
    std::vector<CharData *>   m_Subchars;
};

#endif // STATEDATA_H
