
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
//int delaiBtRapide = 500;
//unsigned long millisAppuisBtDroite;
//unsigned long millisAppuisBtGauche;

bool etatDroite = 0;
bool etatGauche = 0;
bool etatStop = 0;
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
  digitalWrite(ledRouge, HIGH);
  digitalWrite(ledVerte, LOW);
}

void loop() {
  
  if (!digitalRead(btDroite)) {
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
  if (!digitalRead(btGauche)) {
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
    pause = pause + 1;
    delay(10);
    if (pause > 100) {
      digitalWrite(slp, LOW);
      digitalWrite(ledRouge, HIGH);
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
    digitalWrite(pas, HIGH);
    (!digitalRead(btGauche) || !digitalRead(btDroite)) ? delayMicroseconds(rapide) : delayMicroseconds(normale);
    //delayMicroseconds(rapide);
    digitalWrite(pas, LOW);
    (!digitalRead(btGauche) || !digitalRead(btDroite)) ? delayMicroseconds(rapide) : delayMicroseconds(normale);;
    //delayMicroseconds(rapide);
  }
}
