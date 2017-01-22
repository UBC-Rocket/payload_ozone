
int temp_read = 22;
int o3_a_read = 23;
int o3_b_read = 11;
int no2_read = 18;
int pm25_read = 14;
int pwm_led = 15;
int pwm_motor_a = 12;
int pwm_motor_b = 13;
int motor_enable = 17;
int readthresh = 500;

int temperature;
int conc_pm25;
int conc_no2;
int conc_o3;
int o3_a;
int_o3_b;

void setup()
{
    Serial.begin(9600);

    pinMode(tempread, INPUT);
    pinMode(o3_a_read, INPUT);
    pinMode(o3_b_read, INPUT);
    pinMode(no2_read, INPUT);
    pinMode(pm25_read, INPUT);

    pinMode(pwm_motor_a, OUTPUT);
    pinMode(pwm_motor_b, OUTPUT);
    pinMode(pwm_led, OUTPUT);
    pinMode(motor_enable, OUTPUT);

}


int count = 0;
long tic = millis();
long toc;

void loop()
{
    toc = millis();
    if((toc - tic) > readthresh){
        readwrite_all();
        tic = millis();
    }


}

void readwrite_all(){

    temperature = analogRead(temp_read);
    conc_no2 = analogRead(no2_read);

    if(count == 7){
        o3 = analogRead(o3_a_read);
    }
    else if(count == 15){
        o3 = analogRead(o3_b_read);
    }


}
