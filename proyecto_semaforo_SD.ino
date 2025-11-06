// Declaración de las variables usadas en las instrucciones.
int rojoCoche = 8; 
int amarilloCoche = 9;
int verdeCoche = 10;
int rojoPeaton = 12;
int verdePeaton = 13;
int pulsador = 2;
int buzzer = 7;

void setup() {
  // Configuración de los pines de entrada(1) y salida(6).
  pinMode(rojoCoche, OUTPUT);
  pinMode(amarilloCoche, OUTPUT);
  pinMode(verdeCoche, OUTPUT);
  pinMode(rojoPeaton, OUTPUT);
  pinMode(verdePeaton, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pulsador, INPUT_PULLUP);

  // Inicialización del semáforo de coches en verde y el de peatones en rojo, además del buzzer apagado.
  digitalWrite(verdeCoche, HIGH); // Paso permitido para coches.
  digitalWrite(rojoPeaton, HIGH); // Paso denegado para peatones.
  digitalWrite(buzzer, LOW);  // Buzzer apagado.
}

void loop() {
  // Si el botón es presionado.
  if (digitalRead(pulsador) == LOW) {
    // Espera 5 segundos antes de iniciar el cambio de semáforo para no realizar un cambio repentino.
    delay(5000);
    // Cambiar el semáforo de coches para permitir el paso a los peatones.
    digitalWrite(verdeCoche, LOW);
    digitalWrite(amarilloCoche, HIGH);
    delay(15000);  // Espera 15 segundos en amarillo el semaforo de los coches antes de permitir el paso a los peatones.

    digitalWrite(amarilloCoche, LOW);
    digitalWrite(rojoCoche, HIGH);
    digitalWrite(rojoPeaton, LOW);
    digitalWrite(verdePeaton, HIGH);  // Los peatones pueden cruzar.

    // Buzzer intermitente mientras peatones tienen verde fijo.
    unsigned long tiempoTotal = 25000;   
    unsigned long paso = 500;            // Cada ciclo ON/OFF dura 500 ms.

    for (unsigned long t = 0; t < tiempoTotal; t += paso) {
      digitalWrite(buzzer, HIGH);     // Suena.
      delay(paso / 2);                // Duración = 250 ms.
      digitalWrite(buzzer, LOW);      // No suena.
      delay(paso / 2);                // Duración de otros 250 ms.
    }

    // En este bucle conseguimos que el semáforo de los peatones antes de ponerse en rojo y permitir el paso
    // a los coches, parpadea para avisar a los peatones del cambio de estado. El buzzer también ha sido configurado para que,
    // cuando el semáforo de los peatones parpadea este también disminuye la velocidad del sonido para avisar de manera sonora.
    for (int i = 0; i < 5; i++) {
      digitalWrite(verdePeaton, LOW);
      digitalWrite(buzzer, LOW);
      delay(300);
      digitalWrite(verdePeaton, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(300);
    }
    // Vuelta al estado inicial.
    digitalWrite(verdePeaton, LOW);
    digitalWrite(rojoPeaton, HIGH);
    digitalWrite(verdeCoche, HIGH);
    digitalWrite(rojoCoche, LOW);
    digitalWrite(buzzer, LOW);  // Aseguramos que el buzzer está apagado.
  }
}
