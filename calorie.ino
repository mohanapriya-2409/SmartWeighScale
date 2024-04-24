#include <WiFi.h>

const char* ssid = "Miraclee";
const char* password = "qwertyuiop1";

const int serverPort = 8080; // Port for TCP server

WiFiServer server(serverPort);

String previousDetection = ""; // Variable to store previous detection
float appleWeight = 83.6; // Weight of the detected apple in grams

// Lookup table for nutritional content per unit weight of detected objects
const char* nutritionalContent[][6] = {
  {"APPLE", "0.52", "0.013", "0.03", "0.01", "0.0024"},
  {"BANANA", "0.89", "0.023", "0.011", "0.012", "0.0026"},
  {"CARROT", "0.41", "0.09", "0.009", "0.047", "0.0028"},
  {"ORANGE", "0.47", "0.011" ,"0.009", "0.009", "0.0024"}
  
  // Add more objects and their nutritional content per unit weight here
};

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    while (client.connected()) {
      String line = client.readStringUntil('\r');
      if (line.length()) {
        // Print only if the current detection is different from the previous one
        if (line != previousDetection) {
          Serial.println(line);
          // Search for nutritional content per unit weight of the detected object
          for (int i = 0; i < sizeof(nutritionalContent) / sizeof(nutritionalContent[0]); i++) {
            if (line == nutritionalContent[i][0]) {
              // Parse nutritional content per unit weight
             
              float calories = atof((nutritionalContent[i][1]));
              float carbs = atof((nutritionalContent[i][2]));
              float protein = atof(nutritionalContent[i][3]);
              float sugar = atof(nutritionalContent[i][4]);
              float fiber = atof(nutritionalContent[i][5]);
              // Calculate total nutritional content based on apple weight
              float totalCalories = calories * (appleWeight); // Convert weight to percentage
              float totalCarbs = carbs * (appleWeight);
              float totalproteins = protein * (appleWeight) ;
              float totalsugar = sugar *(appleWeight) ;
              float totalfiber = fiber *(appleWeight) ; // Convert weight to percentage
              // Print total nutritional content
              Serial.print("Total nutritional content for ");
              Serial.print(line);
              Serial.println(":");
              Serial.println("DETECTED WEIGHT : 83.6g");
              Serial.print("Calories: ");
              Serial.print(totalCalories);
              Serial.println("kcal");
              Serial.print("Carbs: ");
              Serial.print(totalCarbs);
              Serial.println("g");
              Serial.print("Protein: ");
              Serial.print(totalproteins);
              Serial.println("g");
              Serial.print("Sugar: ");
              Serial.print(totalsugar);
              Serial.println("g");
              Serial.print("Fiber: ");
              Serial.print(totalfiber);
              Serial.println("g");
              break;
            }
          }
          previousDetection = line; // Update previous detection
        }
      }
    }
    client.stop();
  }
}
