#ifndef MORPHYLABNEXUSREADER_H
#define MORPHYLABNEXUSREADER_H

#include <QString>
#include "ncl.h"

class MorphyLabNexusReader
{
public:
    MorphyLabNexusReader();

    void openNexusFile(char* arg);
    void closeNexusFile();
    void saveNexusFile();

    unsigned int getNtax();
    unsigned int getNchar();

    QString getCellData(unsigned int tax_i, unsigned int char_i);
    QString getTaxLabel(unsigned int i);

private:

    MultiFormatReader   *_reader;
    NxsTaxaBlock        *_taxa;
    NxsAssumptionsBlock *_assumptions;
    NxsCharactersBlock  *_characters;
    NxsDataBlock        *_datab;
};

#endif // MORPHYLABNEXUSREADER_H
