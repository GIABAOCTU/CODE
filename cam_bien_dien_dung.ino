void setup() 
{
  Serial.begin(9600);
}
 
void loop() 
{
  int value = analogRead(A0);    
  int percent = map(value, 1023,0 , 0, 100);
  Serial.print(percent);
  Serial.println('%');
}
