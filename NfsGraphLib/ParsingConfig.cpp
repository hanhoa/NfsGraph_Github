#include "StdAfx.h"
#include "ParsingConfig.h"

#include <fstream>

#define NAME_OF_VALUE_COLUMN        "ValueCol"
#define NAME_OF_LEGEND_COLUMN       "LegendCol"
#define NAME_OF_GRAPH_TYPE          "GraphType"
#define NAME_OF_X_MAG               "Xmag"
#define NAME_OF_Y_MAG               "Ymag"
#define NAME_OF_PARAM               "PARAM"

namespace NfsGraph
{

CParsingConfig::CParsingConfig(void)
:m_pConfigBox(NULL)
{
}

CParsingConfig::~CParsingConfig(void)
{
}

bool CParsingConfig::Run(std::string strFileName)
{
    if(m_pConfigBox == NULL)
    {
        m_eParsingError = PE_NOT_SETTING_CONTAINER;
        return false;
    }

    std::ifstream inFile(strFileName);
    if(!inFile)
    {
        MakeDefaultConfigFile(strFileName);
        inFile.open(strFileName);
        
        if(!inFile.is_open())
        {
            m_eParsingError = PE_INCORRECT_FILE_PATH;
            return false;
        }
    }

    char szLine[500], szName[100], szValue[100], szTemp[100];
    char *pValue;
    int i;

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
        inFile.getline(szLine, 500);

        for(i = 0; i < 500; i++) 
        {
            if(szLine[i] != ' ' && szLine[i] != '\t') break;
        }

        if(szLine[i] == '\n' || szLine[i] == '\0') continue;

        pValue = strtok(szLine, "=");
        if(!pValue) 
        {
            goto ParsingConfigFinish;
        }

        strncpy(szName, pValue, 100);

        pValue = strtok(NULL, "=");
        if(!pValue) 
        {
            goto ParsingConfigFinish;
        }

        while(*pValue != '\n' && *pValue != '\0')
        {
            if(*pValue == '"')
            {
                pValue++;
                if(CutString(pValue, szValue, '"') == false)
                {
                    goto ParsingConfigFinish;
                }
                break;
            }
            pValue++;
        }

        if(*pValue == '\n' || *pValue == '\0')
        {
            goto ParsingConfigFinish;
        }

        if(strstr(szName, NAME_OF_VALUE_COLUMN))
        {
            if(szValue[0] == '\0') m_pConfigBox->nValueCol = 1;
            else if(StringToNumber(szValue, m_pConfigBox->nValueCol) == false)
            {
                goto ParsingConfigFinish;
            }
        }
        else if(strstr(szName, NAME_OF_LEGEND_COLUMN))
        {
            if(szValue[0] == '\0') m_pConfigBox->nLegendCol = 0;
            else if(StringToNumber(szValue, m_pConfigBox->nLegendCol) == false)
            {
                goto ParsingConfigFinish;
            }
        }
        else if(strstr(szName, NAME_OF_X_MAG))
        {
            U32 nXmagLevel;
            if(szValue[0] == '\0') m_pConfigBox->eXmag = ML_1x;
            else if(StringToNumber(szValue, nXmagLevel) == false)
            {
                goto ParsingConfigFinish;
            }
            m_pConfigBox->eXmag = (MAG_LEVEL)nXmagLevel;
        }
        else if(strstr(szName, NAME_OF_Y_MAG))
        {
            U32 nYmagLevel;
            if(szValue[0] == '\0') m_pConfigBox->eYmag = ML_1x;
            else if(StringToNumber(szValue, nYmagLevel) == false)
            {
                goto ParsingConfigFinish;
            }
            m_pConfigBox->eYmag = (MAG_LEVEL)nYmagLevel;
        }
        else if(strstr(szName, NAME_OF_GRAPH_TYPE))
        {
            U32 nGraphType;
            if(szValue[0] == '\0') m_pConfigBox->eGraphType = GT_LINE;
            else if(StringToNumber(szValue, nGraphType) == false)
            {
                goto ParsingConfigFinish;
            }
            m_pConfigBox->eGraphType = (GRAPH_TYPE)nGraphType;
        }
        else if(pValue = strstr(szName, NAME_OF_PARAM))
        {
            // This must be like 'PARAM3_5 = "TestName"'.
            // 3 is parameter number and 5 is the real value of the parameter. 
            // "TestName" is alias of value 5.
            U32 nParamNum, nParamValue;
            pValue += strlen(NAME_OF_PARAM);

            // Get parameter number. 
            if(CutString(pValue, szTemp, '_') == false)
            {
                goto ParsingConfigFinish;
            }

            if(StringToNumber(szTemp, nParamNum) == false)
            {
                goto ParsingConfigFinish;
            }

            if(nParamNum >= MAX_NUM_OF_PARAM)
            {
                goto ParsingConfigFinish;
            }

            while(*pValue != '_') pValue++;
            pValue++;

            if(StringToNumber(pValue, nParamValue) == false)
            {
                goto ParsingConfigFinish;
            }

            m_pConfigBox->mapParamName[nParamNum][nParamValue] = szValue;                     
        }
    }

    m_bLoading = false;
    inFile.close();
    return true;

ParsingConfigFinish:
    m_bLoading = false;
    inFile.close();
    m_eParsingError = PE_LOG_FORMAT_ERROR;
    return false;
}

void CParsingConfig::InitConfigBox(ConfigBox *pConfigBox)
{
    pConfigBox->nValueCol = 0;
    pConfigBox->nLegendCol = 0;
    pConfigBox->eGraphType = GT_LINE;
    pConfigBox->eXmag = ML_2x;
    pConfigBox->eYmag = ML_Log2x;

    for(int i = 0; i < MAX_NUM_OF_PARAM; i++)
        pConfigBox->mapParamName[i].clear();
}

void CParsingConfig::MakeDefaultConfigFile(std::string strFileName)
{
    ConfigBox configBox;
    InitConfigBox(&configBox);
    SaveConfigFile(strFileName, &configBox);
}

void CParsingConfig::SaveConfigBox(std::string strFileName)
{
    SaveConfigFile(strFileName, m_pConfigBox);
}

void CParsingConfig::SaveConfigFile(std::string strFileName, ConfigBox *pConfigBox)
{
    std::ofstream ofs(strFileName);

    ofs << NAME_OF_VALUE_COLUMN << " = \"" << pConfigBox->nValueCol << "\"\n";
    ofs << NAME_OF_LEGEND_COLUMN << " = \"" << pConfigBox->nLegendCol << "\"\n";
    ofs << NAME_OF_GRAPH_TYPE << " = \"" << pConfigBox->eGraphType << "\"\n";
    ofs << NAME_OF_X_MAG << " = \"" << pConfigBox->eXmag << "\"\n";
    ofs << NAME_OF_Y_MAG << " = \"" << pConfigBox->eYmag << "\"\n";

    std::map<U32, std::string>::iterator it;

    for(int i = 0; i < MAX_NUM_OF_PARAM; i++)
    {
        for(it = pConfigBox->mapParamName[i].begin(); it != pConfigBox->mapParamName[i].end(); it++)
        {
            ofs << NAME_OF_PARAM << i << "_" << it->first << " = \"" << it->second << "\"\n";
        }
    }

    ofs.close();
}

}