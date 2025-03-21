#ifndef AUDIO_CAPTURE_H
#define AUDIO_CAPTURE_H

#define ENCHANTILLONAGE 44100
#define BITS_PAR_SAMPLE 16
#define TAILLE_BUFFER (ENCHANTILLONAGE * (BITS_PAR_SAMPLE / 8))
#define T_NORMAL_WORD 50

#define FICHIER_TEST_ENREGISTREMENT "./data/enchantillon"

typedef struct {
    int id;
    short valeur;
} POINT_GRAPH;

int enregistrement_fichier(short *buffer);
int capture_audio(short *bufferSonBrut);


#endif /*AUDIO_CAPTURE_H*/