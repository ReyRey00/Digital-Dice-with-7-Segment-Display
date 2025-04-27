/*

    HELLO TECHOCRATS AND FATIMANIANS :)

    Digital-Dice-with-7-Segment-Display - SC;

*/


// Segment pins for Player 1
const int player1Segments[7] = {2, 3, 4, 5, 6, 7, 8};
// Segment pins for Player 2
const int player2Segments[7] = {9, 10, 11, 12, 13, A0, A1};

// Buttons
const int button1 = A2;
const int button2 = A5;

// Buzzer pin
const int buzzerPin = A4;

const byte diceDigits[7] = {
  B00000000, // 0 (blank)
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B01111101  // 6
};

const byte fullOn = B01111111; // All segments ON ("8")

bool player1Rolled = false;
bool player2Rolled = false;

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(player1Segments[i], OUTPUT);
    pinMode(player2Segments[i], OUTPUT);
  }

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

  randomSeed(analogRead(0));
}

void loop() {
  bool pressed1 = digitalRead(button1) == LOW;
  bool pressed2 = digitalRead(button2) == LOW;

  if (pressed1) {
    delay(200);  // debounce
    int finalRoll = rollAnimation(player1Segments);
    displayDice(player1Segments, finalRoll);
    tone(buzzerPin, 1000, 500);  // Final buzz
    player1Rolled = true;
  }

  if (pressed2) {
    delay(200);
    int finalRoll = rollAnimation(player2Segments);
    displayDice(player2Segments, finalRoll);
    tone(buzzerPin, 1000, 500);  // Final buzz
    player2Rolled = true;
  }

  // Idle "88"
  if (!player1Rolled) displayPattern(player1Segments, fullOn);
  if (!player2Rolled) displayPattern(player2Segments, fullOn);
}

int rollAnimation(const int segmentPins[7]) {
  int result = 1;
  for (int i = 0; i < 30; i++) { //can increase/decrease the condtion "30" for longer/shorter duration of rolling animation
    result = random(1, 7);
    displayPattern(segmentPins, diceDigits[result]);
    tone(buzzerPin, 2000, 30); // short beep per frame
    delay(75);
  }
  return result;
}

void displayDice(const int segmentPins[7], int value) {
  displayPattern(segmentPins, diceDigits[value]);
}

void displayPattern(const int segmentPins[7], byte pattern) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], bitRead(pattern, i));
  }
}
