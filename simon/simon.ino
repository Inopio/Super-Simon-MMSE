#include <LiquidCrystal.h>
#include <Servo.h>

//temps
const unsigned long eventInterval = 10000;
unsigned long previousTime = 0;
unsigned long currentTime = millis();

//servomoteur
Servo myservo;
const int servo = 8;

//sequence
//////////////////////
const int length = 10;

//1 = ultrason, 2 = interrupteur, 3 = bouton poussoir, 4 = capteur de lumière
int player[] = {1,2,3,4};

//positions sur le demi cadran
int pos[] = {22,67,112,157};

//liste des directions
long dir[length];

//ordre des joueurs correspondants
long order[length];

int streak,ran,currpos,wait,action;
int previous = -1;
bool lost = false;
bool played = true;
bool closed = false;
bool pressed = false;
//////////////////////

// initialisation, on définit les ports pour RS, E et D4 à D7
const int RS=12; 
const int E=11;

const int D4=4; 
const int D5=5; 
const int D6=6; 
const int D7=7;

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

//ultrason
const int trigPin = 2;
const int echoPin = 3;


//interrupteur
const int interrupt = 9;

//bouton
int buttonState;
const int bouton = 10;

//lumière
int photocellPin = 0;
int photocellReading;

void setup() {
  Serial.begin(9600);
  //servo
  myservo.attach(servo);// attache le servomoteur au pin spécifié 
  pinMode(9, INPUT_PULLUP); //pour éviter de passer successivement à tous les états
   
  //LCD
  lcd.begin(16, 2);
  lcd.print("Start");
    
  lcd.setCursor(0, 1);// pour afficher sur la deuxième ligne
  lcd.print("Game");
  delay(2000); //pour avoir le temps de voir le message s'afficher

  //ultrason
  pinMode(trigPin,OUTPUT);
  digitalWrite(trigPin,LOW);
  pinMode(echoPin,INPUT);
  
  //interrupteur
  pinMode(interrupt, INPUT);
   
  //bouton poussoir:
  buttonState = LOW;
  pinMode(bouton, INPUT_PULLUP);
  
  //capteur ultrason
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW); 
  pinMode(echoPin, INPUT);
  

  //sequence
  //on génère une suite aléatoire de mouvements
  streak = 0;
  randomSeed(analogRead(0));
  for (int i = 0; i < length; i+=1){
    ran = random(4);
    //on s'assure de ne pas avoir deux fois de suite la même action
    while(ran == previous){
      ran = random(4);
    }
    order[i] = player[ran];
    dir[i] = pos[ran];
    previous = ran;
  }

}
  

void loop(){
  if(lost == false){
    Serial.println("Pas perdu");
  }
  else{
    Serial.println("Perdu");
  }

  //Servo
  //Si on n'a pas perdu ou fini la séquence complète et que le tour précédent est terminé
  if(!lost && streak <= length && played){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Current streak");
  lcd.setCursor(0,1);
  lcd.print(streak);
  
  //on pointe les différentes actions à effectuer pendant le tour
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
    //Serial.print(order[i]);
    //Serial.print('\n');
    delay(500);
  }
  //streak++;
  played = false;
  pressed = false;
  action = 0;
  
  //on initialise le compteur de temps
  previousTime = currentTime;
  currentTime = millis();
  }
  else if(lost){
    lcd.clear();
    lcd.print("Game lost");
    lcd.setCursor(0,1);
    lcd.print("Score ");
    lcd.print(streak);
    //Serial.println(lost);
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
  //Serial.print("distance = ");
  //Serial.println(distance);
  if(distance < 5 && !played){ //action
    if (order[action] == 1){
      if(action == streak){
        streak ++;
        //Serial.println("Performed :");
        //Serial.println(0);
        played = true;
        delay(500);
      }
      else{
        action ++;
        //Serial.println("Performed :");
        //Serial.println(0);
        delay(500);
        lcd.clear();
        lcd.print("Last action :");
        lcd.setCursor(0,1);
        lcd.print("Ultrasound");
      }
      previousTime = currentTime;
      currentTime = millis();
    }
    else{
      lost = true;
      //Serial.println("lost ultrason");
    }
  }
  
  //fin ultrason 
  
  //interrupteur
  digitalWrite(interrupt,HIGH);
  int state = digitalRead(interrupt);
  if( state == 0 && !closed && !played){
    //Serial.println("Close");
    closed = true;
    if (order[action] == 2){
      if(action == streak){
        streak ++;
        //Serial.println("Performed :");
        //Serial.println(1);
        played = true;
      }
      else{
        action ++;
        //Serial.println("Performed :");
        //Serial.println(1);
        lcd.clear();
        lcd.print("Last action :");
        lcd.setCursor(0,1);
        lcd.print("Switch");
      }
      previousTime = currentTime;
      currentTime = millis();
    }
    else{
      lost = true;
      //Serial.println("lost interrupteur");
    }
  }
  else if (state != 0){
    //Serial.println("Open");
    closed = false;
  }
    
  //fin interrupteur
  
  // bouton poussoir
  buttonState = digitalRead(bouton);
  
  if(buttonState == LOW && pressed) // le bouton a un niveau HAUT
    {
       pressed = false;
    }
    else if (!pressed && buttonState == HIGH) {
        if (order[action] == 3){
      if(action == streak){
        streak ++;
        //Serial.println("Performed :");
        //Serial.println(2);
        played = true;
      }
      else{
        action ++;
        //Serial.println("Performed :");
        //Serial.println(2);
        lcd.clear();
        lcd.print("Last action :");
        lcd.setCursor(0,1);
        lcd.print("Button");
      }
      previousTime = currentTime;
      currentTime = millis();
    }
        else{
          lost = true;
          //Serial.println("lost bouton");
        }
        pressed = true;
    }
  //fin bouton poussoir

  //capteur de lumière
  photocellReading = analogRead(photocellPin);   
  if (photocellReading < 400) {
    if (order[action] == 4){
      if(action == streak){
        streak ++;
        //Serial.println("Performed :");
        //Serial.println(3);
        played = true;
        delay(500);
      }
      else{
        action ++;
        //Serial.println("Performed :");
        //Serial.println(3);
        delay(500);
        lcd.clear();
        lcd.print("Last action :");
        lcd.setCursor(0,1);
        lcd.print("Light");
      }
      previousTime = currentTime;
      currentTime = millis();
    }
        else{
          lost = true;
          //Serial.println("lost light sensor");
        }
  }
  currentTime = millis();
  if(currentTime - previousTime >= eventInterval){
    //Serial.println("lost time");
    lost = true;
  }
}
