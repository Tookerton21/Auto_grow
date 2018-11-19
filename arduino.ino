class Relay{
  private: 
    //var dec
    int ports[4] = {2, 4, 7, 8};
    
    public:
      int size_arr = 4;
      
      void change_state(int port, uint8_t state){
          digitalWrite(port, state);
           delay(1000);
      }

      void set_state(){
        for(int i=0; i<size_arr; ++i)
          pinMode(ports[i], OUTPUT);
        
      }
      
      int get_port(int i) { 
          return ports[i]; 
        }
      
};

Relay relay;

void setup() {
  // put your setup code here, to run once:
  relay.set_state();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() == 0);

  String val = Serial.readString(); //Variable to store sting message
  val.trim(); //Clean nl char()
  //Serial.println(val);
  //Serial.println(val.equals("true"));
  
  if(val.equals("true")){
    while (Serial.available() == 0);
    String val = Serial.readString();


 
    
    val.trim();
    
    int port;
    if(val.equals("0")){
      port = 0;
    }
    else  if(val.equals("1")){
      port = 1;
    }
     else if(val.equals("2")){
      port = 2;
    }
    else  if(val.equals("3")){
      port = 3;
    }
    else
      port = -1;

    while (Serial.available() == 0);
    String on_off = Serial.readString();
    on_off.trim();

    
    Serial.println(port);
    if(port != -1){
      if(on_off.equals("high")){
        relay.change_state(relay.get_port(port), HIGH);
      }
      else{
       relay.change_state(relay.get_port(port), LOW);
      }
    }
    
  }
   else
    Serial.println("Not Valid");

   //Serial.flush();

  //Serial.println(val);

}
