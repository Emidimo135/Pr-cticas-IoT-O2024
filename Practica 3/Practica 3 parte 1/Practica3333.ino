/*3.1 // Prácticas materia IoT - Práctica realizada por Profesora: Guadalupe Torres G
#include "DHT.h" // Se incluye la librería DHT para trabajar con sensores de temperatura y humedad.

// Definimos el pin y el tipo de sensor.
#define DHTPIN 4 // Pin digital al que está conectado el sensor.
#define DHTTYPE DHT11  // Definimos el tipo de sensor (DHT11).

// Creamos una instancia del sensor DHT usando el pin y tipo definidos.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);  // Iniciamos la comunicación serial a 9600 baudios.
  Serial.println(F("DHT11 test!"));  // Imprimimos un mensaje inicial en el monitor serial para indicar que el sensor se está probando.

  dht.begin();  // Iniciamos el sensor DHT.
}

void loop() {
  delay(2000);  // Pausamos 2 segundos entre lecturas porque el sensor es lento.
  
  // Leemos la humedad desde el sensor.
  float h = dht.readHumidity();
  
  // Leemos la temperatura desde el sensor.
  float t = dht.readTemperature();

  // Verificamos si las lecturas son válidas. Si no lo son, se imprime un mensaje de error.
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));  // Si la lectura falla, imprimimos un mensaje de error.
    return;  // Salimos del loop sin continuar.
  }

  // Si las lecturas son correctas, imprimimos los valores de humedad y temperatura.
  Serial.print(F("Humedad: "));  // Imprimimos el texto "Humedad".
  Serial.print(h);  // Imprimimos el valor de la humedad.
  Serial.print(F("% Temperatura: "));  // Imprimimos el texto "Temperatura".
  Serial.print(t);  // Imprimimos el valor de la temperatura.
  Serial.println(F("°C "));  // Imprimimos el símbolo de grados Celsius y hacemos un salto de línea.
}
*/

/*3.2
// Prácticas IoT - Práctica realizada por Profesora: Guadalupe Torres
#include <Wire.h>                 // Librería para la comunicación I2C
#include <Adafruit_GFX.h>          // Librería gráfica para manejar displays
#include <Adafruit_SSD1306.h>      // Librería para el display OLED SSD1306
#include <Adafruit_Sensor.h>       // Librería base para sensores de Adafruit
#include <DHT.h>                   // Librería para el sensor DHT

#define SCREEN_WIDTH 128           // Ancho del display OLED en píxeles
#define SCREEN_HEIGHT 64           // Alto del display OLED en píxeles

// Declaración del display OLED conectado por I2C (pines SDA, SCL)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTPIN 4                   // Pin digital conectado al sensor DHT

// Definir el tipo de sensor DHT que estamos utilizando
#define DHTTYPE DHT11              // Usamos el sensor DHT11
//#define DHTTYPE DHT22            // Descomentar si se usa un DHT22
//#define DHTTYPE DHT21            // Descomentar si se usa un DHT21

DHT dht(DHTPIN, DHTTYPE);          // Inicializamos el objeto del sensor DHT

void setup() {
  Serial.begin(115200);            // Inicializar la comunicación serial para depuración

  dht.begin();                     // Inicializar el sensor DHT

  // Inicializar el display OLED y verificar si está conectado correctamente
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed")); // Mostrar error si no se inicializa
    for(;;);                     // Bucle infinito si falla el OLED
  }
  delay(2000);                     // Esperar 2 segundos para estabilización
  display.clearDisplay();           // Limpiar el contenido previo en la pantalla
  display.setTextColor(WHITE);      // Establecer el color del texto en blanco
}

void loop() {
  delay(5000);                     // Esperar 5 segundos entre lecturas

  // Leer temperatura y humedad desde el sensor DHT
  float t = dht.readTemperature();  // Leer temperatura en grados Celsius
  float h = dht.readHumidity();     // Leer humedad en porcentaje

  // Mostrar los valores de temperatura y humedad en el monitor serial
  Serial.println(t);
  Serial.println(h);

  // Verificar si las lecturas son válidas
  if (isnan(h) || isnan(t)) {
    Serial.println("Fallo al leer datos del sensor DHT1!");  // Mostrar error si falla la lectura
  }

  // Limpiar el display antes de actualizarlo
  display.clearDisplay();
  
  // Mostrar la temperatura en el display OLED
  display.setTextSize(1);
  display.setCursor(0, 0);          // Posicionar el cursor en la parte superior izquierda
  display.print("Temperatura: ");
  display.setTextSize(2);
  display.setCursor(0, 10);         // Ajustar la posición del cursor
  display.print(t);                 // Mostrar el valor de la temperatura
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);              // Habilitar el conjunto de caracteres CP437 para el símbolo de grados
  display.write(167);               // Mostrar el símbolo de grados
  display.setTextSize(2);
  display.print("C");               // Mostrar la unidad Celsius

  // Mostrar la humedad en el display OLED
  display.setTextSize(1);
  display.setCursor(0, 35);         // Posicionar el cursor más abajo para mostrar la humedad
  display.print("Humedad: ");
  display.setTextSize(2);
  display.setCursor(0, 45);
  display.print(h);                 // Mostrar el valor de la humedad
  display.print(" %");              // Añadir el símbolo de porcentaje
  
  display.display();                // Actualizar la pantalla con los nuevos valores
}*/

/*
3.3
//Medidor de distancia hecho por Guadalupe Torres
const int trigPin = 5;   // Pin conectado al Trigger del sensor ultrasónico
const int echoPin = 18;  // Pin conectado al Echo del sensor ultrasónico

// Definir la velocidad del sonido en cm/us
#define SOUND_SPEED 0.034  // Velocidad del sonido en cm/us
#define CM_TO_INCH 0.393701 // Conversión de centímetros a pulgadas

long duration;           // Variable para almacenar el tiempo que tarda el eco en volver
float distanceCm;        // Variable para almacenar la distancia en centímetros
float distanceInch;      // Variable para almacenar la distancia en pulgadas

void setup() {
  Serial.begin(115200);   // Iniciar la comunicación serial para depuración
  pinMode(trigPin, OUTPUT);  // Configurar el pin Trigger como salida
  pinMode(echoPin, INPUT);   // Configurar el pin Echo como entrada
}

void loop() {
  // Asegurarse de que el Trigger está apagado antes de iniciar la medición
  digitalWrite(trigPin, LOW);
  delayMicroseconds(20);   // Esperar 2 microsegundos
  
  // Enviar una señal de 10 microsegundos al Trigger para iniciar la medición
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(100);
  digitalWrite(trigPin, LOW);
  
  // Leer el tiempo de viaje del pulso usando el pin Echo (en microsegundos)
  duration = pulseIn(echoPin, HIGH);
  
  // Calcular la distancia en centímetros
  distanceCm = duration * SOUND_SPEED / 2;  // Dividimos entre 2 porque es ida y vuelta
  
  // Convertir la distancia a pulgadas
  distanceInch = distanceCm * CM_TO_INCH;
  
  // Mostrar la distancia en el Monitor Serial
  Serial.print("Distancia (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distancia (inch): ");
  Serial.println(distanceInch);
  
  delay(2000);  // Esperar dos segundos antes de realizar la siguiente medición 
}
*/

//3.4
// Medidor de distancia a OLED hecho por Guadalupe Torres
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // Ancho de la pantalla OLED
#define SCREEN_HEIGHT 64 // Altura de la pantalla OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int trigPin = 5;   // Pin de Trigger del sensor ultrasónico
const int echoPin = 18;  // Pin de Echo del sensor ultrasónico
#define SOUND_SPEED 0.034 // Velocidad del sonido en cm/us

long duration;
float distanceCm;

void setup() {
  Serial.begin(115200); // Inicia la comunicación serial
  pinMode(trigPin, OUTPUT); // Establece el pin de Trigger como salida
  pinMode(echoPin, INPUT);  // Establece el pin de Echo como entrada

  // Inicia el display OLED, verifica la conexión
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Bucle infinito si falla la inicialización
  }
  display.clearDisplay(); // Limpia la pantalla
  display.setTextSize(1); // Establece el tamaño del texto
  display.setTextColor(WHITE); // Establece el color del texto
  display.setCursor(0,0); // Posiciona el cursor
  display.println("Iniciando sensor..."); // Muestra mensaje inicial
  display.display(); // Actualiza la pantalla
  delay(2000); // Retardo inicial
}

void loop() {
  digitalWrite(trigPin, LOW); // Asegura que el Trigger está desactivado
  delayMicroseconds(2); // Breve pausa
  digitalWrite(trigPin, HIGH); // Envía un pulso
  delayMicroseconds(10); // Duración del pulso
  digitalWrite(trigPin, LOW); // Finaliza el pulso

  duration = pulseIn(echoPin, HIGH); // Mide el tiempo del eco
  distanceCm = duration * SOUND_SPEED / 2; // Calcula la distancia

  // Muestra la distancia en el OLED
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Distancia: ");
  display.print(distanceCm);
  display.println(" cm");
  display.display();

  // También envía la distancia al Monitor Serial
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);

  delay(1000); // Espera antes de la próxima medición
}