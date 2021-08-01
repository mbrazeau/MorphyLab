#ifndef ABSTRACTPHYDATA_H
#define ABSTRACTPHYDATA_H

#include <string>

class AbstractPhyData
{
public:

    std::string PermittedSymbols = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+-?";

    AbstractPhyData();
    virtual ~AbstractPhyData(){}

    virtual std::string displayText() const = 0;
};

#endif // ABSTRACTPHYDATA_H
