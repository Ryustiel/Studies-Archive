#ifndef TP3_H_INCLUDED
#define TP3_H_INCLUDED

typedef struct Consultation {
    char* date;
    char* motif;
    int niveauUrg;
    struct Consultation* suivant;
} Consultation;


typedef struct Patient {
    char* nom;
    char* prenom;
    struct Consultation* ListeConsult;
    int nbrconsult;
    struct Patient* fils_gauche;
    struct Patient* fils_droit;
} Patient;


typedef Patient* Parbre;

Patient* CreerPatient(char nm[30], char pr[30]);
Consultation* CreerConsult(char date[10], char motif[120], int nivu);
void inserer_patient(Parbre* abr, char nm[30], char pr[30]);
int datecmp(char date1[10], char date2[10]);
void ajouter_consultation(Parbre* abr, char nm[30], char date[10], char motif[120], int nivu);
Patient* rechercher_patient(Parbre* abr, char nm[30]);
void afficher_fiche(Parbre* abr, char nm[30]);
void afficher_patients(Parbre* abr);
void free_patient(Patient* p);
void supprimer_patient(Parbre* abr, char nm[30]);
void free_all_patients(Patient* p);
void supprimer_consultations(Patient* p);
void maj_consultations(Consultation* reference, Patient* patient_modifier);
void maj(Parbre* abr, Parbre* abr2);
void interface();

#endif // TP3_H_INCLUDED
