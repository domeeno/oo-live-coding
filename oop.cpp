#include <iostream>

struct Pos {
  // center
  float x;
  float y;
};

class Circle {
private:
  Pos pos;

  // radius
  float r;

public:
  Circle(float inx, float iny, float inr) : r(inr) {
    pos = Pos{inx, iny};
  }

  void print() {
    std::cout << "x: " << this->pos.x << "y: " << this->pos.y << "\n";
    std::cout << "r: " << this->r << "\n";
  }

  bool collide(Circle &other) {
    float dx = this->pos.x - other.getX();
    float dy = this->pos.y - other.getY();

    float distanceSquared = dx * dx + dy * dy;

    float radiusSum = this->r + other.r;

    float radiusSquared = radiusSum * radiusSum;

    return radiusSquared > distanceSquared;
  }

  void respawn() {
    r = 1;
    pos.x = 100;
    pos.y = 100;
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
  
  // getters
  float getX() {
    return pos.x;
  };
  float getY() {
    return pos.y;
  };
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
