#include <unistd.h>
#include <gquickdraw.h>
#include "math.hxx"

void draw_quad(const Math::Quad& quad)
{
  gd_draw_line((int)quad.a.x, (int)quad.a.y, 
               (int)quad.b.x, (int)quad.b.y);

  gd_draw_line((int)quad.b.x, (int)quad.b.y, 
               (int)quad.c.x, (int)quad.c.y);

  gd_draw_line((int)quad.c.x, (int)quad.c.y, 
               (int)quad.d.x, (int)quad.d.y);

  gd_draw_line((int)quad.a.x, (int)quad.a.y, 
               (int)quad.d.x, (int)quad.d.y);
}

int main()
{
  srand(time(NULL));

  Math::Quad a;
  Math::Quad b;
  
  gd_init_screen(640, 480, true);

  while (1)
    {
      gd_clear_screen();

      a.a.x = rand()%640;
      a.a.y = rand()%480;

      a.b.x = rand()%640;
      a.b.y = rand()%480;

      a.c.x = rand()%640;
      a.c.y = rand()%480;

      a.d.x = rand()%640;
      a.d.y = rand()%480;

      b.a.x = rand()%640;
      b.a.y = rand()%480;

      b.b.x = rand()%640;
      b.b.y = rand()%480;

      b.c.x = rand()%640;
      b.c.y = rand()%480;

      b.d.x = rand()%640;
      b.d.y = rand()%480;
  
      if (Math::quad_collide(a, b))
        gd_draw_rect(0, 0, 50, 50, true);
  
      draw_quad(a);
      draw_quad(b);

      gd_flip_screen();
      
      do{
          gd_process_events();
          usleep(1000);
        }
      while(gd_get_mouse_button(1) == false);
    }
}

/* EOF */
