const int boton = 7;
const int led = 13;

bool ledActiva = false;
bool bloqueo = false;

int lecturaAnterior = HIGH;
int estadoEstable = HIGH;

unsigned long tiempoRebote = 0;
unsigned long tiempoInicio = 0;
unsigned long tiempoBloqueo = 0;

void setup() {
  pinMode(boton, INPUT_PULLUP);
  pinMode(led, OUTPUT);

  digitalWrite(led, LOW);
}

void loop() {

  int lectura = digitalRead(boton);

  if (lectura != lecturaAnterior) {
    tiempoRebote = millis();
  }

  if (millis() - tiempoRebote >= 50) {

    if (lectura != estadoEstable) {
      estadoEstable = lectura;

      // Detectar pulsación
      if (estadoEstable == LOW &&
          !ledActiva && !bloqueo) {

        digitalWrite(led, HIGH);
        tiempoInicio = millis();
        ledActiva = true;
      }
    }
  }

  lecturaAnterior = lectura;

  // Apagar después de 10 segundos
  if (ledActiva &&
      millis() - tiempoInicio >= 10000) {

    digitalWrite(led, LOW);
    ledActiva = false;
    bloqueo = true;
    tiempoBloqueo = millis();
  }

  // Esperar 2 segundos
  if (bloqueo &&
      millis() - tiempoBloqueo >= 2000) {

    bloqueo = false;
  }
}


