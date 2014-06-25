// pins
int sda = 13;
int scl = 12;

void setup() {
  pinMode(sda, OUTPUT);
  pinMode(scl, OUTPUT);
  Serial.begin(9600);
  Serial.println("\nI2C bitbang");
}

void loop() {
  byte n, error, cfgRD, cfgWR;
// LCD Display
  n = 0;
  cfgWR = 0xA0; //0xA0 backward for WRite
  cfgRD = 0xA1; //0xA0 + LSB = 1 for Read
  pinMode(sda,OUTPUT);
  I2C_start();
  I2C_out(cfgWR);
  I2C_out(0x00);
  I2C_out(0x00);
  I2C_out(0xBB);
  I2C_stop();
  delay(50);
  I2C_start();
  I2C_out(cfgWR);
  I2C_out(0x00);
  I2C_out(0x00);
  I2C_stop();
  I2C_start();
  I2C_out(cfgRD); //device ACK included, no additional clk required for read
  Serial.println(I2C_in());
  I2C_ACK(0);
  Serial.println(I2C_in());
  I2C_ACK(1);
  I2C_stop();
  delay(10000);
}

void I2C_ACK(unsigned char j) {
  pinMode(sda,OUTPUT);
  if ((j & 0x1) == 0x1) {
    digitalWrite(sda, HIGH);
  } else {
    digitalWrite(sda, LOW);
  }
  clkPulse();
  pinMode(sda,INPUT);
}

void I2C_out(unsigned char j) {
  Serial.print("I2C_out: ");
  Serial.print(j,HEX);
  Serial.print("\n");
  
  int n;
  unsigned char d;
  d = j;
  for(n=0; n<8; n++) {
    if((d & 0x80) == 0x80) {
      digitalWrite(sda,HIGH);
    } else {
      digitalWrite(sda,LOW);
    }
    d = (d << 1);
    digitalWrite(scl,LOW);
    digitalWrite(scl,HIGH);
    digitalWrite(scl,LOW);
  }
  pinMode(sda,INPUT);
  Serial.print(digitalRead(sda), HEX);
  Serial.print("\n");
  digitalWrite(scl,HIGH);
  // handle ACK  
  while(digitalRead(sda) == HIGH) {
    Serial.println("SDA high additional pulse");
    digitalWrite(scl,LOW);
    digitalWrite(scl,HIGH);
  }
  pinMode(sda,OUTPUT);
  digitalWrite(scl,LOW);
}

void clkPulse(void) {
  digitalWrite(scl,LOW);
  delay(5);
  digitalWrite(scl,HIGH);
  delay(5);
  digitalWrite(scl,LOW);
}  

void poleDeviceACK(void) {
  Serial.println("entering polling");
  pinMode(sda, OUTPUT);
  I2C_start();
  I2C_out(0xA0); // write
  pinMode(sda, INPUT);
  while (digitalRead(sda) == 1) {
      pinMode(sda, OUTPUT);
      I2C_start();
      I2C_out(0xA0);
      delay(10);
      pinMode(sda, INPUT);
  }
  Serial.println("exiting poling");
}

unsigned char I2C_in(void) {  
  int n;
  unsigned char d = 0;
  pinMode(sda,INPUT);
  delay(10);
  for(n=0; n<8; n++) {
    d = (d << 1);
    if(digitalRead(sda) == HIGH) {
      Serial.print("1 ");
      d |= 0x1; // load in 1
    } else {
      Serial.print("0 ");
      d &= 0xFE; // load in 0
    }
    digitalWrite(scl,HIGH);
    delay(5);
    digitalWrite(scl,LOW);
    delay(5);
  }
  Serial.print(d, HEX);
  Serial.print("\n");
  delay(10);
  pinMode(sda,OUTPUT);
  delay(10);
  return d;
}

void I2C_start(void) {
  Serial.println("I2C_start");

  digitalWrite(scl,HIGH);
  digitalWrite(sda,HIGH);
  digitalWrite(sda,LOW);
  digitalWrite(scl,LOW);
}

void I2C_stop(void) {
  Serial.println("I2C_stop");
  
  digitalWrite(sda,LOW);
  digitalWrite(scl,LOW);
  digitalWrite(scl,HIGH);
  digitalWrite(sda,HIGH);
}

