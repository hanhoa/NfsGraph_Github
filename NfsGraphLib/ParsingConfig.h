#pragma once

#include "Parsing.h"
#include "NfsPoints.h"

#include <map>

namespace NfsGraph
{

struct ConfigBox
{
    U32 nValueCol;
    U32 nLegendCol;
    GRAPH_TYPE eGraphType;
    MAG_LEVEL eXmag;
    MAG_LEVEL eYmag;
    std::map<U32, std::string> mapParamName[MAX_NUM_OF_PARAM];
};

class CParsingConfig : public CParsing
{
public:
    CParsingConfig(void);
    virtual ~CParsingConfig(void);

    void SetConfigBox(ConfigBox *pConfigBox) { m_pConfigBox = pConfigBox; }
    void InitConfigBox(ConfigBox *pConfigBox);

    bool Run(std::string strFileName);

    void MakeDefaultConfigFile(std::string strFileName);
    void SaveConfigBox(std::string strFileName);
    
private:
    void SaveConfigFile(std::string strFileName, ConfigBox *pConfigBox);

private:
    ConfigBox *m_pConfigBox;
};

}