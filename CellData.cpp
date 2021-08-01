#include <set>

#include "CellData.h"
#include "statedata.h"

CellData::CellData() : AbstractPhyData()
{
    m_wildCardToken = '?';
    m_displayText.clear();
    m_displayText.push_back(m_wildCardToken);
}

std::string CellData::displayText() const
{
    return m_displayText;
}

CellData::PolyType CellData::polyType()
{
    if (m_pState.size() == 1) {
        return Unambiguous;
    }

    return m_polyType;
}

void CellData::setPolyType(PolyType polytype)
{
    m_polyType = polytype; // TODO: Make this safer
}

int CellData::getNStates()
{
    return m_pState.size();
}

char CellData::getStateToken(unsigned int index)
{
    assert (index < m_pState.size());

    return m_pState[index]->first;
}

StateData &CellData::getStateLabel(unsigned int index)
{
    assert (index < m_pState.size());

    return m_pState[index]->second;
}

//void CellData::scoreData(std::vector<std::pair<char, StateData>*> &value)
//{
//    unsigned int i = 0;
//    char sep = '&';

//    m_pState = value;

//    m_displayText.clear();

//    if (m_polyType == Ambiguous) {
//        sep = '/';
//    }

//    m_displayText += m_pState[0]->first;

//    for (i = 1; i < m_pState.size(); ++i) {
//        m_displayText += sep;
//        m_displayText += m_pState[i]->first;
//    }

//    m_wildCardToken = '\0'; // Clear the wildcard.
//}

//void CellData::scoreData(char c)
//{
//    assert(c == '?' || c == '-' || c == '+');

//    m_pState.clear();

//    m_wildCardToken = c;
//    m_displayText.clear();
//    m_displayText.push_back(c);
//}



bool CellData::scoreData(std::string s)
{
    // Take out any whitespace:
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());

    int expectPolymorph=0;
    char sep = '&';

    if (s.find('/') != std::string::npos || s.find('\\') != std::string::npos) {
        expectPolymorph = 1;
        std::replace(s.begin(), s.end(), '\\', '/');
        std::replace(s.begin(), s.end(), '/', ' ');
        sep = '/';
    }
    else  if (s.find('&')!= s.npos) {
        expectPolymorph = 2;
        std::replace(s.begin(), s.end(), '&', ' ');
    }

    if (s.length() == 1) {
        if (!checkValid(s[0])) {
            return false;
        }
        m_displayText = s;
    } else {

        std::vector<char> rstates;
        std::set<char> states;

        // Remove any separators
        s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());

        for (unsigned long i = 0; i < s.length(); ++i) {
            if (!checkValid(s[i])) {
                return false;
            }
            rstates.push_back(s[i]);
        }

        std::sort(rstates.begin(), rstates.end());
        for (unsigned long i = 0; i < rstates.size(); ++i) {
            states.insert(rstates[i]);
        }

        // Set the display text
        m_displayText.clear();

        std::set<char>::iterator it=states.begin();
        m_displayText.push_back(*it);
        ++it;
        for (; it!=states.end(); ++it) {
             m_displayText.push_back(sep);
            m_displayText.push_back(*it);
        }

        // TODO: Create version for label input mode
    }

    if (expectPolymorph == 1 || s == "?") {
        m_polyType = Ambiguous;
    } else if (expectPolymorph == 2) {
        m_polyType = Polymorphic;
    } else {
        m_polyType = Unambiguous;
    }

    return true;
}

std::string CellData::nexusStyleData()
{
    if (m_displayText.length() > 1) {
        std::string ret = m_displayText;
        if (m_polyType == Ambiguous) {
            std::replace(ret.begin(), ret.end(), '/', ' ');
            ret.insert(0, "{");
            ret.append("}");
        } else {
            std::replace(ret.begin(), ret.end(), '&', ' ');
            ret.insert(0, "(");
            ret.append(")");
        }

        return ret;
    }

    return m_displayText;
}

bool CellData::checkValid(char c)
{
    std::size_t found = AbstractPhyData::PermittedSymbols.find(c);
    if (found != std::string::npos) {
        return true;
    }

    return false;
}


