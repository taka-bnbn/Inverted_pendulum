/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com
*********/

// Wi-Fiライブラリをインポート
#include <WiFi.h>

// Wi-Fi接続情報を入力
const char* ssid     = "Takaya's Xperia";
const char* password = "8bf2186a5378";
const IPAddress ip(192, 168, 59, 144);
const IPAddress gateway(192, 168, 11, 1);
const IPAddress subnet(255, 255, 255, 0);
const IPAddress dns1(192, 168, 11, 1);

// ウェブサーバーをポート80で開始
WiFiServer server(80);

// HTTPリクエストを保存しておく変数
String header;

// ピンの状態を保存する変数の宣言
String output14State = "off";
String output27State = "off";
String output12State = "off";
String output13State = "off";
String output26State = "off";

// 使用するピンに名前を付ける
const int output14 = 14;
const int output27 = 27;
const int output12 = 12;
const int output13 = 13;
const int output26 = 26;
const int led = 2;

void setup() {
  Serial.begin(115200);
  // ピンを出力ピンに割り当て
  pinMode(output14, OUTPUT);
  pinMode(output27, OUTPUT);
  pinMode(output12, OUTPUT);
  pinMode(output13, OUTPUT);
  pinMode(output26, OUTPUT);
  pinMode(led, OUTPUT);

  // ピンをオフ（LEDをオフ）
  digitalWrite(output14, LOW);
  digitalWrite(output27, LOW);
  digitalWrite(output12, LOW);
  digitalWrite(output13, LOW);
  digitalWrite(output26, LOW);

  // ssidとpasswordを用いてWi-Fiに接続
  Serial.print("Connecting to ");
  Serial.println(ssid);
  if (!WiFi.config(ip,gateway,subnet,dns1)){
      Serial.println("Failed to configure!");
  }
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

  }
  // IPアドレスを出力し、webserverをスタート
  Serial.println("");
  digitalWrite(led, HIGH);
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();   //クライアント（スマホやPCなど）がつながっているかどうかをclientに出力

  if (client) {                             // クライアントが来たとき
    Serial.println("New Client.");
      digitalWrite(led, HIGH);

    String currentLine = "";                // クライアントからくるデータを格納する変数
    while (client.connected()) {            // クライアントがつながっている間、以下をループ
      if (client.available()) {             // クライアントからデータが来ているとき
        char c = client.read();             // データを読み込み
        Serial.write(c);                    // 届いたデータをシリアルモニタに出力
        header += c;
        if (c == '\n') {                    // 届いたデータが改行コードだった時
          // もし現在の行が空白ならば、この改行コードのみ受け取る
          // つまりHTTPリクエストの終わりなので、レスポンスを返す
          if (currentLine.length() == 0) {
            // HTTPヘッダは（HTTP/1.1 200 OK)のようなステータスコードから始まる
            // 次にコンテントタイプを送信。今回はhtml形式なので以下のようにする
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // リクエストに従ってGPIOをスイッチする
            if (header.indexOf("GET /14/on") >= 0) {
              Serial.println("GPIO 14 on");
              output14State = "on";
              digitalWrite(output14, HIGH);
            } else if (header.indexOf("GET /14/off") >= 0) {
              Serial.println("GPIO 14 off");
              output14State = "off";
              digitalWrite(output14, LOW);
            } else if (header.indexOf("GET /27/on") >= 0) {
              Serial.println("GPIO 27 on");
              output27State = "on";
              digitalWrite(output27, HIGH);
            } else if (header.indexOf("GET /27/off") >= 0) {
              Serial.println("GPIO 27 off");
              output27State = "off";
              digitalWrite(output27, LOW);
            } else if (header.indexOf("GET /12/on") >= 0) {
              Serial.println("GPIO 12 on");
              output12State = "on";
              digitalWrite(output12, HIGH);
            } else if (header.indexOf("GET /12/off") >= 0) {
              Serial.println("GPIO 12 off");
              output12State = "off";
              digitalWrite(output12, LOW);
            } else if (header.indexOf("GET /13/on") >= 0) {
              Serial.println("GPIO 13 on");
              output13State = "on";
              digitalWrite(output13, HIGH);
            } else if (header.indexOf("GET /13/off") >= 0) {
              Serial.println("GPIO 13 off");
              output13State = "off";
              digitalWrite(output13, LOW);
            } else if (header.indexOf("GET /26/on") >= 0) {
              Serial.println("GPIO 26 on");
              output26State = "on";
              digitalWrite(output26, HIGH);
            } else if (header.indexOf("GET /26/off") >= 0) {
              Serial.println("GPIO 26 off");
              output26State = "off";
              digitalWrite(output26, LOW);
            }

            // htmlを表示
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // ON/OFFボタンのためのCSS
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");

            // ページ本体（bodyタグ内）
            client.println("<body><h1>Team B5<br>Inverted Pendulum</h1>");

            // 現在のピンの状態と、オンオフ用のボタンを出力
            client.println("<p>Progress -state " + output14State + "</p>");
            // output14Stateがオフなら、ONにするボタンを表示
            if (output14State == "off") {
              client.println("<p><a href=\"/14/on\"><button class=\"button\">Progress</button></a></p>");
            } else {
              client.println("<p><a href=\"/14/off\"><button class=\"button button2\">STOP</button></a></p>");
            }

            // 27ピンの状態と、オンオフボタン
            client.println("<p>Recession -state " + output27State + "</p>");
            // output27Stateがオフなら、ONにするボタンを表示
            if (output27State == "off") {
              client.println("<p><a href=\"/27/on\"><button class=\"button\">Recession</button></a></p>");
            } else {
              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">STOP</button></a></p>");
            }

            // 12ピンの状態と、オンオフボタン
            client.println("<p>Extend -state " + output12State + "</p>");
            // output12Stateがオフなら、ONにするボタンを表示
            if (output12State == "off") {
              client.println("<p><a href=\"/12/on\"><button class=\"button\">Extend</button></a></p>");
            } else {
              client.println("<p><a href=\"/12/off\"><button class=\"button button2\">STOP</button></a></p>");
            }

            // 13ピンの状態と、オンオフボタン
            client.println("<p>Contract -state " + output13State + "</p>");
            // output13Stateがオフなら、ONにするボタンを表示
            if (output13State == "off") {
              client.println("<p><a href=\"/13/on\"><button class=\"button\">Contract</button></a></p>");
            } else {
              client.println("<p><a href=\"/13/off\"><button class=\"button button2\">STOP</button></a></p>");
            }

            // 26ピンの状態と、オンオフボタン
            client.println("<p>Stabilize -state " + output26State + "</p>");
            // output26Stateがオフなら、ONにするボタンを表示
            if (output26State == "off") {
              client.println("<p><a href=\"/26/on\"><button class=\"button\">Stabilize</button></a></p>");
            } else {
              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">STOP</button></a></p>");
            }

            client.println("</body></html>");

            //　HTTPレスポンスの最後は改行で終了
            client.println();
            // whileループの終了
            break;
          } else { // 改行コードを取得したら、currentLineをリセット
            currentLine = "";
          }
        } else if (c != '\r') {  // 改行以外の何かしらのコードが来ているとき
          currentLine += c;      // currentLineに追加
        }
      }
    }
    // ヘッダーをリセット
    header = "";
    // 接続をリセット
    client.stop();
    digitalWrite(led, LOW);
    Serial.println("Client disconnected.");
    
    Serial.println("");
  }
}

