#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>


#define ENCHANTILLONAGE 44100
#define BITS_PAR_SAMPLE 16


int main(void)
{
    HWAVEIN handlePeriphAudio;
    WAVEFORMATEX formatAduio;

    MMRESULT statusPeriphOpen;
    MMRESULT statusPeriphClose;

    /* changement de l'encodage pour l'affichage de la console */
    UINT oldCP = GetConsoleOutputCP();
    if (oldCP != 65001) {
        SetConsoleOutputCP(65001);
    }

    formatAduio.wFormatTag = WAVE_FORMAT_PCM;
    formatAduio.nChannels = 1;
    formatAduio.nSamplesPerSec = 44100;
    formatAduio.wBitsPerSample = 16;
    formatAduio.nBlockAlign = (formatAduio.nChannels * formatAduio.wBitsPerSample) / 8;
    formatAduio.nAvgBytesPerSec = formatAduio.nSamplesPerSec * formatAduio.nBlockAlign;
    formatAduio.cbSize = 0;



    statusPeriphOpen = waveInOpen(&handlePeriphAudio, WAVE_MAPPER, &formatAduio, 0, 0, CALLBACK_NULL);

    if (statusPeriphOpen != MMSYSERR_NOERROR)
    {
        printf("erreur lors de l'ouverture du périphérique. Erreur : %d\n", statusPeriphOpen);
        return 1;
    }

    printf("Périphérique ouvert sans problèmes\n");

    statusPeriphClose = waveInClose(handlePeriphAudio);

    if (statusPeriphClose != MMSYSERR_NOERROR)
    {
        printf("erreur lors de la fermeture du périphérique. Erreur : %d\n", statusPeriphClose);
        return 2;
    }

    printf("Périphérique fermé sans problèmes\n");

    return 0;
}