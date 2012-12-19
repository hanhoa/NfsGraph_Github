#pragma once

#include <map>

#define PC_BLACK            RGB(0, 0, 0)
#define PC_BLUE             RGB(0, 0, 0xAA)
#define PC_GREEN            RGB(0, 0xAA, 0)
#define PC_CYAN             RGB(0, 0xAA, 0xAA)
#define PC_RED              RGB(0xAA, 0, 0)
#define PC_MAGENTA          RGB(0xAA, 0, 0xAA)
#define PC_BROWN            RGB(0xAA, 0x55, 0)
#define PC_LIGHTGRAY        RGB(0xAA, 0x55, 0x55)
#define PC_DARKGRAY         RGB(0x55, 0x55, 0x55)
#define PC_LIGHTBLUE        RGB(0x55, 0x55, 0xFF)
#define PC_LIGHTGREEN       RGB(0x55, 0xFF, 0x55)
#define PC_LIGHTCYAN        RGB(0x55, 0xFF, 0xFF)
#define PC_LIGHTRED         RGB(0xFF, 0x55, 0x55)
#define PC_LIGHTMAGENTA     RGB(0xFF, 0x55, 0xFF)
#define PC_YELLOW           RGB(0xFF, 0xFF, 0)
#define MAX_OF_COLORS       15

class CLegend
{
public:
    CLegend(CNfsGraphManager *pNGM);
    ~CLegend(void);

    void DrawLegend(CDC *pScreenDC, CDC *pMemDC, LONG cx, LONG cy);

    void LoadLegendValue(void);
    COLORREF GetLegendColor(U32 nLegendVal);

    U32 GetNumOfLegendItem(void) { return m_mapLegendValues.size(); }
    U32 GetLegendValue(U32 nIdx);

private:
    CLegend(void);

private:
    CNfsGraphManager *m_pNGM;

    COLORREF m_crPalette[MAX_OF_COLORS];
    std::map<U32, COLORREF> m_mapLegendValues;
};

