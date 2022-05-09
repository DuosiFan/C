#include <stdlib.h>
#include <stdio.h>

struct point_tag {
  int x;
  int y;
};

typedef struct point_tag point_t;

struct polygon_tag {
  size_t num_points;
  point_t * points;
};
typedef struct polygon_tag polygon_t;

polygon_t *make_rectangle(point_t c1, point_t c2);

int main(void) {
  point_t c1 = {.x = 0, .y = 0};
  point_t c2 = {.x = 1, .y = 1};

  polygon_t * rect = make_rectangle(c1, c2);
  for (size_t i = 0; i < rect->num_points; ++i)
    printf("(%d, %d)\n", rect->points[i].x, rect->points[i].y);

  free(rect->points);
  free(rect);
  return 0;
}

polygon_t *make_rectangle(point_t c1, point_t c2) {
  polygon_t * rect = malloc(sizeof(*rect));
  rect->num_points = 4;
  rect->points = malloc(rect->num_points*sizeof(*(rect->points)));

  rect->points[0] = c1;
  rect->points[1].x = c1.x;
  rect->points[1].y = c2.y;
  rect->points[2] = c2;
  rect->points[3].x = c2.x;
  rect->points[3].y = c1.y;
  
  return rect;
}




