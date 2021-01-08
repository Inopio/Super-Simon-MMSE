#include <LiquidCrystal.h>
#include <Servo.h>

boolean correctAction;

//servomoteur
Servo myservo;
const int servo = 6;

// initialisation, on définit les ports pour RS, E et D4 à D7
LiquidCrystal lcd(12, 11, 4, 5, 6, 7);

//ultrason
const int trigPin = 2;
const int echoPin = 3;

//interrupteur
const int interrupt = 5;

//bouton
int buttonState;
const int bouton = 4;

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
}
  

void loop(){
  
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