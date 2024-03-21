#include "Arduino.h"
#include "kermite_fullkit_resolve_ldf.h"
#include "km1/KermiteCore.h"
#include "kpm/BoardLED.h"
#include "kpm/KeyScanner_KeyMatrix.h"

KermiteCore kermite;

const int numColumns = 8;
const int numRows = 8;
const int pinColumns[numColumns] = { 26, 27, 28, 29, 6, 7, 0, 1 };
const int pinRows[numRows] = { 26, 27, 28, 29, 6, 7, 0, 1 };

KeyScanner_KeyMatrix keyMatrix(pinColumns, pinRows, numColumns, numRows);

void handleKeyStateChange(int keyIndex, bool pressed) {
  // row と col が同じところ(回路図において、キースイッチがなくてダイオードだけがある場所)
  if (keyIndex % 9 == 0){
    return;
  }

  kermite.feedKeyState(keyIndex, pressed);
}

void setup() {
  keyMatrix.setKeyStateListener(handleKeyStateChange);
  keyMatrix.initialize();

  kermite.setKeyboardName("lyntze46");
  kermite.setProductionMode();
  kermite.begin();
}

void loop() {
  static int count = 0;

  if (count % 10 == 0) {
    keyMatrix.updateInput();
  }

  kermite.processUpdate();

  count++;
  delay(1);
}
