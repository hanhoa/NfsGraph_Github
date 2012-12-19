#pragma once

#include <vector>
#include <string>
#include "gdefine.h"

#define MAX_POINT_COMMENT   20
#define MAX_NUM_OF_PARAM    15      // the number of parameters

namespace NfsGraph
{

struct NG_POINT_INFO
{
    U32 nParams[MAX_NUM_OF_PARAM];
};

class CNfsPoints
{
public:
    CNfsPoints() : m_nNumOfParams(0) { 
        for(int i = 0; i < MAX_NUM_OF_PARAM; i++) 
        { m_nMaxParams[i] = 0; m_strParamTitle[i] = "NoTitle"; }
    }
    void AddPoint(void);
    void RemoveAllPoint(void);

    bool WriteParam(U32 nIndex, U16 nParamIdx, U32 nParamValue);
    bool WriteParamAtLastPoint(U16 nParamIdx, U32 nParamValue);
    bool WriteParamTitle(U32 nParamIdx, std::string strName);

    bool GetPoint(U32 nIndex, NG_POINT_INFO &sPoint);
    U32  GetCount(void) { return m_vecPoints.size(); }

    U32  GetNumOfParams(void) { return m_nNumOfParams; }
    std::string GetParamTitle(U32 nParamIdx) { return m_strParamTitle[nParamIdx]; }
    U32  GetMaxParam(U32 nParamIdx) { return m_nMaxParams[nParamIdx]; }
    
private:
    std::vector<NG_POINT_INFO> m_vecPoints;
    
    std::string m_strParamTitle[MAX_NUM_OF_PARAM];
    U32 m_nMaxParams[MAX_NUM_OF_PARAM];
    U32 m_nNumOfParams;
};

inline void CNfsPoints::AddPoint(void)
{
    m_vecPoints.push_back(NG_POINT_INFO());
    for(int i = 0; i < MAX_NUM_OF_PARAM; i++) m_vecPoints.back().nParams[i] = 0;
}

inline void CNfsPoints::RemoveAllPoint(void)
{
    m_vecPoints.clear();
    for(int i = 0; i < MAX_NUM_OF_PARAM; i++) m_nMaxParams[i] = 0;
}

inline bool CNfsPoints::WriteParam(U32 nIndex, U16 nParamIdx, U32 nParamValue)
{
    if(nIndex >= m_vecPoints.size()) return false;
    if(nParamIdx >= MAX_NUM_OF_PARAM) return false;

    m_vecPoints[nIndex].nParams[nParamIdx] = nParamValue;
    if(nParamIdx >= m_nNumOfParams) m_nNumOfParams = nParamIdx + 1;

    if(m_nMaxParams[nParamIdx] < nParamValue) m_nMaxParams[nParamIdx] = nParamValue;
    return true;
}

inline bool CNfsPoints::WriteParamAtLastPoint(U16 nParamIdx, U32 nParamValue)
{
    if(nParamIdx >= MAX_NUM_OF_PARAM) return false;

    m_vecPoints.back().nParams[nParamIdx] = nParamValue;
    if(nParamIdx >= m_nNumOfParams) m_nNumOfParams = nParamIdx + 1;

    if(m_nMaxParams[nParamIdx] < nParamValue) m_nMaxParams[nParamIdx] = nParamValue;
    return true;
}

inline bool CNfsPoints::WriteParamTitle(U32 nParamIdx, std::string strName)
{
    if(nParamIdx >= MAX_NUM_OF_PARAM) return false;
    if(nParamIdx >= m_nNumOfParams) m_nNumOfParams = nParamIdx + 1;
    m_strParamTitle[nParamIdx] = strName;
    return true;
}

inline bool CNfsPoints::GetPoint(U32 nIndex, NG_POINT_INFO &sPoint)
{
    if(nIndex >= m_vecPoints.size()) return false;

    sPoint = m_vecPoints[nIndex];
    return true;
}

}