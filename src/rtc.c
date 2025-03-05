#include "global.h"
#include "event_data.h"
#include "rtc.h"
#include "siirtc.h"
#include "string_util.h"
#include "strings.h"
#include "text.h"
#include "fake_rtc.h"

// iwram bss
static u16 sErrorStatus;
static struct SiiRtcInfo sRtc;
static u8 sProbeResult;
static u16 sSavedIme;

// iwram common
COMMON_DATA struct Time gLocalTime = {0};

// const rom

static const struct SiiRtcInfo sRtcDummy = {0, MONTH_JAN, 1}; // 2000 Jan 1

static const s32 sNumDaysInMonths[MONTH_COUNT] =
{
    [MONTH_JAN - 1] = 31,
    [MONTH_FEB - 1] = 28,
    [MONTH_MAR - 1] = 31,
    [MONTH_APR - 1] = 30,
    [MONTH_MAY - 1] = 31,
    [MONTH_JUN - 1] = 30,
    [MONTH_JUL - 1] = 31,
    [MONTH_AUG - 1] = 31,
    [MONTH_SEP - 1] = 30,
    [MONTH_OCT - 1] = 31,
    [MONTH_NOV - 1] = 30,
    [MONTH_DEC - 1] = 31,
};

void RtcDisableInterrupts(void)
{
    sSavedIme = REG_IME;
    REG_IME = 0;
}

void RtcRestoreInterrupts(void)
{
    REG_IME = sSavedIme;
}

u32 ConvertBcdToBinary(u8 bcd)
{
    if (OW_USE_FAKE_RTC)
        return bcd;

    if (bcd > 0x9F)
        return 0xFF;

    if ((bcd & 0xF) <= 9)
        return (10 * ((bcd >> 4) & 0xF)) + (bcd & 0xF);
    else
        return 0xFF;
}

bool8 IsLeapYear(u32 year)
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        return TRUE;

    return FALSE;
}

u16 ConvertDateToDayCount(u8 year, u8 month, u8 day)
{
    s32 i;
    u16 dayCount = 0;

    for (i = year - 1; i >= 0; i--)
    {
        dayCount += 365;

        if (IsLeapYear(i) == TRUE)
            dayCount++;
    }

    for (i = 0; i < month - 1; i++)
        dayCount += sNumDaysInMonths[i];

    if (month > MONTH_FEB && IsLeapYear(year) == TRUE)
        dayCount++;

    dayCount += day;

    return dayCount;
}

u16 RtcGetDayCount(struct SiiRtcInfo *rtc)
{
    u8 year, month, day;

    if (OW_USE_FAKE_RTC)
        return rtc->day;

    year = ConvertBcdToBinary(rtc->year);
    month = ConvertBcdToBinary(rtc->month);
    day = ConvertBcdToBinary(rtc->day);
    return ConvertDateToDayCount(year, month, day);
}

void RtcInit(void)
{
    if (OW_USE_FAKE_RTC)
        return;

    sErrorStatus = 0;

    RtcDisableInterrupts();
    SiiRtcUnprotect();
    sProbeResult = SiiRtcProbe();
    RtcRestoreInterrupts();

    if ((sProbeResult & 0xF) != 1)
    {
        sErrorStatus = RTC_INIT_ERROR;
        return;
    }

    if (sProbeResult & 0xF0)
        sErrorStatus = RTC_INIT_WARNING;
    else
        sErrorStatus = 0;

    RtcGetRawInfo(&sRtc);
    sErrorStatus = RtcCheckInfo(&sRtc);
}

u16 RtcGetErrorStatus(void)
{
    return (OW_USE_FAKE_RTC) ? 0 : sErrorStatus;
}

void RtcGetInfo(struct SiiRtcInfo *rtc)
{
    if (OW_USE_FAKE_RTC)
        FakeRtc_GetRawInfo(rtc);
    else if (sErrorStatus & RTC_ERR_FLAG_MASK)
        *rtc = sRtcDummy;
    else
        RtcGetRawInfo(rtc);
}

void RtcGetDateTime(struct SiiRtcInfo *rtc)
{
    RtcDisableInterrupts();
    SiiRtcGetDateTime(rtc);
    RtcRestoreInterrupts();
}

void RtcGetStatus(struct SiiRtcInfo *rtc)
{
    RtcDisableInterrupts();
    SiiRtcGetStatus(rtc);
    RtcRestoreInterrupts();
}

void RtcGetRawInfo(struct SiiRtcInfo *rtc)
{
    RtcGetStatus(rtc);
    RtcGetDateTime(rtc);
}

u16 RtcCheckInfo(struct SiiRtcInfo *rtc)
{
    u16 errorFlags = 0;
    s32 year;
    s32 month;
    s32 value;

    if (OW_USE_FAKE_RTC)
        return 0;

    if (rtc->status & SIIRTCINFO_POWER)
        errorFlags |= RTC_ERR_POWER_FAILURE;

    if (!(rtc->status & SIIRTCINFO_24HOUR))
        errorFlags |= RTC_ERR_12HOUR_CLOCK;

    year = ConvertBcdToBinary(rtc->year);

    if (year == 0xFF)
        errorFlags |= RTC_ERR_INVALID_YEAR;

    month = ConvertBcdToBinary(rtc->month);

    if (month == 0xFF || month == 0 || month > MONTH_COUNT)
        errorFlags |= RTC_ERR_INVALID_MONTH;

    value = ConvertBcdToBinary(rtc->day);

    if (value == 0xFF)
        errorFlags |= RTC_ERR_INVALID_DAY;

    if (month == MONTH_FEB)
    {
        if (value > IsLeapYear(year) + sNumDaysInMonths[month - 1])
            errorFlags |= RTC_ERR_INVALID_DAY;
    }
    else
    {
        if (value > sNumDaysInMonths[month - 1])
            errorFlags |= RTC_ERR_INVALID_DAY;
    }

    value = ConvertBcdToBinary(rtc->hour);

    if (value > HOURS_PER_DAY)
        errorFlags |= RTC_ERR_INVALID_HOUR;

    value = ConvertBcdToBinary(rtc->minute);

    if (value > MINUTES_PER_HOUR)
        errorFlags |= RTC_ERR_INVALID_MINUTE;

    value = ConvertBcdToBinary(rtc->second);

    if (value > SECONDS_PER_MINUTE)
        errorFlags |= RTC_ERR_INVALID_SECOND;

    return errorFlags;
}

void RtcReset(void)
{
    if (OW_USE_FAKE_RTC)
    {
        memset(FakeRtc_GetCurrentTime(), 0, sizeof(struct Time));
        return;
    }

    RtcDisableInterrupts();
    SiiRtcReset();
    RtcRestoreInterrupts();
}

void FormatDecimalTime(u8 *dest, s32 hour, s32 minute, s32 second)
{
    dest = ConvertIntToDecimalStringN(dest, hour, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest++ = CHAR_COLON;
    dest = ConvertIntToDecimalStringN(dest, minute, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest++ = CHAR_COLON;
    dest = ConvertIntToDecimalStringN(dest, second, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest = EOS;
}

void FormatHexTime(u8 *dest, s32 hour, s32 minute, s32 second)
{
    dest = ConvertIntToHexStringN(dest, hour, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest++ = CHAR_COLON;
    dest = ConvertIntToHexStringN(dest, minute, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest++ = CHAR_COLON;
    dest = ConvertIntToHexStringN(dest, second, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest = EOS;
}

void FormatHexRtcTime(u8 *dest)
{
    FormatHexTime(dest, sRtc.hour, sRtc.minute, sRtc.second);
}

void FormatDecimalDateDay(u8 *dest, s32 day)
{
    dest = ConvertIntToDecimalStringN(dest, day, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest++ = CHAR_SPACE;
    *dest = EOS;
}
void FormatDecimalDateYear(u8 *dest, s32 year)
{
    *dest++ = CHAR_SPACE;
    dest = ConvertIntToDecimalStringN(dest, year, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest = EOS;
}

void FormatDecimalDate(u8 *dest, s32 year, s32 month, s32 day)
{
    dest = ConvertIntToDecimalStringN(dest, year, STR_CONV_MODE_LEADING_ZEROS, 4);
    *dest++ = CHAR_HYPHEN;
    dest = ConvertIntToDecimalStringN(dest, month, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest++ = CHAR_HYPHEN;
    dest = ConvertIntToDecimalStringN(dest, day, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest = EOS;
}

void FormatHexDate(u8 *dest, s32 year, s32 month, s32 day)
{
    dest = ConvertIntToHexStringN(dest, year, STR_CONV_MODE_LEADING_ZEROS, 4);
    *dest++ = CHAR_HYPHEN;
    dest = ConvertIntToHexStringN(dest, month, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest++ = CHAR_HYPHEN;
    dest = ConvertIntToHexStringN(dest, day, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest = EOS;
}

void RtcCalcTimeDifference(struct SiiRtcInfo *rtc, struct Time *result, struct Time *t)
{
    u16 days = RtcGetDayCount(rtc);
    result->seconds = ConvertBcdToBinary(rtc->second) - t->seconds;
    result->minutes = ConvertBcdToBinary(rtc->minute) - t->minutes;
    result->hours = ConvertBcdToBinary(rtc->hour) - t->hours;
    result->days = days - t->days;

    if (result->seconds < 0)
    {
        result->seconds += SECONDS_PER_MINUTE;
        --result->minutes;
    }

    if (result->minutes < 0)
    {
        result->minutes += MINUTES_PER_HOUR;
        --result->hours;
    }

    if (result->hours < 0)
    {
        result->hours += HOURS_PER_DAY;
        --result->days;
    }
}

void RtcCalcLocalTime(void)
{
    RtcGetInfo(&sRtc);
    RtcCalcTimeDifference(&sRtc, &gLocalTime, &gSaveBlock2Ptr->localTimeOffset);
}

u8 Rtc_GetCurrentHour(void) // Returns current hour from RTC data
{     
    RtcGetInfo(&sRtc);	
	return sRtc.hour - (sRtc.hour/0x10) * 6;
}
u8 Rtc_GetCurrentMinute(void){ // Returns current minute from RTC data
    
    RtcGetInfo(&sRtc);
    return sRtc.minute - (sRtc.minute/0x10) * 6;
}
u8 Rtc_GetCurrentMonth(void)
{
    RtcGetInfo(&sRtc);
    return sRtc.month < 10 ? sRtc.month : sRtc.month - 6;
}
u8 Rtc_GetCurrentDay(void)
{
    RtcGetInfo(&sRtc);
    return sRtc.day - (sRtc.day/0x10) * 6;
}
u8 Rtc_GetCurrentYear(void)
{
    RtcGetInfo(&sRtc);
    return sRtc.year - (sRtc.year/0x10) * 6;
}
u8 Rtc_GetCurrentDayOfWeek(void)
{
    RtcGetInfo(&sRtc);
    return sRtc.dayOfWeek;
}
void UpdateDayOfWeek(void)
{
    VarSet(VAR_CURRENT_DAYOFWEEK, Rtc_GetCurrentDayOfWeek());
}
u8 valueinarray(u8 val, u8 *arr, int n)
{
    int i;
    for(i = 0; i < n; i++) {
        if(arr[i] == val)
            return 1;
    }
    return 0;
}
void Rtc_GetCurrentSeason_Short(void)
{
    // Gets current mont as integer.
    u8 current_month = Rtc_GetCurrentMonth();
    // Creates array with seasons as integers
    u8 summer[3] = {1, 5, 9};
    u8 autumm[3] = {2, 6, 10};
    u8 winter[3] = {3, 7, 11};
    u8 spring[3] = {4, 8, 12};
    // Checks where is current month located
    u8 is_summer = valueinarray(current_month, summer, 3);
    u8 is_autumm = valueinarray(current_month, autumm, 3);
    u8 is_winter = valueinarray(current_month, winter, 3);
    u8 is_spring = valueinarray(current_month, spring, 3);
    if(is_summer == 1)
        VarSet(VAR_CURRENT_SEASON, SEASON_SUMMER);
    if(is_autumm == 1)
        VarSet(VAR_CURRENT_SEASON, SEASON_AUTUMM);
    if(is_winter == 1)
        VarSet(VAR_CURRENT_SEASON, SEASON_WINTER);
    if(is_spring == 1)
        VarSet(VAR_CURRENT_SEASON, SEASON_SPRING);
}
void UpdateSeason(void)
{
    Rtc_GetCurrentSeason_Short();
}
// Convertir de Season(Int) a Season(Str)
const u8 *ConvertSeasonInt2Str(void)
{
    u8 season = VarGet(VAR_CURRENT_SEASON);
    switch(season)
    {
    case SEASON_SUMMER:
        return gText_SEASONS_Summer;
    case SEASON_AUTUMM:
        return gText_SEASONS_Autumm;
    case SEASON_WINTER:
        return gText_SEASONS_Winter;
    case SEASON_SPRING:
        return gText_SEASONS_Spring;
    default:
        return gText_SEASONS_Summer;
    }
}
const u8 *ConvertDayOfWeekInt2Str(void)
{
    u8 dayOfWeek = VarGet(VAR_CURRENT_DAYOFWEEK);
    switch(dayOfWeek)
    {
    case SUNDAY:
        return gText_dayOfWeek_Sunday;
    case MONDAY:
        return gText_dayOfWeek_Monday;
    case TUESDAY:
        return gText_dayOfWeek_Tuesday;
    case WEDNESDAY:
        return gText_dayOfWeek_Wednesday;
    case THURSDAY:
        return gText_dayOfWeek_Thursday;
    case FRIDAY:
        return gText_dayOfWeek_Friday;
    case SATURDAY:
        return gText_dayOfWeek_Saturday;
    default:
        return gText_dayOfWeek_Saturday;
    }
}
const u8 *ConvertMonth2Str(u8 month_int)
{
    if(month_int == MONTH_JAN)
        return gText_MONTH_JAN;
    if(month_int == MONTH_FEB)
        return gText_MONTH_FEB;
    if(month_int == MONTH_MAR)
        return gText_MONTH_MAR;
    if(month_int == MONTH_APR)
        return gText_MONTH_APR;
    if(month_int == MONTH_MAY)
        return gText_MONTH_MAY;
    if(month_int == MONTH_JUN)
        return gText_MONTH_JUN;
    if(month_int == MONTH_JUL)
        return gText_MONTH_JUL;
    if(month_int == MONTH_AUG)
        return gText_MONTH_AUG;
    if(month_int == MONTH_SEP)
        return gText_MONTH_SEP;
    if(month_int == MONTH_OCT)
        return gText_MONTH_OCT;
    if(month_int == MONTH_NOV)
        return gText_MONTH_NOV;
    if(month_int == MONTH_DEC)
        return gText_MONTH_DEC;
    else
        return gText_MONTH_JAN;
}
// Función para obtener los datos de hora y minutos del RTC
void FormatDecimalTimeWOSeconds(u8 *dest, u8 hour, u8 minute)
{
    dest = ConvertIntToDecimalStringN(dest, hour, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest++ = CHAR_COLON;
    dest = ConvertIntToDecimalStringN(dest, minute, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest = EOS;
}

bool8 IsBetweenHours(s32 hours, s32 begin, s32 end)
{
    if (end < begin)
        return hours >= begin || hours < end;
    else
        return hours >= begin && hours < end;
}

u8 GetTimeOfDay(void)
{
    RtcCalcLocalTime();
    if (IsBetweenHours(gLocalTime.hours, MORNING_HOUR_BEGIN, MORNING_HOUR_END))
        return TIME_MORNING;
    else if (IsBetweenHours(gLocalTime.hours, EVENING_HOUR_BEGIN, EVENING_HOUR_END))
        return TIME_EVENING;
    else if (IsBetweenHours(gLocalTime.hours, NIGHT_HOUR_BEGIN, NIGHT_HOUR_END))
        return TIME_NIGHT;
    return TIME_DAY;
}

void RtcInitLocalTimeOffset(s32 hour, s32 minute)
{
    RtcCalcLocalTimeOffset(0, hour, minute, 0);
}

void RtcCalcLocalTimeOffset(s32 days, s32 hours, s32 minutes, s32 seconds)
{
    gLocalTime.days = days;
    gLocalTime.hours = hours;
    gLocalTime.minutes = minutes;
    gLocalTime.seconds = seconds;
    RtcGetInfo(&sRtc);
    RtcCalcTimeDifference(&sRtc, &gSaveBlock2Ptr->localTimeOffset, &gLocalTime);
}

void CalcTimeDifference(struct Time *result, struct Time *t1, struct Time *t2)
{
    result->seconds = t2->seconds - t1->seconds;
    result->minutes = t2->minutes - t1->minutes;
    result->hours = t2->hours - t1->hours;
    result->days = t2->days - t1->days;

    if (result->seconds < 0)
    {
        result->seconds += SECONDS_PER_MINUTE;
        --result->minutes;
    }

    if (result->minutes < 0)
    {
        result->minutes += MINUTES_PER_HOUR;
        --result->hours;
    }

    if (result->hours < 0)
    {
        result->hours += HOURS_PER_DAY;
        --result->days;
    }
}

u32 RtcGetMinuteCount(void)
{
    RtcGetInfo(&sRtc);
    return (HOURS_PER_DAY * MINUTES_PER_HOUR) * RtcGetDayCount(&sRtc) + MINUTES_PER_HOUR * sRtc.hour + sRtc.minute;
}

u32 RtcGetLocalDayCount(void)
{
    return RtcGetDayCount(&sRtc);
}

void FormatDecimalTimeWithoutSeconds(u8 *txtPtr, s8 hour, s8 minute, bool32 is24Hour)
{
    if (is24Hour)
    {
        txtPtr = ConvertIntToDecimalStringN(txtPtr, hour, STR_CONV_MODE_LEADING_ZEROS, 2);
        *txtPtr++ = CHAR_COLON;
        txtPtr = ConvertIntToDecimalStringN(txtPtr, minute, STR_CONV_MODE_LEADING_ZEROS, 2);
    }
    else
    {
        if (hour == 0)
            txtPtr = ConvertIntToDecimalStringN(txtPtr, 12, STR_CONV_MODE_LEADING_ZEROS, 2);
        else if (hour < 13)
            txtPtr = ConvertIntToDecimalStringN(txtPtr, hour, STR_CONV_MODE_LEADING_ZEROS, 2);
        else
            txtPtr = ConvertIntToDecimalStringN(txtPtr, hour - 12, STR_CONV_MODE_LEADING_ZEROS, 2);

        *txtPtr++ = CHAR_COLON;
        txtPtr = ConvertIntToDecimalStringN(txtPtr, minute, STR_CONV_MODE_LEADING_ZEROS, 2);
        txtPtr = StringAppend(txtPtr, gText_Space);
        if (hour < 12)
            txtPtr = StringAppend(txtPtr, gText_AM);
        else
            txtPtr = StringAppend(txtPtr, gText_PM);
    }

    *txtPtr++ = EOS;
    *txtPtr = EOS;
}
