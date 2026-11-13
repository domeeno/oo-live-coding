#include <iostream>

class Circle {
private:
  // origin 
  float x;
  float y;

  // radius
  float r;

public:
  Circle(float inx, float iny, float inr) : x(inx), y(iny), r(inr) {}

  void print() {
    std::cout << "x: " << this->x << "y: " << this->y << "\n";
    std::cout << "r: " << this->r << "\n";
  }

  bool collide(Circle &other) {
    float dx = this->x - other.x;
    float dy = this->y - other.y;

    float distanceSquared = dx * dx + dy * dy;

    float radiusSum = this->r + other.r;

    float radiusSquared = radiusSum * radiusSum;

    return radiusSquared > distanceSquared;
  }

  void respawn() {
    r = 1;
    x = 100;
    y = 100;
  }

  void consume(Circle &dinner) {
    if (r < dinner.r) {
      return;
    }
    if (this->collide(dinner)) {
      r += dinner.r;

      dinner.respawn();
    }
  }
};

int main(int argc, char *argv[]) {
  Circle c1{195, 194, 40};
  Circle c2{204, 204, 20};
  Circle c3{25, 11, 20};


  c1.print();
  c2.print();
  c3.print();

  c1.consume(c2);

  c1.print();
  c2.print();
  return 0;
}
