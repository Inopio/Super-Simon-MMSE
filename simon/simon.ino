#include <LiquidCrystal.h>
#include <Servo.h>

boolean correctAction;

//servomoteur
Servo myservo;
const int servo = 8;

//sequence
const int length = 10;
//0 = ultrason, 1 = interrupteur, 2 = bouton poussoir, 3 = 
int player[] = {0,1,2,3};
int pos[] = {22,67,112,157};
long dir[length];
long order[length];
int streak,ran,currpos,wait;
int previous = -1;
bool lost = false;
bool played = true;
bool closed = false;
bool pressed = false;

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
  
  //capteur ultrason
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW); 
  pinMode(echoPin, INPUT);
  

  //sequence
  streak = 0;
  randomSeed(analogRead(0));
  for (int i = 0; i < length; i+=1){
    ran = random(1,3);
    while(ran == previous){
      ran = random(1,3);
    }
    order[i] = ran;
    dir[i] = pos[ran];
    previous = ran;
  }

}
  

void loop(){

  //Servo
  if(!lost && streak < length && played){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Current streak");
  lcd.setCursor(0,1);
  lcd.print(streak);
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
  //streak++;
  played = false;
  }
  else if(lost){
    lcd.clear();
    lcd.print("Game lost");
    lcd.setCursor(0,1);
    lcd.print("Score ");
    lcd.print(streak);
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
//  if(distance < 5 && !played){ //action
//    if (order[streak] == 0){
//      streak ++;
//    }
//    else{
//      lost = true;
//    }
//    played = true;
//  }
  
  //fin ultrason 
  
  //interrupteur
  digitalWrite(interrupt,HIGH);
  int state = digitalRead(interrupt);
  if( state == 0 && !closed && !played){
    //Serial.println("Close");
    closed = true;
    if (order[streak] == 1){
      streak ++;
    }
    else{
      lost = true;
    }
    played = true;
  }
  else if (state != 0){
    //Serial.println("Open");
    closed = false;
  }
    
  //fin interrupteur
  
  // bouton poussoir
  buttonState = digitalRead(bouton);
  
  if(buttonState == HIGH && pressed) // le bouton a un niveau HAUT
    {
       pressed = false;
    }
    else if (!pressed)
    {
        if (order[streak] == 2){
          streak ++;  
        }
        else{
          lost = true;
        }
        pressed = true;
        played = true;
    }
}