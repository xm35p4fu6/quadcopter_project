/*Server*/
void setup(){
 //Serial.begin(9600);
 //Serial1.begin(9600);
 while(!Serial1){ };
 Serial.println("PORT= ");
 string IN="AT+Server=1,";
 while(1){
 if(Serial.available()>0){
     IN=Serial.read();
     IN+=IN;
     Serial.read();
     break;
   }
 }
 Serial1.println(IN);
 while(1){
   if(Serial1.available()>0){
     char I=Serial1.read();
     Serial.print(I);
   }
 }
}

void loop(){

}
