void setup(){
  Serial1.begin(9600);
  Serial.begin(9600);
}
void loop(){
  if(Serial.available()>0){
    char a =Serial.read();
    Serial1.print(a);
  }
  if(Serial1.available()>0){
    char a =Serial1.read();
    Serial.print(a);
  }
}
