#include <AccelStepper.h> //librairie de pilotage de moteurs pas à pas

// création des objets AccelStepper pour piloter les moteurs pas à pas
// axe X moteur 1  pin 2 = step, pin 5 = direction
// axe X moteur 2  step dupliqué physiquement sur la carte de commande, pin 13 = direction
// axe Y moteur 3 pin 3 = step, pin 6 = direction
// axe Z moteur 4 pin 4 = step, pin 7 = direction
AccelStepper xaxis(AccelStepper::DRIVER, 2, 5); 
AccelStepper yaxis(AccelStepper::DRIVER, 3, 6); 
AccelStepper zaxis(AccelStepper::DRIVER, 4, 7);
#define PIN_SENS_MOTEUR2 9
#define PIN_ENABLE 8

#include <hx711.h>  //librairie de la carte de mesure en pont de wheatstone Hx711 attention librairie perso base sur première librairie
//attention le signal CLK pour le HX711 ne fonctionne que sur les pin analogique ??? d'où A0 à A3

// création des objets Hx711 pour mesurer le poids
Hx711 capteur1(10, A0); // Hx711.DOUT - pin #10  Hx711.SCK - pin #A0
Hx711 capteur2(11, A1);
Hx711 capteur3(12, A2);
Hx711 capteur4(13, A3);

#define NB_MESURES 30 //nombre de mesures de poids pour réaliser la moyenne 

float capteur1_valeur=0; //valeur du capteur 1
float capteur1_offset=0; //valeur à vide du capteur1
float capteur1_fact=0; //facteur d'echelle du capteur1
float capteur1_tare_connue=(1.43+20)/4; //poids de la tare du capteur 1 (newton) plateau  avec masse de 2kg centrée
float capteur1_x=-60; //position du capteur 1 en mm ATTENTION si c'est la pièce qui se déplace pas le palpeur la position du capteur est inversé
float capteur1_y=-87.5; //position du capteur 1 en mm

float capteur2_valeur=0; //valeur du capteur 2
float capteur2_offset=0; //valeur à vide du capteur2
float capteur2_fact=0; //facteur d'echelle du capteur2
float capteur2_tare_connue=(1.43+20)/4; //poids de la tare du capteur 2 (newton) plateau  avec masse de 2kg centrée
float capteur2_x=60; //position du capteur 2 en mm ATTENTION si c'est la pièce qui se déplace pas le palpeur la position du capteur est inversé
float capteur2_y=-87.5; //position du capteur 2 en mm

float capteur3_valeur=0; //valeur du capteur 3
float capteur3_offset=0; //valeur à vide du capteur3
float capteur3_fact=0; //facteur d'echelle du capteur3
float capteur3_tare_connue=(1.43+20)/4; //poids de la tare du capteur 3 (newton) plateau  avec masse de 2kg centrée
float capteur3_x=60; //position du capteur 3 en mm ATTENTION si c'est la pièce qui se déplace pas le palpeur la position du capteur est inversé
float capteur3_y=87.5; //position du capteur 3 en mm

float capteur4_valeur=0; //valeur du capteur 4
float capteur4_offset=0; //valeur à vide du capteur4
float capteur4_fact=0; //facteur d'echelle du capteur4
float capteur4_tare_connue=(1.43+20)/4; //poids de la tare du capteur 3 (newton) plateau  avec masse de 2kg centrée
float capteur4_x=-60; //position du capteur 4 en mm ATTENTION si c'est la pièce qui se déplace pas le palpeur la position du capteur est inversé
float capteur4_y=87.5; //position du capteur 4 en mm

float mesure_poids=0; //somme ds poids de chaque capteur (N)
float plateau_poids=0; //poids du plateau support du système (N)
float piece_poids=0; //poids de la pièce = mesure_poids-plateau_poids(N)

//mouvement type compatible avec la librairie AccelStepper
#define X_VITESSE_MAX 500 //pas par seconde
#define X_ACCELERATION_MAX 200 //pas par seconde² ATTENTION à calculer en fonction de la masse, du couple moteur et de la transmission
#define X_MOTEUR_PAS 200 //nombre de pas/tour du moteur de l'axe x TIENT COMPTE du réglage pas demi pas ...
#define X_COURROIE_PAS 2 //pas de la courroie de l'axe x
#define X_POULIE_Z 20 //nombre de dent de de l'axe x
#define X_COURSE 150 //course suivant x en mm
long x_position_pas=0;//position sur l'axe x en pas
float x_facteur=1; //facteur de conversion mm/pas
float x_position_mm=0; //position sur l'axe x en mm
long x_min=0; //limite min axe x en pas divisé par 2 après réglage du zéro défini dans le setup
long x_max=0; //limite max axe x en pas divisé par 2 après réglage du zéro défini dans le setup

#define Y_VITESSE_MAX 500 //pas par seconde
#define Y_ACCELERATION_MAX 200 //pas par seconde² ATTENTION à calculer en fonction de la masse, du couple moteur et de la transmission
#define Y_MOTEUR_PAS 200 //nombre de pas/tour du moteur de l'axe y TIENT COMPTE du réglage pas demi pas ...
#define Y_COURROIE_PAS 2 //pas de la courroie de l'axe y
#define Y_POULIE_Z 20 //nombre de dent de de l'axe y
#define Y_COURSE 200 //course suivant y en mm
long y_position_pas=0;//position sur l'axe y en pas
float y_facteur=1; //facteur de conversion mm/pas
float y_position_mm=0; //position sur l'axe y en mm
long y_min=0; //limite min axe y en pas divisé par 2 après réglage du zéro défini dans le setup
long y_max=0; //limite max axe y en pas divisé par 2 après réglage du zéro défini dans le setup

#define Z_VITESSE_MAX 200 //pas par seconde
#define Z_ACCELERATION_MAX 100 //pas par seconde² ATTENTION à calculer en fonction de la masse, du couple moteur et de la transmission
#define Z_MOTEUR_PAS 200 //nombre de pas/tour du moteur de l'axe z TIENT COMPTE du réglage pas demi pas ...
#define Z_CAME_COURSE 5 //déplacement créé par la came pour un demi tour en mm
#define Z_COURSE 100 //course suivant z en pas égale au nombre de pas du moteur pour un demi tour
long z_position_pas=0;//position sur l'axe z en pas
float z_facteur=1; //facteur de conversion mm/pas
float z_position_mm=0; //position sur l'axe z en mm
long z_min=-Z_COURSE; //limite min axe z en pas 0 après réglage du zéro
long z_max=Z_COURSE; //limite max axe z en pas divisé par 2 après réglage du zéro

byte data;

byte mode=0;
byte bouton=0;
short increment=1;

float piece_xg_mm=0;
float piece_yg_mm=0;
float plateau_xg_mm=0;
float plateau_yg_mm=0;
long piece_xg_pas=0;
long piece_yg_pas=0;

float seuil=0.2; //seuil pour évaluer un capteur à zéro (0,2N soit 20g)
float precision_position_cdg=0.5; //précision désirée pour la mesure du CdG

void setup() 
 {
  xaxis.setMaxSpeed(X_VITESSE_MAX);
  yaxis.setMaxSpeed(Y_VITESSE_MAX);
  zaxis.setMaxSpeed(Z_VITESSE_MAX);
  xaxis.setAcceleration(X_ACCELERATION_MAX);
  yaxis.setAcceleration(Y_ACCELERATION_MAX);
  zaxis.setAcceleration(Z_ACCELERATION_MAX);
  pinMode(PIN_SENS_MOTEUR2, OUTPUT); // sortie digitale contrôle de direction du moteur 2 de l'axe X (le nombre de pas est dupliqué du moteur 1 sur la carte)
  digitalWrite(PIN_SENS_MOTEUR2,0);
   pinMode(PIN_ENABLE, OUTPUT); // sortie digitale contrôle de direction du moteur 2 de l'axe X (le nombre de pas est dupliqué du moteur 1 sur la carte)
  digitalWrite(PIN_ENABLE,0);
  x_facteur=float(X_COURROIE_PAS)*float(X_POULIE_Z)/float(X_MOTEUR_PAS); //facteur de conversion mm/pas
  y_facteur=float(Y_COURROIE_PAS)*float(Y_POULIE_Z)/float(Y_MOTEUR_PAS); //facteur de conversion mm/pas
  z_facteur=float(Z_CAME_COURSE)/float(Z_COURSE); //facteur de conversion mm/pas
  x_min=-X_COURSE/x_facteur;
  x_max=X_COURSE/x_facteur;
  y_min=-Y_COURSE/y_facteur;
  y_max=Y_COURSE/y_facteur;
  
  Serial.begin(9600);
 }
 
void loop() 
{
 if (Serial.available()) 
   {
    data=Serial.read();
    switch(data)
     {
       case 1: // mode déplacements calibrage origine
         mode=1;
      break;

      case 2: // mode mesure
         mode=2;
       break;
      
      case 11: // X+ ou tare à 0
         if (mode==1) // déplacement suivant X+ de l'incrément
           {
            deplacement(x_position_pas+increment,y_position_pas,z_position_pas);
           }
         if (mode==2) // tare 
           {
            capteur1_offset=capteur1.averageValue(NB_MESURES); //mesure et affecte l'offset
            capteur2_offset=capteur2.averageValue(NB_MESURES);
            capteur3_offset=capteur3.averageValue(NB_MESURES);
            capteur4_offset=capteur4.averageValue(NB_MESURES);
            
            mesurer_le_poids(); //mesure du poids et envoie pour affichage (permet de vérifier)
           } 
      break; 
     
      case 21: // X- ou tare connue
          if (mode==1) // déplacement suivant X- de l'incrément
           {
            deplacement(x_position_pas-increment,y_position_pas,z_position_pas);
           }
         if (mode==2)  //mesure du poids avec tare connue pour déterminer le facteur d'écchelle
           {
            capteur1_fact=(capteur1.averageValue(NB_MESURES)-capteur1_offset)/(capteur1_tare_connue+plateau_poids); //calcule l'echelle
            capteur2_fact=(capteur2.averageValue(NB_MESURES)-capteur2_offset)/(capteur2_tare_connue+plateau_poids); //calcule l'echelle
            capteur3_fact=(capteur3.averageValue(NB_MESURES)-capteur3_offset)/(capteur3_tare_connue+plateau_poids); //calcule l'echelle
            capteur4_fact=(capteur4.averageValue(NB_MESURES)-capteur4_offset)/(capteur4_tare_connue+plateau_poids); //calcule l'echelle
            
            mesurer_le_poids(); //mesure du poids et envoie pour affichage (permet de vérifier)
           } 
      break; 

      case 31: // sauv X0 ou mesure un poids quelconque
          if (mode==1)
           {
            xaxis.setCurrentPosition(0); //initialise la position de x
            x_position_pas=0; //initialise la position de x
            x_min=x_min/2;
            x_max=x_max/2;
            x_position_mm=x_position_pas*x_facteur;
            envoie_donnees(1,x_position_mm);//envoie la nouvelle position en x pour affichage case 1
           }
          if (mode==2)
           {
            piece_poids=mesurer_le_poids()-plateau_poids; //mesure du poids
            envoie_donnees(10,piece_poids);//envoie pour affichage
           } 
      break; 
        
      case 12: // Y+ ou mesure le poids du plateau à vide
         if (mode==1) // déplacement suivant y+ de l'incrément
           {
            deplacement(x_position_pas,y_position_pas+increment,z_position_pas);
           }
         if (mode==2)
           {
            plateau_poids= mesurer_le_poids(); //mesure du poids
            envoie_donnees(10,plateau_poids);//envoie le poids du plateau pour affichage case 10
           }
      break; 

       case 22: // Y- ou mesure CdG plateau
          if (mode==1)// déplacement suivant Y- de l'incrément
           {
            deplacement(x_position_pas,y_position_pas-increment,z_position_pas);
           }
          if (mode==2)
           {
            mesure_cdg();
           }
      break; 

      case 32: // sauv Y0 ou retour à l'origine
         if (mode==1)
           {
            yaxis.setCurrentPosition(0);
            y_position_pas=0;
            y_min=y_min/2;
            y_max=y_max/2;
            y_position_mm=y_position_pas*y_facteur;
            envoie_donnees(2,y_position_mm);//envoie la nouvelle position en y pour affichage en case 2
           }
         if (mode==2)
           {
            deplacement(x_position_pas,y_position_pas,z_min); // baisse le palpeur
            deplacement(0,0,z_min); //déplace le palpeur à l'origine
           }
      break;
      
      case 13: // Z plus ou lance la mesure automatique
         if (mode==1)// déplacement suivant Z+ de l'incrément
           {
            deplacement(x_position_pas,y_position_pas,z_position_pas+increment);
           }
         if (mode==2)
           {
            mesure_cdg();
           }
      break; 
      
      case 23: // Z-
          if (mode==1)// déplacement suivant Z- de l'incrément
           {
            deplacement(x_position_pas,y_position_pas,z_position_pas-increment);
           }
      break; 
      
      case 33: // sauv position haute Z
         zaxis.setCurrentPosition(Z_COURSE);
         z_position_pas=Z_COURSE;
         z_min=0;
         z_max=Z_COURSE;
         z_position_mm=z_position_pas*z_facteur;
         deplacement(x_position_pas,y_position_pas,0);
         envoie_donnees(3,z_position_mm);//envoie la nouvelle position en z pour affichage en case 3
      break;

      case 41: // incrément=1
         increment=1;
      break;

      case 42: // incrément=10
         increment=10;
      break;

      case 43: // incrément=100
         increment=100;
      break;
      
      case 44: // incrément=1000
         increment=1000;
      break;
     }
    while (Serial.available()) {data=Serial.read();} //vide le tampon de la communication série
    envoie_donnees(255,0); //initialise les couleurs du clavier
   } // fin de la boucle de traitement de la commande envoyée sur le port série
} //fin de la boucle principale loop


void envoie_donnees(byte grandeur,float valeur)
  {
   byte byte1;
   byte byte2;
   valeur=valeur*10; //x10 pour avaoir une précision de 0,1
   valeur=valeur+32768; //prise en compte des valeurs négatives
   if (valeur<0)
     {
      valeur=0;
     }
   if (valeur>65535)
     {
      valeur=65535;
     }
   byte2 = byte(valeur/256);
   byte1 = byte(valeur-256*byte2);
   Serial.write(grandeur);
   Serial.write(byte1);
   Serial.write(byte2);
   delay(200);
  }
  
float mesurer_le_poids()
  {
   capteur1_valeur=(capteur1.averageValue(NB_MESURES)-capteur1_offset)/capteur1_fact;
   envoie_donnees(6,capteur1_valeur);
   capteur2_valeur=(capteur2.averageValue(NB_MESURES)-capteur2_offset)/capteur2_fact;
   envoie_donnees(7,capteur2_valeur);
   capteur3_valeur=(capteur3.averageValue(NB_MESURES)-capteur3_offset)/capteur3_fact;
   envoie_donnees(8,capteur3_valeur);
   capteur4_valeur=(capteur4.averageValue(NB_MESURES)-capteur4_offset)/capteur4_fact; 
   envoie_donnees(9,capteur4_valeur);
   mesure_poids=capteur1_valeur+capteur2_valeur+capteur3_valeur+capteur4_valeur;
   return(mesure_poids); //valeur brut plateau + pièce
  }

void calcule_cdg() //procedure de calcul du centre de gravité en utilisant les mesures des capteurs
 {
  piece_poids=mesurer_le_poids()-plateau_poids; //mesure du poids
  envoie_donnees(10,piece_poids);//envoie pour affichage
  piece_xg_mm=((capteur1_x*capteur1_valeur+capteur2_x*capteur2_valeur+capteur3_x*capteur3_valeur+capteur4_x*capteur4_valeur)-(plateau_xg_mm*plateau_poids))/piece_poids;
  piece_yg_mm=((capteur1_y*capteur1_valeur+capteur2_y*capteur2_valeur+capteur3_y*capteur3_valeur+capteur4_y*capteur4_valeur)-(plateau_yg_mm*plateau_poids))/piece_poids;
  piece_xg_pas=long(piece_xg_mm/x_facteur);
  piece_yg_pas=long(piece_yg_mm/y_facteur);
  envoie_donnees(4,piece_xg_mm);
  envoie_donnees(5,piece_yg_mm);
 }

void mesure_cdg() //procedure de recherche du centre de gravité
 {
  bool test=false;
  float simplex_pas=0; //mm déplacement pour la recherche
  float erreur=1;
  calcule_cdg();
  do
   {
    test=false;
    deplacement(piece_xg_pas,piece_yg_pas,0); // déplace le palpeur au CdG supposé ATTENTION en x c'est la pièce qui se déplace pas le palpeur donc - !!!!
    zaxis.runToNewPosition(z_max); //soulève la pièce
    mesurer_le_poids();  //mesure le poids sur les capteurs s'ils sont tous les 4 à zéro (seuil) le palpeur est au CdG
    zaxis.runToNewPosition(z_min); //baisse la pièce avant un nouveau déplacement
  erreur=0;
  if (capteur1_valeur>seuil)
      {
       erreur+=capteur1_valeur;
      }
    if (capteur2_valeur>seuil) 
      {
       erreur+=capteur2_valeur;
      }
    if (capteur3_valeur>seuil)
      {
       erreur+=capteur3_valeur;
      }
    if (capteur4_valeur>seuil)
      {
       erreur+=capteur4_valeur;
      }
    simplex_pas=erreur/seuil*precision_position_cdg;
    if (simplex_pas>5) {simplex_pas=5;}
    if (capteur1_valeur>seuil)
      {
       piece_xg_mm+=simplex_pas*abs(capteur1_x)/capteur1_x; 
       piece_yg_mm+=simplex_pas*abs(capteur1_y)/capteur1_y;
       test=true;
      }
    if (capteur2_valeur>seuil) 
      {
       piece_xg_mm+=simplex_pas*abs(capteur2_x)/capteur2_x;
       piece_yg_mm+=simplex_pas*abs(capteur2_y)/capteur2_y;
       test=true;
      }
    if (capteur3_valeur>seuil)
      {
       piece_xg_mm+=simplex_pas*abs(capteur3_x)/capteur3_x;
       piece_yg_mm+=simplex_pas*abs(capteur3_y)/capteur3_y;
       test=true;
      }
    if (capteur4_valeur>seuil)
      {
       piece_xg_mm+=simplex_pas*abs(capteur4_x)/capteur4_x;
       piece_yg_mm+=simplex_pas*abs(capteur4_y)/capteur4_y;
       test=true;
      }
    piece_xg_pas=long(piece_xg_mm/x_facteur);
    piece_yg_pas=long(piece_yg_mm/y_facteur);
    envoie_donnees(4,piece_xg_mm);
    envoie_donnees(5,piece_yg_mm);
    if (Serial.available()) 
       {
        data=Serial.read();
        if ((data==23)||(data=33)) 
          {
           test=false;
          } //arrête la recherche si appui sur le bouton STOP
       }
   }
  while (test);
  deplacement(x_position_pas,y_position_pas,z_min); // baisse le palpeur
  deplacement(0,0,z_min); //déplace le palpeur à l'origine
       
 } // fin de la procedure de recherche

void deplacement(long x,long y,long z) //procédure de déplacement sur une position ABSOLUE en pas
  {
   if ((x-x_position_pas)>0)
      {
       digitalWrite(PIN_SENS_MOTEUR2,0); //le moteur 2 de l'axe X tourne en sens inverse du moteur 1
      }
   else
      {
       digitalWrite(PIN_SENS_MOTEUR2,1); //le moteur 2 de l'axe X tourne en sens inverse du moteur 1
      }
   if (((x-x_position_pas)!=0)&&(x<x_max)&&(x>x_min))
      {
       xaxis.runToNewPosition(x);
       x_position_pas=x;
       x_position_mm=x_position_pas*x_facteur;
       envoie_donnees(1,x_position_mm);//envoie la nouvelle position en x pour affichage case 1
      }
   if (((y-y_position_pas)!=0)&&(y<y_max)&&(y>y_min))
      {
       yaxis.runToNewPosition(y);
       y_position_pas=y;
       y_position_mm=y_position_pas*y_facteur;
       envoie_donnees(2,y_position_mm); //envoie la nouvelle position en y pour affichage case 2
      }
   if ((z-z_position_pas)!=0)
      {
       zaxis.runToNewPosition(z);
       z_position_pas=z;
       z_position_mm=z_position_pas*z_facteur;
       envoie_donnees(3,z_position_mm);//envoie la nouvelle position en z pour affichage case 3
      }         
  } //fin de la procédure de déplacement

