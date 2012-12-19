#pragma once
#include "gdefine.h"
#include "NfsPoints.h"
#include "ParsingConfig.h"

#include <string>

namespace NfsGraph
{

class CNfsGraphManager
{
public:
    CNfsGraphManager(void);
    virtual ~CNfsGraphManager(void);

    void InitResource(void);
    void ClearResource(void);

    //////////////////////////////////////////////////////////////////////////
    // Read Log Information Function
    bool ReadLogFile(std::string strLogFileName, std::string strConfigFileName);
    void StopReadingLogFile(void);

    std::string GetErrorMsg(void) { return m_strErrorMsg; }


    //////////////////////////////////////////////////////////////////////////
    // Config Information Function
    U32  GetMainDataCol(void) { return m_GraphConfig.nValueCol; }
    void SetMainDataCol(U32 nValueCol) { m_GraphConfig.nValueCol = nValueCol; }

    U32  GetLegendCol(void) { return m_GraphConfig.nLegendCol; }
    void SetLegendCol(U32 nLegendCol) { m_GraphConfig.nLegendCol = nLegendCol; }

    GRAPH_TYPE GetGraphType(void) { return m_GraphConfig.eGraphType; }
    void SetGraphType(GRAPH_TYPE eType) { m_GraphConfig.eGraphType = eType; }

    void SetMagX(MAG_LEVEL eMagX) { m_GraphConfig.eXmag = eMagX; }
    void SetMagY(MAG_LEVEL eMagY) { m_GraphConfig.eYmag = eMagY; }
    MAG_LEVEL GetMagX(void) { return m_GraphConfig.eXmag; }
    MAG_LEVEL GetMagY(void) { return m_GraphConfig.eYmag; }

    std::string GetLegendString(U32 nParamValue) { return GetParamString(m_GraphConfig.nLegendCol, nParamValue); }
    bool SetLegendString(U32 nParamIdx, U32 nParamValue, std::string strAlias) { return SetParamString(m_GraphConfig.nLegendCol, nParamValue, strAlias); }

    void SaveConfigFile(std::string strFileName);


    //////////////////////////////////////////////////////////////////////////
    // Graph Information Functions
    //
    // X value is the row of data table. There are several data in a row. We call them 'Param' or 'Parameter'.
    // One of the params can be Y value. We call it 'Main Data'. 
    // Also, one of the params can be standard to distinguish Main Data. We call it 'Legend Data'.
    // There can be one more data tables in a log file. We distinguish them by 'Graph #1', 'Graph #2'....
    //

    U32  GetTotalCount(void) { return m_vecNfsPoints[m_nCurrentGraphNum]->GetCount(); }         // The total number of main data. (the number of rows of data table).
    U32  GetNumOfParams(void) { return m_vecNfsPoints[m_nCurrentGraphNum]->GetNumOfParams(); }  // The number of params. (the number of columns pf data table).
    U32  GetMaxValue(void) { return m_vecNfsPoints[m_nCurrentGraphNum]->GetMaxParam(m_GraphConfig.nValueCol); }   // The max value among main data.

    void SetCurGraphNum(U32 nGraphNum) { (nGraphNum < m_vecNfsPoints.size()) ? m_nCurrentGraphNum = nGraphNum : m_nCurrentGraphNum = (m_vecNfsPoints.size() - 1); }
    U32  GetCurGraphNum(void) { return m_nCurrentGraphNum; }
    U32  GetTotalNumOfGraph(void) { return (m_vecNfsPoints.size() - 1); }

    std::string GetDataTitle(U32 nIdx) { return (nIdx < GetNumOfParams()) ? m_vecNfsPoints[m_nCurrentGraphNum]->GetParamTitle(nIdx) : "NoTitle"; }  // To get the name of param.

    bool GetPosCoordinate(U32 nGraphIdx, U32 nPtIdx, U32 &nXpos, U32 &nYpos);     // Coordinates refer to the point which is left-bottom of canvas. cellsize is 1.

    bool GetLegendValue(U32 nGraphIdx, U32 nPtIdx, U32 &nValue);   // Get the value which is of legend column at the point.
    
 
private:
    bool GetPosInfo(U32 nGraphIdx, U32 nPtIdx, NG_POINT_INFO &sPoint);

    std::string GetParamString(U32 nParamIdx, U32 nParamValue);
    bool SetParamString(U32 nParamIdx, U32 nParamValue, std::string strAlias);

private:
    std::vector<CNfsPoints*> m_vecNfsPoints;
    ConfigBox m_GraphConfig;

    U32 m_nCurrentGraphNum;

    std::string m_strErrorMsg;
};

}
