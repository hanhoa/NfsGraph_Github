#include "StdAfx.h"
#include "NfsGraphManager.h"
#include "ParsingLogFile.h"

#include <fstream>
#include <sstream>
#include <math.h>

namespace NfsGraph
{

CNfsGraphManager::CNfsGraphManager(void)
{   
    InitResource();
}

CNfsGraphManager::~CNfsGraphManager(void)
{
    ClearResource();
}

void CNfsGraphManager::InitResource(void)
{
    m_vecNfsPoints.push_back(new CNfsPoints());
    m_nCurrentGraphNum = 0;

    CParsingConfig parConfig;
    parConfig.InitConfigBox(&m_GraphConfig);
}

void CNfsGraphManager::ClearResource(void)
{
    std::vector<CNfsPoints*>::iterator it = m_vecNfsPoints.begin();

    for(; it != m_vecNfsPoints.end(); it++)
    {
        delete *it;
    }

    m_vecNfsPoints.clear();

    m_strErrorMsg = "";
}

bool CNfsGraphManager::ReadLogFile(std::string strLogFileName, std::string strConfigFileName)
{
    CParsingLogFile cParser;
    CParsingConfig cConfigPaser;

    std::ostringstream strStream;

    ClearResource();
    InitResource();

    // First, Parsing Log file.
    cParser.SetPointVector(&m_vecNfsPoints);
    if(!cParser.Run(strLogFileName))
    {   
        std::string::size_type idx = strLogFileName.rfind('\\');
        if(idx != std::string::npos) strLogFileName.erase(0, idx + 1);
        strStream << "File [ " << strLogFileName << " ]\n" << cParser.GetErrorMsg();
        m_strErrorMsg = strStream.str();
        return false;
    }

    // Second, Parsing config file.
    cConfigPaser.SetConfigBox(&m_GraphConfig);
    if(!cConfigPaser.Run(strConfigFileName))
    {
        std::string::size_type idx = strConfigFileName.rfind('\\');
        if(idx != std::string::npos) strConfigFileName.erase(0, idx + 1);
        strStream << "File [ " << strConfigFileName << " ]\n" << cConfigPaser.GetErrorMsg();
        m_strErrorMsg = strStream.str();
        return false;
    }
    
    return true;
}

void CNfsGraphManager::StopReadingLogFile(void)
{
    CParsing::Stop();
}

void CNfsGraphManager::SaveConfigFile(std::string strFileName)
{
    CParsingConfig cConfigPaser;
    cConfigPaser.SetConfigBox(&m_GraphConfig);
    cConfigPaser.SaveConfigBox(strFileName);
}

bool CNfsGraphManager::GetPosCoordinate(U32 nGraphIdx, U32 nPtIdx, U32 &nXpos, U32 &nYpos)
{
    NG_POINT_INFO sPointInfo;
    if(GetPosInfo(nGraphIdx, nPtIdx, sPointInfo) == false) return false;

    if(m_GraphConfig.nValueCol >= m_vecNfsPoints[nGraphIdx]->GetNumOfParams()) m_GraphConfig.nValueCol = m_vecNfsPoints[nGraphIdx]->GetNumOfParams() - 1;

    bool bLog;
    double fXmag, fYmag;
    fXmag = getRealMag(m_GraphConfig.eXmag, bLog);
    if(bLog)
    {
        if(nPtIdx == 0) nXpos = 0;
        else nXpos = (U32)logB((double)nPtIdx, fXmag);
    }
    else
        nXpos = (U32)(nPtIdx * fXmag);

    fYmag = getRealMag(m_GraphConfig.eYmag, bLog);
    if(bLog)
    {
        if(sPointInfo.nParams[m_GraphConfig.nValueCol] == 0) nYpos = 0;
        else nYpos = (U32)logB((double)sPointInfo.nParams[m_GraphConfig.nValueCol], fYmag);
    }
    else
        nYpos = (U32)(sPointInfo.nParams[m_GraphConfig.nValueCol] * fYmag);

    return true;
}

bool CNfsGraphManager::GetPosInfo(U32 nGraphIdx, U32 nPtIdx, NG_POINT_INFO &sPoint)
{
    if(nGraphIdx >= m_vecNfsPoints.size()) return false;
    if(nPtIdx >= m_vecNfsPoints[nGraphIdx]->GetCount()) return false;

    if(m_vecNfsPoints[nGraphIdx]->GetPoint(nPtIdx, sPoint) == false) return false;

    return true;
}

std::string CNfsGraphManager::GetParamString(U32 nParamIdx, U32 nParamValue)
{
    if(nParamIdx >= MAX_NUM_OF_PARAM) return "";
    if((m_GraphConfig.mapParamName[nParamIdx].find(nParamValue) == m_GraphConfig.mapParamName[nParamIdx].end())
        || m_GraphConfig.mapParamName[nParamIdx][nParamValue].compare("") == 0)
    {
        char szTempString[100];
        sprintf(szTempString, "%d", nParamValue);
        szTempString[99] = '\0';
        return szTempString;
    }
    else
        return m_GraphConfig.mapParamName[nParamIdx][nParamValue];
}

bool CNfsGraphManager::SetParamString(U32 nParamIdx, U32 nParamValue, std::string strAlias)
{
    if(nParamIdx >= MAX_NUM_OF_PARAM) return false;
    m_GraphConfig.mapParamName[nParamIdx][nParamValue] = strAlias;
    return true;
}

bool CNfsGraphManager::GetLegendValue(U32 nGraphIdx, U32 nPtIdx, U32 &nValue)
{
    NG_POINT_INFO sPointInfo;
    if(nGraphIdx >= m_vecNfsPoints.size()) return false;
    if(nPtIdx >= m_vecNfsPoints[nGraphIdx]->GetCount()) return false;

    if(m_vecNfsPoints[nGraphIdx]->GetPoint(nPtIdx, sPointInfo) == false) return false;

    if(m_GraphConfig.nLegendCol >= m_vecNfsPoints[nGraphIdx]->GetNumOfParams()) m_GraphConfig.nLegendCol = m_vecNfsPoints[nGraphIdx]->GetNumOfParams() - 1;

    nValue = sPointInfo.nParams[m_GraphConfig.nLegendCol];

    return true;
}

}