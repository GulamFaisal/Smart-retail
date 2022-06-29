#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "xxxxxxx"; //Enter Wi-Fi SSID
const char* password =  "xxxxxxxx"; //Enter Wi-Fi Password

ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
int a;
int p1=0,p2=0,p3=0,p4=0;
int p5=0;
int c1=0,c2=0,c3=0,c4=0,c5=0;
int count_prod;
int total;
String page = "";
String text = "";
double data;
void setup(void) {
  pinMode(D1,INPUT);
  pinMode(D5,INPUT);
  pinMode(D6,INPUT);
  pinMode(D7,INPUT);
  pinMode(D0,INPUT);
  pinMode(D4,INPUT_PULLUP);

  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", []() {
    page = "<html style='background:url(https://media.istockphoto.com/photos/flying-shopping-cart-with-shopping-bags-on-a-pink-background-picture-id1292443598?k=20&m=1292443598&s=612x612&w=0&h=kDZHrdaoSei36vleKWfrHgJ0a5Seh7dfeCNOHImC_d4=); background-size: cover; width: 100vw; height: 100vh;'><head><title>E Cart using IoT</title></head><style type=\"text/css\">";
    page += "table{border-collapse: collapse;background:linear-gradient(45deg, hsla(4, 95%, 84%, 1) 0%, hsla(177, 72%, 78%, 1) 100%)}th {background-color:#3498db ;color: white;}table,td {border: 4px solid black;font-size: x-large;";
    page += "text-align:center;border-style: groove;border-color: rgb(255,0,0);}</style><body><center>";
    page += "<h1>Smart Shopping Cart using IoT</h1><br><br><table style=\"width: 1200px;height: 450px;\"><tr>";
    page += "<th>ITEMS</th><th>QUANTITY</th><th>COST</th></tr><tr><td>Milk</td><td>"+String(p1)+"</td><td>"+String(c1)+"</td>";
    page += "</tr><tr><td>Coca Cola</td><td>"+String(p2)+"</td><td>"+String(c2)+"</td>";
    page += "</tr><tr><td>Trimmer</td><td>"+String(p3)+"</td><td>"+String(c3)+"</td>";
    page += "</tr><tr><td>Sugar</td><td>"+String(p4)+"</td><td>"+String(c4)+"</td>";
    page += "</tr><tr><td>Battery</td><td>"+String(p5)+"</td><td>"+String(c5)+"</td>";
    page += "</tr><tr><th>Grand Total</th><th>"+String(count_prod)+"</th><th>"+String(total)+"</th>";
    page += "</tr></table><br><input type=\"button\" name=\"Pay Now\" value=\"Pay Now\" style=\"width: 200px; height:50px\"></center></body></html>";
        
    
    server.send(200, "text/html", page);
  });

  server.begin();
  Serial.println("Web server started!");
}

void loop() {
  int x=digitalRead(D5);
  int y=digitalRead(D6);
  int b=digitalRead(D7);
  int a=digitalRead(D4);
  int z=digitalRead(D0);
  int c=digitalRead(D1);

  if ((x==1)&&(a==1))
    {
        
        total = total + 30;
        count_prod++;
        p1++;
        delay(5000);
    }
  else if ((x==1)&&(a==0))
    {
      if(p1>0)
        {
      
        total = total - 30;
        count_prod--;
        p1--;
        delay(5000);
        }
    }
  else if ((a==1)&&(y==1))
    {
        total = total + 39;
        count_prod++;
        p2++;
        delay(5000);
    }
  else if ((a==0)&&(y==1))
    {
      if(p2>0)
        {
        
        total = total - 39;
        count_prod--;
        p2--;
        delay(5000);
        }
    }
  else if ((b==1)&&(a==1))
    {
        
        total = total + 400;
        p3++;
        count_prod++;
        
        delay(5000);
    }
  else if ((b==1)&&(a==0))
    {
      if(p3>0)
        {
        total = total - 400;
        p3--;
        count_prod--;
        delay(5000);
        }
    }
  else if ((z==1)&&(a==1))
    {
        total = total + 50;
        p4++;
        count_prod++;
        
        delay(5000);
    }
  else if ((z==1)&&(a==0))
    {
      if(p4>0)
        {
        total = total - 50;
        count_prod--;
        p4--;
        delay(5000);
        }
    }
  else if ((c==1)&&(a==1))
    {
        total = total + 80;
        count_prod++;
        p5++;
        delay(5000);
        Serial.println(p5);
    }
  else if ((c==1)&&(a==0))
    {
      if(p5>0)
        {
        total = total - 80;
        count_prod--;
        p5--;
        delay(5000);
        }
    }
    
    c1=p1*30;
    c2=p2*39;
    c3=p3*400;
    c4=p4*50;
    c5=p5*80;
  server.handleClient();
}
