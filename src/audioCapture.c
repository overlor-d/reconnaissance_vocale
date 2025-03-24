#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>

#include "AudioCapture.h"

// Fonction pour enregistrer les données audio dans un fichier
int enregistrement_fichier(short *buffer)
{
    int i;
    FILE *fichierTestEnregistrement;
    POINT_GRAPH point;

    printf("Commencement de l'enregistrement dans le fichier de test\n");

    fichierTestEnregistrement = fopen(FICHIER_TEST_ENREGISTREMENT, "wb");
    if (fichierTestEnregistrement == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier de test\n");
        return 3;
    }

    for (i = 0; i < TAILLE_BUFFER / 2; i++)
    {
        point.valeur = buffer[i];

        fwrite(&point, sizeof(POINT_GRAPH), 1, fichierTestEnregistrement);
    }

    fclose(fichierTestEnregistrement);
    return 0;
}

// Fonction pour capturer le son depuis le micro
int capture_audio(short *bufferSonBrut)
{
    HWAVEIN handlePeriphAudio;
    WAVEFORMATEX formatAduio;
    MMRESULT statusPeriphOpen;
    MMRESULT statusPeriphClose;
    WAVEHDR bufferDescriptor;

    formatAduio.wFormatTag = WAVE_FORMAT_PCM;
    formatAduio.nChannels = 1;
    formatAduio.nSamplesPerSec = ENCHANTILLONAGE;
    formatAduio.wBitsPerSample = BITS_PAR_SAMPLE;
    formatAduio.nBlockAlign = (formatAduio.nChannels * formatAduio.wBitsPerSample) / 8;
    formatAduio.nAvgBytesPerSec = formatAduio.nSamplesPerSec * formatAduio.nBlockAlign;
    formatAduio.cbSize = 0;

    statusPeriphOpen = waveInOpen(&handlePeriphAudio, WAVE_MAPPER, &formatAduio, 0, 0, CALLBACK_NULL);
    if (statusPeriphOpen != MMSYSERR_NOERROR)
    {
        printf("Erreur lors de l'ouverture du périphérique. Erreur : %d\n", statusPeriphOpen);
        return 1;
    }

    bufferDescriptor.lpData = (LPSTR)bufferSonBrut;
    bufferDescriptor.dwBufferLength = TAILLE_BUFFER;
    bufferDescriptor.dwBytesRecorded = 0;
    bufferDescriptor.dwUser = 0;
    bufferDescriptor.dwFlags = 0;
    bufferDescriptor.dwLoops = 0;

    waveInPrepareHeader(handlePeriphAudio, &bufferDescriptor, sizeof(WAVEHDR));
    waveInAddBuffer(handlePeriphAudio, &bufferDescriptor, sizeof(WAVEHDR));

    waveInStart(handlePeriphAudio);

    while (!(bufferDescriptor.dwFlags & WHDR_DONE))
    {
        Sleep(10);
    }

    printf("Enregistrement terminé !\n");

    waveInStop(handlePeriphAudio);
    waveInUnprepareHeader(handlePeriphAudio, &bufferDescriptor, sizeof(WAVEHDR));
    statusPeriphClose = waveInClose(handlePeriphAudio);

    if (statusPeriphClose != MMSYSERR_NOERROR)
    {
        printf("Erreur lors de la fermeture du périphérique. Erreur : %d\n", statusPeriphClose);
        return 2;
    }

    return 0;
}

int main(void)
{

    /* changement de l'encodage pour l'affichage de la console */
    UINT oldCP = GetConsoleOutputCP();
    if (oldCP != 65001) {
        SetConsoleOutputCP(65001);
    }

    short bufferSonBrut[TAILLE_BUFFER];

    capture_audio(bufferSonBrut);

    enregistrement_fichier(bufferSonBrut);

    printf("Échantillons sauvegardés dans %s\n", FICHIER_TEST_ENREGISTREMENT);

    return 0;
}
