#include <LiquidCrystal.h>
#include <Servo.h>

boolean correctAction;

//servomoteur
Servo myservo;
const int servo = 8;

//sequence
const int length = 10;
int player[] = {0,1,2,3};
int pos[] = {22,67,112,157};
long dir[length];
long order[length];
int streak,ran,currpos,wait;
bool lost = false;

// initialisation, on définit les ports pour RS, E et D4 à D7
LiquidCrystal lcd(12, 11, 4, 5, 6, 7);

//ultrason
const int trigPin = 2;
const int echoPin = 3;


//interrupteur
const int interrupt = 9;

//bouton
int buttonState;
const int bouton = 10;

void setup() {
  Serial.begin(9600);

  correctAction = false; //est à vrai quand la bonne action est effectuée
  //servo
  myservo.attach(servo);// attache le servomoteur au pin spécifié 
  pinMode(9, INPUT_PULLUP); //pour éviter de passer successivement à tous les états
   
  //LCD
  lcd.begin(16, 2);
  lcd.print("Start");
    
  lcd.setCursor(0, 1);// pour afficher sur la deuxième ligne
  lcd.print("Game");
  delay(2000); //pour avoir le temps de voir le message s'afficher
  
  //interrupteur
   pinMode(interrupt, INPUT);
   
  //bouton poussoir:
  buttonState = LOW;
  pinMode(bouton, INPUT);

  //sequence
  streak = 0;
  randomSeed(analogRead(0));
  for (int i = 0; i < length; i+=1){
    ran = random(4);
    order[i] = ran;
    dir[i] = pos[ran];
  }

}
  

void loop(){

  //Servo
  if(!lost && streak < length){
  for (int i = 0; i < streak+1; i+=1){
    if (currpos == dir[i]){
      wait = 10;
    }else{
      wait = 10/abs(currpos - dir[i]);
    }
    if(currpos < dir[i]){
      for (int j = currpos; j <= dir[i]; j += 1) {
        myservo.write(j);
        delay(wait);
      }
    }
    else{
      for (int j = currpos; j >= dir[i]; j -= 1) {
        myservo.write(j);
        delay(wait);
      }
    }
    currpos = dir[i];
    Serial.print(currpos);
    Serial.print('\n');
    delay(500);
  }
  streak++;
  }
  //fin servo
  
  // Ultrason
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long measure = pulseIn(echoPin, HIGH);
   
  //0.0240 correspond à la vitesse du son dans l'air, on divise par 2 pour le temps d'aller-retour
  float distance = measure*0.0340 / 2.0  ;
  
  //on affiche la distance
  Serial.print("distance = ");
  Serial.println(distance);
  if(distance < 5){ //action
     }
  //fin ultrason 
  
  //interrupteur
  digitalWrite(interrupt,HIGH);
  int state = digitalRead(interrupt);
  if( state == 0)
    Serial.println("Close");
  else
    Serial.println("Open");
    
  //fin interrupteur
  
  // bouton poussoir
  buttonState = digitalRead(bouton);
  
  if(buttonState == HIGH) // le bouton a un niveau HAUT
    {
       //action
    }
    else 
    {
        //action
    }
}
