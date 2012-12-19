#include "StdAfx.h"
#include "Parsing.h"

#include <fstream>
#include <sstream>

namespace NfsGraph
{

bool CParsing::m_bLoading = false;

CParsing::CParsing(void)
{
    m_eParsingError = PE_NO_ERROR;
    m_nErrorLine = -1;
}

CParsing::~CParsing(void)
{
}

bool CParsing::CheckBasicalErrors(void *pContainer, std::string strFileName)
{
    if(pContainer == NULL)
    {
        m_eParsingError = PE_NOT_SETTING_CONTAINER;
        return false;
    }

    std::ifstream inFile(strFileName);
    if(!inFile)
    {
        m_eParsingError = PE_INCORRECT_FILE_PATH;
        return false;
    }

    inFile.close();
    return true;
}

bool CParsing::StringToNumber(const char *szString, U32 &nNum)
{
    nNum = 0;
    while(*szString == ' ' || *szString == '\t') szString++;

    while(*szString != '\0')
    {
        if(*szString == ' ' || *szString == '\t') break;
        if(*szString > '9' || *szString < '0') return false;

        nNum *= 10;
        nNum += *szString - '0';

        szString++;
    }
    return true;
}

bool CParsing::StringToDouble(const char *szString, double &fNum)
{
    fNum = 0.;
    while(*szString == ' ' || *szString == '\t') szString++;

    double fTemp = 10.;
    bool bLower = false;
    while(*szString != '\0')
    {
        if(*szString == ' ' || *szString == '\t') break;
        
        if(*szString == '.')
        {
            bLower = true;
        }
        else if(*szString <= '9' && *szString >= '0')
        {
            if(bLower == false)
            {
                fNum *= 10.;
                fNum += *szString - '0';
            }
            else
            {
                fNum += (double)(*szString - '0') / fTemp;
                fTemp *= 10.;
            }
        }
        else
            return false;

        szString++;
    }

    return true;
}

bool CParsing::CutString(char *szString, char *pResult, char delim)
{
    char *pValue;
    
    pValue = szString;
    while(*pValue != '\n' && *pValue != '\0' && *pValue != delim) pValue++;
    if(*pValue == '\n' || *pValue == '\0')
    {
        return false;
    }
    *pValue = '\0';
    strcpy(pResult, szString);
    *pValue = delim;
    return true;
}

std::string CParsing::TrimString(std::string strContent)
{
    std::string::size_type pt;
    pt = strContent.find_first_not_of(" \t");
    if(pt == std::string::npos) return "";
    strContent.erase(0, pt);

    pt = strContent.find_last_not_of(" \t");
    if(pt == std::string::npos) return "";
    strContent.erase(pt + 1);
    
    return strContent;
}

std::string CParsing::GetErrorMsg(void)
{
    std::ostringstream strStream;
    switch(m_eParsingError)
    {
    case PE_NO_ERROR:
        strStream << "Line(" << m_nErrorLine << ") : No error";
        return strStream.str();

    case PE_NOT_SETTING_CONTAINER:
        strStream << "Line(" << m_nErrorLine << ") : Not setting container.";
        return strStream.str();

    case PE_INCORRECT_FILE_PATH:
        strStream << "Line(" << m_nErrorLine << ") : The file doesn't exist.";
        return strStream.str();

    case PE_LOG_FORMAT_ERROR:
        strStream << "Line(" << m_nErrorLine << ") : Log File Format Error";
        return strStream.str();

    case PE_STOP_BY_USER:
        strStream << "Process has been stopped.";
        return strStream.str();
    }

    return "No error";
}

}