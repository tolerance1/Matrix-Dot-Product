#include "CpuInfo.h"

#include <cpuid.h>
#include <algorithm>

CpuInfo::CpuInfo()
{
    aggregateVendorID();
    aggregateBrandString();
}

string CpuInfo::to_string(uint32_t reg)
{
    return string (reinterpret_cast<char*>(&reg), sizeof(reg));
}

void CpuInfo::aggregateVendorID()
{
    if(__get_cpuid(query_vendorID, &eax, &ebx, &ecx, &edx) )
    {
        vendorID = to_string(ebx) + to_string(edx) + to_string(ecx);
    }
}

void CpuInfo::aggregateBrandString()
{
    if(__get_cpuid(query_brandString_support, &eax, &ebx, &ecx, &edx) )
    {
        if(eax >= 0x80000004) //brand string is supported
        {
            brandString.clear();

            eaxValues cycleOrder[3] = {query_brandString_1, query_brandString_2, query_brandString_3};

            for(size_t i = 0; i < 3; ++i)
            {
                __get_cpuid(cycleOrder[i], &eax, &ebx, &ecx, &edx);

                brandString += to_string(eax) + to_string(ebx) + to_string(ecx) + to_string(edx);
            }

            removeFillChars(brandString);
        }
    }
}

void CpuInfo::removeFillChars(string& str)
{
    if(vendorID == "AuthenticAMD")
    {
        auto iter = find(str.begin(), str.end(), '\0');

        if(iter != str.end()) str.erase(iter, str.end());
    }
    else if(vendorID == "GenuineIntel")
    {
        //remove consecutive duplicate spaces
        auto iter = unique(str.begin(), str.end(),
                           [](char& ch1, char& ch2){return (ch1 == ' ' && ch2 == ' ');} );

        //erase the shifted duplicates
        if(iter != str.end()) str.erase(iter, str.end());

        if(* str.begin() == ' ') str.erase(str.begin());

        if(*(str.end() - 1) == '\0') str.erase(str.end() - 1);
    }
}
