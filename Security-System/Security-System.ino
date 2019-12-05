#include <Servo.h>
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

#define LED_PIN  11
#define LED_COUNT 4 // 네오픽셀의 총 갯수는 4
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
/*************return 값을 2개 반환하기 위해 구조체 생성 ************/
struct values {

  int px;
  int py;
};

/************* 좌표 클래스 ************/
class pointXY {
  private:
    int x;
    int y;
  public:
    values v;
    void setXY(int x, int y) {
      this->x = x;
      this->y = y;
    }
    int getX() {
      return x;
    }
    int getY() {
      return y;
    }
    values getXY() {
      v.px = this->x;
      v.py = this->y;
      return v;
    }

};
/*************비밀번호 클래스 ************/
class passwd {


  public:
    pointXY passwdXY[3]; // 비밀번호 좌표를 저장하는 변수


};

/*************좌표 간의 넓이 계산 ************/
float calArea(pointXY ptXY[], pointXY ptXY2[]) {
  // (ptXY[0].x, ptXY[0].y)  (ptXY[1].x,ptXY[1].y)   (ptXY[2].x, ptXY[2].y)
  //     a         b             c         d              e         f

  float area = 0.5 * ((ptXY[0].getX() * ptXY[1].getY() + ptXY[1].getX() * ptXY[2].getY() + ptXY[2].getX() * ptXY[0].getY())
                      - (ptXY[1].getX() * ptXY[0].getY() + ptXY[2].getX() * ptXY[1].getY() + ptXY[0].getX() * ptXY[2].getY()));
  float area2 = 0.5 * ((ptXY2[0].getX() * ptXY2[1].getY() + ptXY2[1].getX() * ptXY2[2].getY() + ptXY2[2].getX() * ptXY2[0].getY())
                       - (ptXY2[1].getX() * ptXY2[0].getY() + ptXY2[2].getX() * ptXY2[1].getY() + ptXY2[0].getX() * ptXY2[2].getY()));

  if (area == area2)
  {
    Serial.println("1차 검사 통과\n");
    return 1;
  }
  else
  {
    return 0;
  }

}

/*************좌표 간의 차이 계산 ************/
pointXY* calDiffPoint(pointXY ptXY[], pointXY ptXY2[]) {

  pointXY diffPoint[2];
  pointXY diffPoint2[2];

  diffPoint[0].setXY((ptXY[0].getX() - (ptXY[1].getX())), (ptXY[0].getY() - (ptXY[1].getY())));
  diffPoint[1].setXY((ptXY[0].getX() - (ptXY[2].getX())), (ptXY[0].getY() - (ptXY[2].getY())));

  Serial.println("입력된 비밀번호의 차 입니다.");
  printPoint(diffPoint);

  diffPoint2[0].setXY((ptXY2[0].getX() - (ptXY2[1].getX())), (ptXY2[0].getY() - (ptXY2[1].getY())));
  diffPoint2[1].setXY((ptXY2[0].getX() - (ptXY2[2].getX())), (ptXY2[0].getY() - (ptXY2[2].getY())));


  Serial.println("비밀번호의 차 입니다.");
  printPoint(diffPoint2);


  if (diffPoint[0].getX() == diffPoint2[0].getX() &&
      diffPoint[0].getY() == diffPoint2[0].getY() &&
      diffPoint[1].getX() == diffPoint2[1].getX() &&
      diffPoint[1].getY() == diffPoint2[1].getY())
  {

    Serial.println("2차 검사 통과\n");
    return 1;
  }
  else return 0;


}

/*************이전 좌표와 현재 좌표가 중복인지 확인 ************/
int checkPrePoint(pointXY ptXY, pointXY preptXY) {

  if ((ptXY.getX() == preptXY.getX()) &&
      (ptXY.getY() == preptXY.getY()))
  {

    return -1;

  }
  else
    return 0;
}


void printPoint(pointXY ptXY[]) {

  for (int i = 0; i < 2; i++) {
    Serial.print(ptXY[i].getX());
    Serial.print(" ");
    Serial.println(ptXY[i].getY());
  }

}
/*************전역변수 선언 ************/
passwd pw;
pointXY ptXY[3];
int pwIndex = 0;

int fsrSensor0 = A0; // 1번 압력센서 A0에 연결
int fsrSensor1 = A1; // 2번 압력센서 A1에 연결
int fsrSensor2 = A2; // 3번 압력센서 A2에 연결
int fsrSensor3 = A3; // 4번 압력센서 A3에 연결
int fsrSensor4 = A4; // 5번 압력센서 A4에 연결
int fsrSensor5 = A5; // 6번 압력센서 A5에 연결
int fsrSensor6 = A6; // 7번 압력센서 A6에 연결
int fsrSensor7 = A7; // 8번 압력센서 A7에 연결
int fsrSensor8 = A8; // 9번 압력센서 A8에 연결

int inputPIN = 2;
int statusPIR = 0;
int valueRead = 0;

Servo myservo;  // 서보모터 선

int echoPin = 13;
int trigPin = 12;

int openFlag = 0;
float timer;
int bt = 0;

int fsr0;
int fsr1;
int fsr2;
int fsr3;
int fsr4;
int fsr5;
int fsr6;
int fsr7;
int fsr8;

int transFsr0;
int transFsr1;
int transFsr2;
int transFsr3;
int transFsr4;
int transFsr5;
int transFsr6;
int transFsr7;
int transFsr8;

void setup() {

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  strip.begin();
  strip.show();


   


  /*************초기 암호 설정(1,4,5) ************/
  Serial.begin(9600);
  pw.passwdXY[0].setXY(1, 0);
  pw.passwdXY[1].setXY(1, 1);
  pw.passwdXY[2].setXY(0, 1);
  myservo.attach(7);
  myservo.write(0);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {

 // put your main code here, to run repeatedly:
  /************* 압력센서 9개 선언 ************/
  fsr0 = analogRead(fsrSensor0); // A0로 부터 아날로그 신호를 읽고 이를 fsr0에 저장
  transFsr0 = map(fsr0, 0, 1024, 0, 255); // maapping 실시

  fsr1 = analogRead(fsrSensor1); // A1로 부터 아날로그 신호를 읽고 이를 fsr1에 저장
  transFsr1 = map(fsr1, 0, 1024, 0, 255); // maapping 실시

  fsr2 = analogRead(fsrSensor2); // A2로 부터 아날로그 신호를 읽고 이를 fsr2에 저장
  transFsr2 = map(fsr2, 0, 1024, 0, 255); // maapping 실시

  fsr3 = analogRead(fsrSensor3); // A3로 부터 아날로그 신호를 읽고 이를 fsr3에 저장
  transFsr3 = map(fsr3, 0, 1024, 0, 255); // maapping 실시

  fsr4 = analogRead(fsrSensor4); // A4로 부터 아날로그 신호를 읽고 이를 fsr4에 저장
  transFsr4 = map(fsr4, 0, 1024, 0, 255); // maapping 실시

  fsr5 = analogRead(fsrSensor5); // A5로 부터 아날로그 신호를 읽고 이를 fsr5에 저장
  transFsr5 = map(fsr5, 0, 1024, 0, 255); // maapping 실시

  fsr6 = analogRead(fsrSensor6); // A6로 부터 아날로그 신호를 읽고 이를 fsr6에 저장
  transFsr6 = map(fsr6, 0, 1024, 0, 255); // maapping 실시

  fsr7 = analogRead(fsrSensor7); // A7로 부터 아날로그 신호를 읽고 이를 fsr7에 저장
  transFsr7 = map(fsr7, 0, 1024, 0, 255); // maapping 실시

  fsr8 = analogRead(fsrSensor8); // A8로 부터 아날로그 신호를 읽고 이를 fsr8에 저장
  transFsr8 = map(fsr8, 0, 1024, 0, 255); // maapping 실시


  /////

  // 초음파를 보낸다. 다 보내면 echo가 HIGH 상태로 대기하게 된다.
  //digitalWrite(trigPin, LOW);
  //digitalWrite(echoPin, LOW);
  //delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);



  // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  unsigned long duration = pulseIn(echoPin, HIGH);
  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산 한다.
  float distance = ((float)(340 * duration) / 10000) / 2;
  Serial.println(distance);

  /************* 사용자가 3개의 패턴을 입력할때까지 압력센서로 입력을 받음 ************/

  if (distance < 90  || distance>= 810)
  {
    strip.setBrightness(bt);
    
    colorWipe(pwIndex);
    //Serial.println("사용자가 접근하였습니다.");
    if (pwIndex < 3)
    {

      if (transFsr0 > 10)
      {
        Serial.print("현재 ");
        Serial.print(pwIndex);
        Serial.println("번째 암호가 입력되었습니다.");
        Serial.println("0번");
        
        ptXY[pwIndex].setXY(0, 0);
        if (pwIndex != 0)
        {
          pwIndex += checkPrePoint(ptXY[pwIndex], ptXY[pwIndex - 1]);
        }
        pwIndex++;
      }

      if (transFsr1 > 10)
      {
        Serial.print("현재 ");
        Serial.print(pwIndex);
        Serial.println("번째 암호가 입력되었습니다.");
        Serial.println("1번");
        ptXY[pwIndex].setXY(1, 0);
        if (pwIndex != 0)
        {
          pwIndex += checkPrePoint(ptXY[pwIndex], ptXY[pwIndex - 1]);
        }
        pwIndex ++;
      }
      if (transFsr2 > 10)
      {
        Serial.print("현재 ");
        Serial.print(pwIndex);
        Serial.println("번째 암호가 입력되었습니다.");
        Serial.println("2번");
        ptXY[pwIndex].setXY(2, 0);
        if (pwIndex != 0)
        {
          pwIndex += checkPrePoint(ptXY[pwIndex], ptXY[pwIndex - 1]);
        }
        pwIndex ++;
      }
      if (transFsr3 > 10)
      {
        Serial.print("현재 ");
        Serial.print(pwIndex);
        Serial.println("번째 암호가 입력되었습니다.");
        Serial.println("3번");
        ptXY[pwIndex].setXY(0, 1);
        if (pwIndex != 0)
        {
          pwIndex += checkPrePoint(ptXY[pwIndex], ptXY[pwIndex - 1]);
        }
        pwIndex ++;
      }
      if (transFsr4 > 10)
      {
        Serial.print("현재 ");
        Serial.print(pwIndex);
        Serial.println("번째 암호가 입력되었습니다.");
        Serial.println("4번");
        ptXY[pwIndex].setXY(1, 1);
        if (pwIndex != 0)
        {
          pwIndex += checkPrePoint(ptXY[pwIndex], ptXY[pwIndex - 1]);
        }
        pwIndex ++;
      }
      if (transFsr5 > 10)
      {
        Serial.print("현재 ");
        Serial.print(pwIndex);
        Serial.println("번째 암호가 입력되었습니다.");
        Serial.println("5번");
        ptXY[pwIndex].setXY(2, 1);
        if (pwIndex != 0)
        {
          pwIndex += checkPrePoint(ptXY[pwIndex], ptXY[pwIndex - 1]);
        }
        pwIndex ++;
      }

      if (transFsr6 > 10)
      {
        Serial.print("현재 ");
        Serial.print(pwIndex);
        Serial.println("번째 암호가 입력되었습니다.");
        Serial.println("6번");
        ptXY[pwIndex].setXY(0, 2);
        if (pwIndex != 0)
        {
          pwIndex += checkPrePoint(ptXY[pwIndex], ptXY[pwIndex - 1]);
        }
        pwIndex ++;
      }
      if (transFsr7 > 10)
      {
        Serial.print("현재 ");
        Serial.print(pwIndex);
        Serial.println("번째 암호가 입력되었습니다.");
        Serial.println("7번");
        ptXY[pwIndex].setXY(1, 2);
        if (pwIndex != 0)
        {
          pwIndex += checkPrePoint(ptXY[pwIndex], ptXY[pwIndex - 1]);
        }
        pwIndex ++;
      }
      if (transFsr8 > 10)
      {
        Serial.print("현재 ");
        Serial.print(pwIndex);
        Serial.println("번째 암호가 입력되었습니다.");
        Serial.println("8번");
        ptXY[pwIndex].setXY(2, 2);
        if (pwIndex != 0)
        {
          pwIndex += checkPrePoint(ptXY[pwIndex], ptXY[pwIndex - 1]);
        }
        pwIndex ++;
      }
delay(30);
    }

    else if (pwIndex == 3)
    {
      Serial.println("입력된 비밀번호 입니다.");
      printPoint(ptXY);


      Serial.println("현재 비밀번호 입니다.");
      printPoint(pw.passwdXY);

      if (calArea(ptXY, pw.passwdXY) == 1 && calDiffPoint(ptXY, pw.passwdXY) == 1)
      {

        Serial.println("암호 일치\n");
        pwIndex = 0;
        myservo.write(90);
        openFlag = 1;
        delay(1000);

      }
      else {

        Serial.println("암호 불일치\n");
        pwIndex = 0;
        myservo.write(0);
        openFlag = 0;
        colorWipe(5);
        delay(1000);
      }
    }
  }

  else
  {
    colorWipe(4);
    // Serial.println("사용자 접근 대기중");
    if (openFlag == 1)
    {
      //Serial.println("현재 잠금 해제 상태입니다.");
      timer += 0.5;
      Serial.println(timer);
      if (timer > 3.0)
      {
        myservo.write(0);
        timer = 0;
        openFlag = 0;

      }
    }
    else {
      Serial.println("현재 잠금 상태입니다.");

    }
    bt = 0;
    delay(300);
  }


}

void colorWipe(int colorDate) {

  if (bt == 80)
  {
  }
  else {
    bt += 2;
  }

  if (colorDate == 0)
  {

    uint32_t color = strip.Color(0, 0, 255);

    strip.setPixelColor(0, color);
    strip.setPixelColor(1, color);
    strip.setPixelColor(2, color);
    strip.setPixelColor(3, color);
    strip.show();


  }

  else if (colorDate == 1)
  {
    uint32_t color = strip.Color(255, 100, 0);

    strip.setPixelColor(0, color);
    strip.setPixelColor(1, color);
    strip.setPixelColor(2, color);
    strip.setPixelColor(3, color);
    strip.show();

  }

  else if (colorDate == 2)
  {
    uint32_t color = strip.Color(255, 100, 100);
    strip.setPixelColor(0, color);
    strip.setPixelColor(1, color);
    strip.setPixelColor(2, color);
    strip.setPixelColor(3, color);
    strip.show();
    //delay(50);

  }
  else if (colorDate == 3)
  {
    uint32_t color = strip.Color(0, 255, 0);
    strip.setPixelColor(0, color);
    strip.setPixelColor(1, color);
    strip.setPixelColor(2, color);
    strip.setPixelColor(3, color);
    strip.show();
    //delay(50);

  }
  else if (colorDate == 4)
  {
    uint32_t color = strip.Color(0, 0, 0);
    strip.setPixelColor(0, color);
    strip.setPixelColor(1, color);
    strip.setPixelColor(2, color);
    strip.setPixelColor(3, color);
    strip.show();
    //delay(50);

  }
  else if (colorDate == 5)
  {
    uint32_t color = strip.Color(255, 0, 0);
    strip.setPixelColor(0, color);
    strip.setPixelColor(1, color);
    strip.setPixelColor(2, color);
    strip.setPixelColor(3, color);
    strip.show();
    //delay(50);

  }




}
