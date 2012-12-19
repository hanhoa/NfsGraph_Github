#pragma once

#include <string>
#include "gdefine.h"

namespace NfsGraph
{

enum EParsingError
{
    PE_NO_ERROR,
    PE_NOT_SETTING_CONTAINER,
    PE_INCORRECT_FILE_PATH,
    PE_LOG_FORMAT_ERROR,
    PE_STOP_BY_USER
};

class CParsing
{
public:
    CParsing(void);
    virtual ~CParsing(void);

    virtual bool Run(std::string strFileName) = 0;
    
    static void Stop(void) { m_bLoading = false; }

    std::string GetErrorMsg(void);
    U32    GetErrorLine(void) { return m_nErrorLine; }

protected:  // Inner Functions
    bool CheckBasicalErrors(void *pContainer, std::string strFileName);
    bool StringToNumber(const char *szString, U32 &nNum);
    bool StringToDouble(const char *szString, double &fNum);
    bool CutString(char *szString, char *pResult, char delim);
    std::string TrimString(std::string strContent);

protected:
    EParsingError m_eParsingError;
    S32 m_nErrorLine;
    
    static bool m_bLoading;
};

}