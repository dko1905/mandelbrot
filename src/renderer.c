#include "canvas.h"
#include "renderer.h"
#include "hsv.h"
#include "colormode.h"

#include <errno.h>
#include <stdio.h>
#include <strings.h>

#ifdef __unix__
#include <unistd.h>
#include <pthread.h>
#endif

int rendertocanvas(rendercanvas_t *canvas, colormode_t colormode, double x_offset, double y_offset, double scale, size_t step_max){
  int status;
  double x, y;
  _Complex double point, z;
  size_t steps;
  pixel_t *pixel;

  status = 0;

  for(size_t num_y = 0; num_y < canvas->height; ++num_y){
    y = (double)num_y / scale - (double)canvas->height / 2. / scale + x_offset;

    for(size_t num_x = 0; num_x < canvas->width; ++num_x){
      x = (double)num_x / scale - (double)canvas->width / 2. / scale + x_offset;
    
      point = x + y * I;
      z = 0. + 0.i;
      steps = 0;

      while(cabs(z) < 2.0 && steps < step_max){
        z = z * z + point;

        ++steps;
      }

      if(steps < step_max){
        pixel = pixel_at(canvas, num_x, num_y);
				if(colormode == BLACKANDWHITE){
					pixel->red = 255;
					pixel->green = 255;
					pixel->blue = 255;
				}
				else if(colormode == HSV_1){
					HSVtoRGB((steps * 10) % 255, 1, 1, pixel);
				}
      } 
      else{
        pixel_t *pixel = pixel_at(canvas, num_x, num_y);
        if(colormode == BLACKANDWHITE){
          pixel->red = 0;
					pixel->green = 0;
					pixel->blue = 0;
        } 
        else if(colormode == HSV_1){
          pixel->red = 0;
					pixel->green = 0;
					pixel->blue = 0;
        }
      }
    }
  }

  return status;
}


#ifdef __unix__

struct renderfunc_param{
  rendercanvas_t *canvas;
  colormode_t colormode;
  double x_offset, y_offset;
  double scale;
  size_t step_max;
  int spid;
  int nupid;
};

void *renderfunc(void *raw_params){
  struct renderfunc_param *params = (struct renderfunc_param*)raw_params;

  rendercanvas_t *canvas = params->canvas;
  double x_offset = params->x_offset;
  double y_offset = params->y_offset;
  double scale = params->scale;
  size_t step_max = params->step_max;
  colormode_t colormode = params->colormode;

  for(size_t num_y = 0 + params->spid; num_y < canvas->height; num_y += params->nupid){
    double x, y;
    _Complex double point, z;
    size_t steps;
    pixel_t *pixel;

    y = (double)num_y / scale - (double)canvas->height / 2. / scale + x_offset;

    for(size_t num_x = 0; num_x < canvas->width; ++num_x){
      x = (double)num_x / scale - (double)canvas->width / 2. / scale + x_offset;
    
      point = x + y * I;
      z = 0. + 0.i;
      steps = 0;

      while(cabs(z) < 2.0 && steps < step_max){
        z = z * z + point;

        ++steps;
      }

      if(steps < step_max){
        pixel = pixel_at(canvas, num_x, num_y);
				if(colormode == BLACKANDWHITE){
					pixel->red = 255;
					pixel->green = 255;
					pixel->blue = 255;
				}
				else if(colormode == HSV_1){
					HSVtoRGB((steps * 10) % 255, 1, 1, pixel);
				}
      } 
      else{
        pixel_t *pixel = pixel_at(canvas, num_x, num_y);
        if(colormode == BLACKANDWHITE){
          pixel->red = 0;
					pixel->green = 0;
					pixel->blue = 0;
        } 
        else if(colormode == HSV_1){
          pixel->red = 0;
					pixel->green = 0;
					pixel->blue = 0;
        }
      }
    }
  }
}

int rendertocanvas_multithread(rendercanvas_t *canvas, colormode_t colormode, double x_offset, double y_offset, double scale, size_t step_max, size_t thread_n){
  struct renderfunc_param standard_params = {
    canvas: canvas,
    colormode: colormode,
    x_offset: x_offset,
    y_offset: y_offset,
    scale: scale,
    step_max: step_max,
    spid: 0,
    nupid: 0
  };

  pthread_t *pthreads = malloc(sizeof(pthread_t) * thread_n);
  struct renderfunc_param *custom_params_arr = malloc(sizeof(struct renderfunc_param) * thread_n);

  for(size_t tc = 0; tc < thread_n; ++tc){
    struct renderfunc_param *custom_params = &custom_params_arr[tc];
    bcopy(&standard_params, custom_params, sizeof(struct renderfunc_param));

    custom_params->spid = tc;
    custom_params->nupid = thread_n;

    int cr = pthread_create(&pthreads[tc], NULL, renderfunc, (void *) custom_params);
    if(cr < 0){
      perror("Failed to create pthread, exiting");
      return -1;
    }
  }

  for(size_t tc = 0; tc < thread_n; ++tc){
    int jr = pthread_join(pthreads[tc], NULL);
    if(jr < 0){
      perror("Failed to join pthread, continuing");
    }
  }

  free(custom_params_arr);

  return 0;
}

#endif