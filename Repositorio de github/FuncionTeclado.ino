#include <IRremote.h>
#include <BleKeyboard.h>

#define IR_RECEIVE_PIN 4

IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;
BleKeyboard bleKeyboard("ESP32 Keyboard");

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Inicia el receptor IR
  bleKeyboard.begin(); // Inicia el teclado BLE
}

void loop() {
  if (irrecv.decode(&results)) {
    unsigned long key_value = results.value;
    Serial.print("Código recibido: 0x");
    Serial.println(key_value, HEX); // Imprime el valor en hexadecimal
    
    if (bleKeyboard.isConnected()) {
      switch (key_value) {
        case 0XFF906F: // Código del botón "Next"
          bleKeyboard.write(KEY_RIGHT_ARROW); // Siguiente diapositiva
          Serial.println("Siguiente diapositiva");
          break;
        case 0XFFE01F: // Código del botón "Previous"
          bleKeyboard.write(KEY_LEFT_ARROW); // Diapositiva anterior
          Serial.println("Diapositiva anterior");
          break;
        case 0XFFA857: // Código del botón "Enter"
          bleKeyboard.write(KEY_F5); // Presionar Enter
          Serial.println("Enter");
          break;
        case 0XFFA25D: // Código del botón "Power Off"
          bleKeyboard.write(KEY_ESC); // Cerrar PowerPoint (Escape)
          Serial.println("Cerrar PowerPoint");
          break;
        default:
          Serial.println("Botón no asignado");
          break;
      }
    }
    
    irrecv.resume(); // Habilita la recepción del siguiente valor
  }
}
