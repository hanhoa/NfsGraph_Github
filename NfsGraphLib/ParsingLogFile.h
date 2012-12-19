#pragma once

#include "Parsing.h"
#include "NfsPoints.h"

namespace NfsGraph
{

class CParsingLogFile : public CParsing
{
public:
    CParsingLogFile(void);
    virtual ~CParsingLogFile(void);
        
    void SetPointVector(std::vector<CNfsPoints*> *pvecNfsPoints) { m_pvecNfsPoints = pvecNfsPoints; }

    bool Run(std::string strFileName);
    
private:
    std::vector<CNfsPoints*> *m_pvecNfsPoints;
};

}