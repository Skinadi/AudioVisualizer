#ifndef FFT_h
#define FFT_h

#include <math.h>
#include <fftw3.h>

struct Data
{
    double freqwency;
    double magnitude;
    double aplitude;
};
class FFT
{
private:
    fftw_complex *in, *out;
    fftw_plan p;
    int FPS;
    int currTime;
    int channel;
    WAVReader * file;
    int data_size;

    int * data;
    int SamplesPerSecond;
public:
    Data * tab;
    FFT(WAVReader * file,int FPS,int channel)
    {
        this->file=file;
        this->FPS=FPS;
        this->currTime=0;
        this->channel=channel;
        in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * file->FMT.nSamplesPerSec/FPS);
        out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * file->FMT.nSamplesPerSec/FPS);
        tab = new Data[file->FMT.nSamplesPerSec/FPS];
        this->data_size = file->FMT.nSamplesPerSec/FPS;

        data = file->DATA.channels[channel].data();
        this->SamplesPerSecond=file->FMT.nSamplesPerSec;
    }
    ~FFT()
    {
        fftw_destroy_plan(p);
        fftw_free(in);
        fftw_free(out);
        delete [] tab;
    }
    void calkulateNext()
    {
        for(int i = currTime; i<SamplesPerSecond/FPS+currTime; i++)  //60 FPS
        {
            in[i-currTime][0]=data[i];
            in[i-currTime][1]=0;
            out[i-currTime][0]=0;
            out[i-currTime][1]=0;
        }
        currTime = SamplesPerSecond/FPS + currTime;     //TO DO - END OF DATA/MUSIC

        p = fftw_plan_dft_1d(SamplesPerSecond/FPS, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

        fftw_execute(p); /* repeat as needed */

        for(int i = 0; i<SamplesPerSecond/FPS; i++)
        {
            tab[i].magnitude = 20 * log10(sqrt(out[i][0]*out[i][0] + out[i][1]*out[i][1]));
            tab[i].freqwency = i * FPS;
            tab[i].aplitude = out[i][0];
        }
    }
    int getFPS()
    {
        return FPS;
    }
    int get_data_size()
    {
        return data_size;
    }

};

#endif // FFT_h
