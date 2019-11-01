
/*************return 값을 2개 받기 위해 구조체 생성 ************/
struct values{

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
    values getXY(){
        v.px = this->x;
        v.py = this->y;
        return v;
    }

};
/*************비밀번호 클래스 ************/
class passwd {

  private:
    float area;

  public:

    pointXY passwdXY1;
    pointXY passwdXY2;
    pointXY passwdXY3;

    void setArea(float area) {
      this->area = area;
    }

    float test() {
      return area;
    }

};

/*************이전 좌표와 현재 좌표가 중복인지 확인 ************/
int checkPrePoint(pointXY tptXY, pointXY pretptXY) {

  if ((tptXY.getX() == pretptXY.getX()) &&
      (tptXY.getY() == pretptXY.getY()))
  {

    return -1;

  }
  else
    return 0;
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

void setup() {
/*************초기 암호 설정(2,4,5) ************/
  pw.setArea(0.5);
  pw.passwdXY1.setXY(1, 0);
  pw.passwdXY2.setXY(0, -1);
  pw.passwdXY3.setXY(1, 1);

}

void loop() {
  // put your main code here, to run repeatedly:

  /************* 압력센서 9개 선언 ************/
  int fsr0 = analogRead(fsrSensor0); // A0로 부터 아날로그 신호를 읽고 이를 fsr0에 저장
  int transFsr0 = map(fsr0, 0, 1024, 0, 255); // maapping 실시

  int fsr1 = analogRead(fsrSensor1); // A1로 부터 아날로그 신호를 읽고 이를 fsr1에 저장
  int transFsr1 = map(fsr1, 0, 1024, 0, 255); // maapping 실시

  int fsr2 = analogRead(fsrSensor2); // A2로 부터 아날로그 신호를 읽고 이를 fsr2에 저장
  int transFsr2 = map(fsr2, 0, 1024, 0, 255); // maapping 실시

  int fsr3 = analogRead(fsrSensor3); // A3로 부터 아날로그 신호를 읽고 이를 fsr3에 저장
  int transFsr3 = map(fsr3, 0, 1024, 0, 255); // maapping 실시

  int fsr4 = analogRead(fsrSensor4); // A4로 부터 아날로그 신호를 읽고 이를 fsr4에 저장
  int transFsr4 = map(fsr4, 0, 1024, 0, 255); // maapping 실시

  int fsr5 = analogRead(fsrSensor5); // A5로 부터 아날로그 신호를 읽고 이를 fsr5에 저장
  int transFsr5 = map(fsr5, 0, 1024, 0, 255); // maapping 실시

  int fsr6 = analogRead(fsrSensor6); // A6로 부터 아날로그 신호를 읽고 이를 fsr6에 저장
  int transFsr6 = map(fsr6, 0, 1024, 0, 255); // maapping 실시

  int fsr7 = analogRead(fsrSensor7); // A7로 부터 아날로그 신호를 읽고 이를 fsr7에 저장
  int transFsr7 = map(fsr7, 0, 1024, 0, 255); // maapping 실시

  int fsr8 = analogRead(fsrSensor8); // A8로 부터 아날로그 신호를 읽고 이를 fsr8에 저장
  int transFsr8 = map(fsr8, 0, 1024, 0, 255); // maapping 실시

  if (transFsr0 > 6)
  {
    ptXY[pwIndex].setXY(0, 0);
    if (pwIndex != 0)
    {
      pwIndex += checkPrePoint(ptXY[pwIndex], ptXY[pwIndex - 1]);
    }
    pwIndex++;
  }
  if (transFsr1 > 6)
  {
    ptXY[pwIndex].setXY(1, 0);
    if (pwIndex != 0)
    {
      pwIndex += checkPrePoint(ptXY[pwIndex], ptXY[pwIndex - 1]);
    }
    pwIndex ++;
  }
  if (transFsr2 > 6)
  {
    ptXY[pwIndex].setXY(2, 0);
    if (pwIndex != 0)
    {
      pwIndex += checkPrePoint(ptXY[pwIndex], ptXY[pwIndex - 1]);
    }
    pwIndex ++;
  }
  if (transFsr3 > 6)
  {
    ptXY[pwIndex].setXY(0, 1);
    if (pwIndex != 0)
    {
      pwIndex += checkPrePoint(ptXY[pwIndex], ptXY[pwIndex - 1]);
    }
    pwIndex ++;
  }
  if (transFsr4 > 6)
  {
    ptXY[pwIndex].setXY(1, 1);
    if (pwIndex != 0)
    {
      pwIndex += checkPrePoint(ptXY[pwIndex], ptXY[pwIndex - 1]);
    }
    pwIndex ++;
  }
  if (transFsr5 > 6)
  {
    ptXY[pwIndex].setXY(2, 1);
    if (pwIndex != 0)
    {
      pwIndex += checkPrePoint(ptXY[pwIndex], ptXY[pwIndex - 1]);
    }
    pwIndex ++;
  }
  if (transFsr6 > 6)
  {
    ptXY[pwIndex].setXY(0, 2);
    if (pwIndex != 0)
    {
      pwIndex += checkPrePoint(ptXY[pwIndex], ptXY[pwIndex - 1]);
    }
    pwIndex ++;
  }
  if (transFsr7 > 6)
  {
    ptXY[pwIndex].setXY(1, 2);
    if (pwIndex != 0)
    {
      pwIndex += checkPrePoint(ptXY[pwIndex], ptXY[pwIndex - 1]);
    }
    pwIndex ++;
  }
  if (transFsr8 > 6)
  {
    ptXY[pwIndex].setXY(2, 2);
    if (pwIndex != 0)
    {
      pwIndex += checkPrePoint(ptXY[pwIndex], ptXY[pwIndex - 1]);
    }
    pwIndex ++;
  }




}
