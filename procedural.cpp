#include <iostream>

struct Circle {
  // center
  float x;
  float y;

  // radius
  float r;
};

void printCircle(Circle &c) {
  std::cout << "x: " << c.x << "y: " << c.y << "\n";
  std::cout << "r: " << c.r << "\n";
}

bool collide(Circle &a, Circle &b) {
  float dx = a.x - b.x;
  float dy = a.y - b.y;

  float distanceSquared = dx * dx + dy * dy;

  float radiusSum = a.r + b.r;

  float radiusSquared = radiusSum * radiusSum;

  return radiusSquared > distanceSquared;
}

void respawn(Circle &c) {
  c.r = 1;
  c.x = 100;
  c.y = 100;
}

void consume(Circle &winner, Circle &dinner) {
  if (winner.r < dinner.r) {
    return;
  }
  if (collide(winner, dinner)) {
    winner.r += dinner.r;

    respawn(dinner);
  }
}

int main(int argc, char *argv[]) {
  Circle c1{195, 194, 40};
  Circle c2{204, 204, 20};

  printCircle(c1);
  printCircle(c2);

  consume(c1, c2);

  printCircle(c1);
  printCircle(c2);

  return 0;
}
