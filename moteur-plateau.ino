
#define btGauche 2
#define btStop 3
#define btDroite 4
#define dir 6
#define pas 5
#define slp 7
#define ledRouge 8
#define ledVerte 9

unsigned long nbTourMax = 50;
unsigned long  nbPasMax = 1600 * nbTourMax;
unsigned long  nbPas = nbPasMax / 2;  // Record the number of steps we've taken
int vitNormale = 10; // ~tours par minutes
int vitRapide = 200;
int normale = 18750 / vitNormale;
int rapide = 18750 / vitRapide;
int vitesse = 0;
int delaiBtRapide = 500;
unsigned long millisBtDroite = 0;
unsigned long millisBtGauche = 0;
bool ancienEtatBtDroite = LOW;
bool ancienEtatBtGauche = LOW;

bool droite = LOW;
bool gauche = LOW;
bool etatBtDroite = LOW;
bool etatBtGauche = LOW;
bool etatDroite = LOW;
bool etatGauche = LOW;
bool etatStop = LOW;
//bool start = 0;
int pause = 0;

void setup() {
  pinMode(btDroite, INPUT_PULLUP);
  pinMode(btStop, INPUT_PULLUP);
  pinMode(btGauche, INPUT_PULLUP);
  pinMode(dir, OUTPUT);
  pinMode(pas, OUTPUT);
  pinMode(slp, OUTPUT);
  pinMode(ledRouge, OUTPUT);
  pinMode(ledVerte, OUTPUT);
  digitalWrite(pas, LOW);
  digitalWrite(slp, LOW); //déactive les sorties du easydiver
  digitalWrite(ledRouge, LOW);
  digitalWrite(ledVerte, LOW);
}

void loop() {
  droite = !digitalRead(btDroite);
  if (droite != ancienEtatBtDroite) {
    millisBtDroite = millis();
  }
  gauche = !digitalRead(btGauche);
  if (gauche != ancienEtatBtGauche) {
    millisBtGauche = millis();
  }
  if (droite) {
    etatDroite = 1;
    etatGauche = 0;
    etatStop = 0;
    //start = 1;
    pause = 0;
    digitalWrite(dir, HIGH);
    digitalWrite(slp, HIGH);
    digitalWrite(ledRouge, LOW);
    digitalWrite(ledVerte, HIGH);
  }
  if (gauche) {
    etatDroite = 0;
    etatGauche = 1;
    etatStop = 0;
    //start = 1;
    pause = 0;
    digitalWrite(dir, LOW);
    digitalWrite(slp, HIGH);
    digitalWrite(ledRouge, LOW);
    digitalWrite(ledVerte, HIGH);
  }
  if (!digitalRead(btStop)) {
    etatDroite = 0;
    etatGauche = 0;
    etatStop = 1;
    digitalWrite(ledVerte, LOW);
    digitalWrite(ledRouge, HIGH);
    pause = pause + 1;
    delay(10);
    if (pause > 100) {
      digitalWrite(slp, LOW);
      digitalWrite(ledRouge, LOW);
    }
  }
  if (etatDroite || etatGauche && !etatStop) {
    // Check to see if we are at the end of our move
    if (nbPas == nbPasMax || nbPas == 0)
    {
      // We are! Reverse direction (invert DIR signal)
      if (digitalRead(dir) == LOW)
      {
        digitalWrite(dir, HIGH);
      }
      else
      {
        digitalWrite(dir, LOW);
      }
      delay(200);
    }
    if (digitalRead(dir) == LOW) {
      nbPas = nbPas - 1;   // record this step
    }
    else
    {
      nbPas = nbPas + 1;
    }
    if (droite && (millis() - millisBtDroite > delaiBtRapide)) {
    vitesse = rapide;
    etatBtDroite = droite;
  } else if (gauche && (millis() - millisBtGauche > delaiBtRapide)) {
    vitesse = rapide;
    etatBtGauche = gauche;
  } else {
    vitesse = normale;
  }
  digitalWrite(pas, HIGH);
  delayMicroseconds(vitesse);
  digitalWrite(pas, LOW);
  delayMicroseconds(vitesse);
}
ancienEtatBtDroite = droite;
ancienEtatBtGauche = gauche;
}
