const int inputPin = A0;
const int inputWindow = 100;
const int relay = 7;

unsigned int inputSample;
int Led_toggle = 0;
int clap = 0;
unsigned long p_millis = 0;
unsigned long c_millis = 0;

void setup() 
{
  pinMode(inputPin, INPUT);
  pinMode(relay,OUTPUT);
  digitalWrite(relay,LOW);
  Serial.begin(9600);
}

void loop() 
{
  c_millis = millis();
  
  if(c_millis- p_millis > 100)
  {
    p_millis = c_millis;
    unsigned int inputMax = 0;
    unsigned int inputMin = 1024;

    for (unsigned int i = 0; i < inputWindow; i++) 
    {
      inputSample = analogRead(inputPin);
      inputMin = min(inputMin, inputSample);
      inputMax = max(inputMax, inputSample);
    }

    Serial.print("Min: ");
    Serial.print(inputMin);
    Serial.print("  Max: ");
    Serial.print(inputMax);
    Serial.print("  Diff: ");
    Serial.print(inputMax - inputMin);
    Serial.println();

    if(inputMax - inputMin > 150)
    {
      clap++;
    }

    if(clap == 2)
    {
      clap = 0;
      if(Led_toggle == 0)
      {
        Led_toggle = 1;
        digitalWrite(relay,HIGH);
      }
      else
      {
        Led_toggle = 0;
        digitalWrite(relay,LOW);
      }
    }
  }
}
