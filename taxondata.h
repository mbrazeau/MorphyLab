#ifndef TAXONDATA_H
#define TAXONDATA_H

#include <string>

#include "abstractphydata.h"

class TaxonData : public AbstractPhyData

{
public:
    TaxonData();
    ~TaxonData(){};

    std::string displayText() const override;

    void suppressHigherName(bool suppress);
    void setHigherName(std::string name);
    void setGenus(std::string name);
    void setSpecies(std::string name);
    void setSubspecies(std::string name);

private:


    std::string higherName;
    std::string genus;
    std::string species;
    std::string subspecies;

    bool m_suppressHigherName;

};

#endif // TAXONDATA_H
