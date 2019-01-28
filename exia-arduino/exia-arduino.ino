
// data pins (button pin)
#define DATA_PIN1 5
#define DATA_PIN2 6

// mode state
unsigned int mode_current = 0;
const unsigned int mode_number = 6;

// counter state
unsigned long loop_current = 0;
const unsigned long loop_delay = 1;
const unsigned long loop_number = ((unsigned long) 1000 * 60 * 10) / loop_delay;

void sleep(unsigned long ms) {
  delay(ms);
  loop_current += ms / loop_delay;
}

void setup() {

  // set pin modes
  pinMode(DATA_PIN1, OUTPUT);
  pinMode(DATA_PIN2, OUTPUT);

  // start serial
  Serial.begin(9600);
  while (!Serial);
}

void loop() {

  // check if data is arriving
  while (Serial.available() > 0) {

    // read single char
    int input = Serial.read();

    // check command
    switch (input) {
      case '0':
        setMode(0);
        break;
      case '1':
        setMode(1);
        break;
      case '2':
        setMode(2);
        break;
      case '3':
        setMode(3);
        break;
      case '4':
        setMode(4);
        break;
      case '5':
        setMode(5);
        break;
    }
  }

  // refresh mode
  delay(loop_delay);
  if (++loop_current >= loop_number) {
    int mode_last = mode_current;
    nextMode();
    setMode(mode_last);
    loop_current = 0;
  }
}

// set the mode to a specific one
void setMode(int mode) {
  while (mode_current != mode)
    nextMode();
}

// for setting the mode to the next one
void nextMode() {

  // set to high for modus change
  digitalWrite(DATA_PIN1, HIGH);
  digitalWrite(DATA_PIN2, HIGH);
  sleep(100);

  // set to low again
  digitalWrite(DATA_PIN1, LOW);
  digitalWrite(DATA_PIN2, LOW);

  // ensure mode set is done
  sleep(100);

  // remember the current mode
  mode_current = (mode_current + 1) % mode_number;

  // send the current state over serial
  if (Serial)
    Serial.print(mode_current);
}
