#include <unistd.h>
#include <gquickdraw.h>
#include "math.hxx"

int main()
{
  srand(time(NULL));

  float x1 = rand()%640;
  float y1 = rand()%480;

  float x2 = rand()%640;
  float y2 = rand()%480;

  float x3 = rand()%640;
  float y3 = rand()%480;

  gd_init_screen(640, 480, true);

  while (1)
    {
      gd_clear_screen();
      if (Math::point_inside_triangle(gd_get_mouse_x(), gd_get_mouse_y(), 
                                      x1, y1, x2, y2, x3, y3))
        gd_draw_rect(0, 0, 50, 50, true);
      
      if (Math::lines_intersect(x2, y2, x3, y3,
                                0, 0, gd_get_mouse_x(), gd_get_mouse_y()))
        gd_draw_rect(590, 0, 50, 50, true);
      
      gd_draw_line(0, 0, gd_get_mouse_x(), gd_get_mouse_y());

      gd_set_fg_color(0xFFFFFF);
      gd_draw_line((int)x1, (int)y1, (int)x2, (int)y2);
      gd_set_fg_color(0xFF00F);
      gd_draw_line((int)x2, (int)y2, (int)x3, (int)y3);
      gd_set_fg_color(0xFFFFFF);
      gd_draw_line((int)x3, (int)y3, (int)x1, (int)y1);

      gd_flip_screen();

      gd_process_events();
      usleep(1000);
    }
}

/* EOF */

