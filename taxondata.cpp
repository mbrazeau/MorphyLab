#include "taxondata.h"

TaxonData::TaxonData() : AbstractPhyData()
{
    m_suppressHigherName = true;
    higherName += "";
    genus += "";
    species += "";
    subspecies += "";
}

std::string TaxonData::displayText() const
{
    std::string name;

    name += higherName;
    name += genus;
    name += species;
    name += subspecies;

    return name;
}

void TaxonData::setGenus(std::string name)
{
    genus = name;
}

