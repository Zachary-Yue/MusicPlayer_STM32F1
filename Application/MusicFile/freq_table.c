
#include "freq_table.h"


#define FTIM        (9000000.0f)
#define ARRT(f)     ((u16)((FTIM / (f)) - 0.50f))

/**
 * @brief 频率 - ARR 重装值对照表。
 * 
 */
static u16 FreqTab[] =
{
    ARRT(261.6255653f),     // C4
    ARRT(277.182631f),
    ARRT(293.6647679f),     // D4
    ARRT(311.1269837f),
    ARRT(329.6275569f),     // E4
    ARRT(349.2282314f),     // F4
    ARRT(369.9944227f),
    ARRT(391.995436f),      // G4
    ARRT(415.3046976f),
    ARRT(440.0f),             // A4
    ARRT(466.1637615f),
    ARRT(493.8833013f),     // B4
    ARRT(523.2511306f),     // C5
    ARRT(554.365262f),      // 下面的依此类推
    ARRT(587.3295358f),
    ARRT(622.2539674f),
    ARRT(659.2551138f),
    ARRT(698.4564629f),
    ARRT(739.9888454f),
    ARRT(783.990872f),
    ARRT(830.6093952f),
    ARRT(880.0f),
    ARRT(932.327523f),
    ARRT(987.7666025f),
    ARRT(1046.502261f),
    ARRT(1108.730524f),
    ARRT(1174.659072f),
    ARRT(1244.507935f),
    ARRT(1318.510228f),
    ARRT(1396.912926f),
    ARRT(1479.977691f),
    ARRT(1567.981744f),
    ARRT(1661.21879f),
    ARRT(1760.0f),
    ARRT(1864.655046f),
    ARRT(1975.533205f),
    ARRT(2093.004522f),
    ARRT(2217.461048f),
    ARRT(2349.318143f),
    ARRT(2489.01587f),
    ARRT(2637.020455f),
    ARRT(2793.825851f),
    ARRT(2959.955382f),
    ARRT(3135.963488f),
    ARRT(3322.437581f),
    ARRT(3520.0f),
    ARRT(3729.310092f),
    ARRT(3951.06641f),
};

u16 Get_Freq(u8 pitch)
{
    if (pitch >= sizeof(FreqTab) / sizeof(u16)) return 0xffff;
    return FreqTab[pitch];
}
