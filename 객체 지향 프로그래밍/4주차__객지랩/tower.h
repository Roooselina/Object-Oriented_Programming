#ifndef TOWER_H //같은 헤더 중복 호출 방지
#define TOWER_H

class Tower {
private:
    int height;

public:
    Tower();               // 기본 생성자
    Tower(int h);          // 매개변수가 있는 생성자
    int getHeight();       
    void setHeight(int h); 
};
#endif 