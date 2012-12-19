#include "StdAfx.h"
#include "ParsingLogFile.h"

#include <fstream>

namespace NfsGraph
{

CParsingLogFile::CParsingLogFile(void)
{
    m_pvecNfsPoints = NULL;
}

CParsingLogFile::~CParsingLogFile(void)
{
}

bool CParsingLogFile::Run(std::string strFileName)
{
    if(CheckBasicalErrors(m_pvecNfsPoints, strFileName) == false) return false;

    std::ifstream inFile(strFileName);

    char szLine[500];
    char *pValue;
    U16 nParamIdx;
    U32 nValue, nIdx;
    bool bFirstLine = true;

    m_bLoading = true;
    
    m_nErrorLine = 0;
    while(!inFile.eof())
    {
        if(m_bLoading == false)
        {
            inFile.close();
            m_eParsingError = PE_STOP_BY_USER;
            return false;
        }

        m_nErrorLine++;
        nParamIdx = 0;
        inFile.getline(szLine, 500);

        if(szLine[0] == '#') 
        {
            U32 nNumOfParams = m_pvecNfsPoints->back()->GetNumOfParams();
            
            m_pvecNfsPoints->push_back(new CNfsPoints());
            for(U32 i = 0; i < nNumOfParams; i++)
            {
                m_pvecNfsPoints->back()->WriteParamTitle(i, m_pvecNfsPoints->at(m_pvecNfsPoints->size() - 2)->GetParamTitle(i));
            }

            continue;
        }

        if(szLine[0] == '/' && szLine[1] == '/') 
        {
            continue;
        }

        for(nIdx = 0; szLine[nIdx] == ' ' || szLine[nIdx] == '\t'; nIdx++) ;
        if(szLine[nIdx] == '\0' || szLine[nIdx] == '\n') continue;

        pValue = strtok(szLine, ",");
        if(!pValue) 
        {
            goto ParsingLogFileFinish;
        }

        if(bFirstLine)
        {
            std::string strName;
            do 
            {
                if(nParamIdx == MAX_NUM_OF_PARAM) 
                {
                    goto ParsingLogFileFinish;
                }

                strName = pValue;
                strName = TrimString(strName);
                m_pvecNfsPoints->back()->WriteParamTitle(nParamIdx++, strName);
            } while (pValue = strtok(NULL, ","));

            bFirstLine = false;
        }
        else
        {
            m_pvecNfsPoints->back()->AddPoint();
            do 
            {
                if(StringToNumber(pValue, nValue) == false)
                {
                    goto ParsingLogFileFinish;
                }

                if(nParamIdx == MAX_NUM_OF_PARAM) 
                {
                    goto ParsingLogFileFinish;
                }

                m_pvecNfsPoints->back()->WriteParamAtLastPoint(nParamIdx++, nValue);
            } while (pValue = strtok(NULL, ","));
        }
    }

    if(m_pvecNfsPoints->back()->GetCount() == 0) 
    {
        delete m_pvecNfsPoints->back();
        m_pvecNfsPoints->pop_back();
    }

    m_bLoading = false;
    inFile.close();
    return true;

ParsingLogFileFinish:
    m_bLoading = false;
    inFile.close();
    m_eParsingError = PE_LOG_FORMAT_ERROR;
    return false;
}

}