#ifndef WAVreader
#define WAVreader

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <fstream>

using namespace std;

struct FmtChunk  //ONLY PCM
{
    int cksize;// 4     chunk size
    int wFormatTag;//	2	Format code
    int nChannels;//	2	Number of interleaved channels
    int nSamplesPerSec;//	4	Sampling rate (blocks per second)
    int nAvgBytesPerSec;//	4	Data rate
    int nBlockAlign;	//2	Data block size (bytes)
    int wBitsPerSample;//	2	Bits per sample

};
struct DataChunk  // for max 2 channels
{
    int size;
    vector <int> channels[2];
};

class WAVReader  // Only PCM Wave files
{
private:
    ifstream file;

public:
    vector <unsigned char> buffer;
    FmtChunk FMT;
    DataChunk DATA;
    WAVReader(string name)
    {
        file.open(name.c_str(),iostream::binary);
        if(file.good())
        {    //TO DO
            vector <unsigned char> temp((
            std::istreambuf_iterator<char>(file)),
            (std::istreambuf_iterator<char>()));
            buffer = temp;
            makefmtchunk();
            makedatachunk();
        }
    }
    ~WAVReader()
    {
        file.close();
        buffer.clear();

    }
    unsigned int littletobigendian4(unsigned int first, unsigned int second, unsigned int third, unsigned int fourth)
    {
        return first+(second<<8)+(third<<16)+(fourth<<24);
    }
    unsigned int littletobigendian2(unsigned int first, unsigned int second)
    {
        return first+(second<<8);
    }
    void makefmtchunk()
    {
        int index;
        for(int i = 0; i<buffer.size(); i++)
        {
            if(buffer[i]=='f' && buffer[i+1]=='m' && buffer[i+2]=='t')
            {
                index = i+4;
                break;
            }
        }
        //index+=4;
        FMT.cksize = littletobigendian4(buffer[index],buffer[index+1],buffer[index+2],buffer[index+3]);
        if(FMT.cksize!=16)
        {
            //TO DO // wywalić program gdy wave nie jest PCM
        }
        index+=4;
        FMT.wFormatTag = littletobigendian2(buffer[index],buffer[index+1]);
        if(FMT.wFormatTag!=1)
        {
            //TO DO //wywalic bo na pewno nie PCM
        }
        index+=2;
        FMT.nChannels = littletobigendian2(buffer[index],buffer[index+1]);
        index+=2;
        FMT.nSamplesPerSec = littletobigendian4(buffer[index],buffer[index+1],buffer[index+2],buffer[index+3]);
        index+=4;
        FMT.nAvgBytesPerSec = littletobigendian4(buffer[index],buffer[index+1],buffer[index+2],buffer[index+3]);
        index+=4;
        FMT.nBlockAlign = littletobigendian2(buffer[index],buffer[index+1]);
        index+=2;
        FMT.wBitsPerSample = littletobigendian2(buffer[index],buffer[index+1]);
        index+=2;
    }

    void makedatachunk()
    {
        int index;
        for(int i = 0; i<buffer.size(); i++)
        {
            if(buffer[i]=='d' && buffer[i+1]=='a' && buffer[i+2]=='t' && buffer[i+3]=='a')
            {
                index = i+4;
                break;
            }
        }
        DATA.size = littletobigendian4(buffer[index],buffer[index+1],buffer[index+2],buffer[index+3]);
        index+=4;
        int amountofbytes = FMT.wBitsPerSample/8;
        if(amountofbytes==2)   // TO DO FOR DIFFERENT VALUES THAN 2
        {
            for(int i = 0; i<DATA.size; )
            {
                for(int j = 0; j<FMT.nChannels; j++)
                {
                    DATA.channels[j].push_back(littletobigendian2(buffer[index],buffer[index+1]));  // to do different endians than 2
                    i+=2;
                    index+=2;
                }
            }
        }

    }
};
#endif // WAVreader
