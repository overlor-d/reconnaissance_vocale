#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>

#include "audioCapture.h"
#include "AudioManipulation.h"

int lecture_fichier_brut()
{
    FILE *fichierTestEnregistrement;
    POINT_GRAPH point;

    printf("Lecture du fichier :\n");

    fichierTestEnregistrement = fopen(FICHIER_TEST_ENREGISTREMENT, "rb");
    if (fichierTestEnregistrement == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier de test\n");
        return 3;
    }

    while (fread(&point, sizeof(POINT_GRAPH), 1, fichierTestEnregistrement) == 1)
    {
        printf("%hd\n", point.valeur);
    }

    fclose(fichierTestEnregistrement);
    return 0;
}

int jouer_audio(short * buffer, DWORD taille)
{
    HWAVEOUT handleOutput;
    WAVEFORMATEX format;
    WAVEHDR bufferLecture;

    format.wFormatTag = WAVE_FORMAT_PCM;
    format.nChannels = 1;
    format.nSamplesPerSec = ENCHANTILLONAGE;
    format.wBitsPerSample = BITS_PAR_SAMPLE;
    format.nBlockAlign = (format.nChannels * format.wBitsPerSample) / 8;
    format.nAvgBytesPerSec = format.nSamplesPerSec * format.nBlockAlign;
    format.cbSize = 0;

    MMRESULT res = waveOutOpen(&handleOutput, WAVE_MAPPER, &format, 0, 0, CALLBACK_NULL);
    if (res != MMSYSERR_NOERROR) {
        char err[256];
        waveOutGetErrorText(res, err, sizeof(err));
        printf("Erreur lors de l'ouverture du périphérique de sortie : %s\n", err);
        return 1;
    }

    bufferLecture.lpData = (LPSTR)buffer;
    bufferLecture.dwBufferLength = taille;
    bufferLecture.dwFlags = 0;
    bufferLecture.dwLoops = 0;

    waveOutPrepareHeader(handleOutput, &bufferLecture, sizeof(WAVEHDR));
    waveOutWrite(handleOutput, &bufferLecture, sizeof(WAVEHDR));

    

    while (!(bufferLecture.dwFlags & WHDR_DONE))
    {
        Sleep(10);
    }

    waveOutUnprepareHeader(handleOutput, &bufferLecture, sizeof(WAVEHDR));
    waveOutClose(handleOutput);


    return 0;
}

int recup_echantillon(short * buffer, DWORD taille)
{
    FILE * fichier = fopen(FICHIER_TEST_ENREGISTREMENT, "rb");

    if (fichier == NULL)
    {
        printf("Problème d'ouverture de fichier");
        return 1;
    }

    fread(buffer, 1, taille, fichier);
    fclose(fichier);
    
    return 0;
}

int main(void)
{
    short bufferSonBrut[TAILLE_BUFFER];

    recup_echantillon(bufferSonBrut, TAILLE_BUFFER);

    jouer_audio(bufferSonBrut, TAILLE_BUFFER);

    return 0;
}