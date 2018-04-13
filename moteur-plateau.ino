
#define btDroite 2
#define btStop 3
#define btGauche 4
#define dir 6
#define pas 5
#define slp 7

int nbTourMax = 2;
int nbPasMax = 1600 * nbTourMax;
int nbPas = 0;  // Record the number of steps we've taken
int vitNormale = 2; // tours par minutes
int vitRapide = 400;
unsigned int normale = 18750 / vitNormale;
unsigned int rapide = 18750 / vitRapide;

void setup() {   
  pinMode(btDroite, INPUT_PULLUP);
  pinMode(btStop, INPUT_PULLUP);
  pinMode(btGauche, INPUT_PULLUP);             
  pinMode(dir, OUTPUT);     
  pinMode(pas, OUTPUT);
  pinMode(slp, OUTPUT);
  digitalWrite(dir, LOW);
  digitalWrite(pas, LOW);
  digitalWrite(slp, HIGH);
  //digitalWrite(slp, LOW); //déactive les sorties du easydiver
}

void loop() {
  digitalWrite(pas, HIGH);
  delayMicroseconds(rapide);          
  digitalWrite(pas, LOW); 
  delayMicroseconds(rapide);
  nbPas = nbPas + 1;   // record this step
  
  // Check to see if we are at the end of our move
  if (nbPas == nbPasMax)
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
    // Reset our nbPas back to zero since we're
    // starting a new move
    nbPas = 0;
    // Now pause
    delay(100);
  }
}
