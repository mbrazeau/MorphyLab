#include "MorphyLabNexusReader.h"

MorphyLabNexusReader::MorphyLabNexusReader()
{
    // Allocate the storage for blocks
    _reader         = new MultiFormatReader();
    _taxa           = new NxsTaxaBlock();
    _assumptions    = new NxsAssumptionsBlock(_taxa);
    _characters     = new NxsCharactersBlock(_taxa, _assumptions);
    _datab          = new NxsDataBlock(_taxa, _assumptions);

//    // Add the blocks to the reader stack
    _reader->Add(_taxa);
    _reader->Add(_assumptions);
    _reader->Add(_characters);
    _reader->Add(_datab);
}

void MorphyLabNexusReader::openNexusFile(char *arg)
{
    _reader->ReadFilepath(arg, MultiFormatReader::NEXUS_FORMAT);

    if (hasDataBlock()) {
        _datab->TransferTo(*_characters);
    }
}

void MorphyLabNexusReader::closeNexusFile()
{
    // TODO: Ask to save first, of course.

    _reader->DeleteBlocksFromFactories();
    return;
}

void MorphyLabNexusReader::saveNexusFile()
{
    return;
}

unsigned int MorphyLabNexusReader::getNchar()
{
    return _characters->GetNChar();
}

unsigned int MorphyLabNexusReader::getNtax()
{
    return _taxa->GetNTax();
}

QString MorphyLabNexusReader::getTaxLabel(unsigned int i)
{
    NxsString nxTaxlabel = _taxa->GetTaxonLabel(i);

    QString *ret = new QString(nxTaxlabel.c_str());

    return *ret;
}

bool MorphyLabNexusReader::hasDataBlock()
{
    BlockReaderList b1 = _reader->GetUsedBlocksInOrder();
    for (std::list<NxsBlock *>::iterator i = b1.begin(); i != b1.end(); ++i)
    {
        NxsBlock * b = (*i);
        if (b->GetID().compare("DATA") == 0)
        {
            return true;
        }
    }
    return false;
}

QString MorphyLabNexusReader::getCellData(unsigned int tax_i, unsigned int char_i)
{

    QString c;

    unsigned int i = 0;

    if (_characters->GetInternalRepresentation(tax_i, char_i, 0) == -2) {
        return "?";
    }

    for (i = 0; i < _characters->GetNumStates(tax_i, char_i); ++i) {
        if (i > 0) {
            if (_characters->IsPolymorphic(tax_i, char_i)) {
                c.append("&");
            } else {
                c.append("/");
            }
        }
        c.append(_characters->GetState(tax_i, char_i, i));
    }

    return c;
}
