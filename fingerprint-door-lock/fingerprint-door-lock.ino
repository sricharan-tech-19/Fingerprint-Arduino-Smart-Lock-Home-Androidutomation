String readString;
#define relay1 3    // Connect relay1 to pin D3

void setup()
{
  Serial.begin(9600);           // Set rate for communicating with phone or fingerprint sensor
  pinMode(relay1, OUTPUT);      // Set relay1 as output
  digitalWrite(relay1, HIGH);   // Turn ON relay at the beginning
}

void loop()
{
  while(Serial.available())    // If data is available on Serial
  {
    delay(10);                 // Small delay for stability
    char c = Serial.read();    // Read one character
    if (c == '#'){
      break;                   // Stop reading if '#' is encountered
    }
    readString += c;           // Append character to readString
  }

  if (readString.length() > 0)   // If any command has been received
  {
    Serial.println(readString);  // Print received string (for debugging)
    
    if(readString == "f success")   // If fingerprint match is successful
    {
      digitalWrite(relay1, LOW);    // Turn OFF the relay (e.g., unlock)
      delay(3000);                  // Wait for 3 seconds
      digitalWrite(relay1, HIGH);   // Turn ON relay again (lock)
    }
    
    readString = "";                // Clear the string for the next input
  }
}

