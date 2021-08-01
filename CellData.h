#ifndef CELLDATA_H
#define CELLDATA_H

#include <vector>
#include <utility>
#include <string>

#include "abstractphydata.h"

class StateData;

class CellData : public AbstractPhyData
{
public:

    enum PolyType {Unambiguous, // For unambiguous single states
                   Ambiguous,   // For polymorphisms treated as ambiguity
                   Polymorphic  // For 'true' polymorphism.
                  };

    CellData();
    ~CellData(){}

    bool         labelInputMode();
    void         useLabelInputMode(bool uselab);

    std::string displayText() const override;
    PolyType polyType();
    void setPolyType(PolyType polytype);
    int  getNStates();
    char getStateToken(unsigned int index);
    StateData &getStateLabel(unsigned int index);
//    void scoreData(std::vector<std::pair<char, StateData>*> &value);
//    void scoreData(char c);
    bool scoreData(std::string s);
    std::string nexusStyleData();
    std::string tntStyleData();

private:

    char m_wildCardToken;
    bool m_labelInputMode;
    std::string m_displayText;
    PolyType m_polyType;
    std::vector<std::pair<char, StateData>*> m_pState;

    bool checkValid(char c);
};

#endif // CELLDATA_H
