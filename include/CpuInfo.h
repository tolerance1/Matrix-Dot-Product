#ifndef CPUINFO_H
#define CPUINFO_H

#include <string>

using std::string;

class CpuInfo
{
    public:
        CpuInfo();

        string& getVendorID() {return vendorID; }
        string& getBrandString() {return brandString; }

    private:
        string vendorID {"Unknown"};
        string brandString {"Unknown"};

        uint32_t eax, ebx, ecx, edx;

        enum eaxValues {query_vendorID = 0,
                        query_brandString_support = 0x80000000,
                        query_brandString_1 = 0x80000002,
                        query_brandString_2 = 0x80000003,
                        query_brandString_3 = 0x80000004};


        string to_string(uint32_t reg);

        void aggregateVendorID();
        void aggregateBrandString();
        void removeFillChars(string& str);
};

#endif // CPUINFO_H
