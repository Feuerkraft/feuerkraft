//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include <argp.h>
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <png.h>

const char *argp_program_version = "Feuerkraft TileGen Version 0.0.0";
const char *argp_program_bug_address = "<grumbel@gmail.com>";

static char doc[] = "Feuerkraft TileGen";
     
static struct argp_option options[] = {
  {"verbose",  'v', 0,      0,  "Produce verbose output" },
  {"quiet",    'q', 0,      0,  "Don't produce any output" },
  {"output",   'o', "FILE", 0,  "Output to FILE instead of standard output" },
  {"rot90",    'r', 0,      0,  "Rotate mask by 90 degrees" },
  {"rot180",   'u', 0,      0,  "Rotate mask by 180 degrees" },
  {"rot270",   'l', 0,      0,  "Rotate mask by 270 degrees" },
  {"flip",     'f', 0,      0,  "Flip image" },
  { 0 }
};

struct arguments {
  bool flip;
  enum { ROT0, ROT90, ROT180, ROT270 } rotate;
  char* mask_file;
  char* layer1_file;
  char* layer2_file;
  char* output_file;
};

error_t
parse_option(int key, char *arg, struct argp_state *state)
{
  struct arguments* args = static_cast<arguments*>(state->input);

  switch (key)
    {
    case ARGP_KEY_ARG:
      if (state->arg_num == 0)
        args->mask_file = arg;
      else if (state->arg_num == 1)
        args->layer1_file = arg;
      else if (state->arg_num == 2)
        args->layer2_file = arg;
      else
        return ARGP_ERR_UNKNOWN;
      break;

    case ARGP_KEY_ARGS:
      //std::cout << "Arguments: " << key << " " << (int)arg  << std::endl;
      break;

    case ARGP_KEY_NO_ARGS:
      //std::cout << "no arguments" << std::endl;
      break;

    case ARGP_KEY_END:
      if (args->mask_file == 0
          || args->layer1_file == 0
          || args->layer2_file == 0)
        argp_usage(state);
      break;
      
    case ARGP_KEY_INIT:
      //std::cout << "Init" << std::endl;
      break;

    case ARGP_KEY_FINI:
      //std::cout << "Fini" << std::endl;
      break;

    case ARGP_KEY_SUCCESS:
      //std::cout << "Success" << std::endl;
      break;

    case ARGP_KEY_ERROR:
      std::cout << "ERROR" << std::endl;
      break;

    case 'f':
      args->flip = true;
      break;

    case 'r':
      args->rotate = arguments::ROT90;
      break;

    case 'u':
      args->rotate = arguments::ROT180;
      break;

    case 'l':
      args->rotate = arguments::ROT270;
      break;

    case 'o':
      args->output_file = arg;
      break;

    default:
      std::cout << "Unknown Key: " << (char)key << " Arg: " << (int)arg << " State: " << state << std::endl;
      break;
    }
  return 0;
}

static struct argp argp = { options, parse_option, "MASK LAYER1 LAYER2", doc, 0, 0 };

class Color
{
public:
  int red;
  int green;
  int blue;

  Color ()
    : red (0), green (255), blue (0)
  {
  }

  Color (int r, int g, int b) 
    : red (r), green (g), blue (b)
  {    
  }
};

class Image
{
private:
  int m_width;
  int m_height;
  int row_bytes;

  std::vector<unsigned char> m_image;
  
public:
  Image (const Image& image)
    : m_width(image.m_width),
      m_height(image.m_height),
      row_bytes(image.row_bytes),
      m_image(image.m_image)
  {
  }

  /** Load an image from a given png source */
  Image (const std::string& filename) 
  {
    FILE* fp;
    png_structp png_ptr;
    png_infop info_ptr;
    png_uint_32 pwidth, pheight;
    int bit_depth, color_type, interlace_type, compression_type, filter_type;

    if ((fp = fopen(filename.c_str (), "rb")) == NULL)
      {
	perror (filename.c_str ());
	exit (EXIT_FAILURE);
      }

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
				     NULL, NULL, NULL);
    info_ptr = png_create_info_struct(png_ptr);
    png_init_io(png_ptr, fp);
    png_read_info(png_ptr, info_ptr);
    png_get_IHDR(png_ptr, info_ptr, &pwidth, &pheight,
		 &bit_depth, &color_type, &interlace_type,
		 &compression_type, &filter_type);
    row_bytes = png_get_rowbytes(png_ptr, info_ptr);

    std::cout << "BitDepth:    " << bit_depth << "\n"
              << "Colortype:   " << color_type << "\n"
              << "Interlace:   " << interlace_type << "\n"
              << "Filter Type: " << filter_type << "\n"
              << "Row Bytes:   " << row_bytes << "\n"
              << "Width:       " << pwidth << "\n"
              << "Height:      " << pheight << "\n"
              << std::endl;

    // Create the 'data' array
    png_bytep row_pointers[pheight];
    for (unsigned int i = 0; i < pheight; ++i)
      row_pointers[i] = new png_byte[row_bytes];

    png_read_image(png_ptr, row_pointers);
    
    if (color_type != PNG_COLOR_TYPE_RGB)
      {
        std::cout << "Unsupported color type" << std::endl;
        exit (EXIT_FAILURE);
      }

    m_width  = pwidth;
    m_height = pheight;

    m_image.resize (m_height * row_bytes);

    // Convert the png into our internal data structure
    for (int y = 0; y < m_height; ++y)
      for (int i = 0; i < row_bytes; ++i)
        {
          m_image[i + (row_bytes * y)] = row_pointers[y][i];
        }
	  
    png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
    fclose (fp);
  }
  
  ~Image () 
  {
  }

  void write_pnm(std::string filename)
  {
    FILE* fp;
    fp = fopen(filename.c_str (), "wb");
    if (fp == NULL)
      assert (false);

    fprintf(fp, "P3\n# CREATOR\n");
    fprintf(fp, "%d %d\n", m_width, m_height);
    fprintf(fp, "255\n");

    for (unsigned int i = 0; i < m_image.size (); ++i)
      fprintf(fp, "%d\n", m_image[i]);

    fclose(fp);
  }

  void write_png_file(std::string filename)
  {
    FILE* fp;
    fp = fopen(filename.c_str (), "wb");
    if (fp == NULL)
      assert (false);

    write_png(fp);

    fclose(fp);
  }

  void write_png (FILE* fp)
  {
    png_structp png_ptr;
    png_infop info_ptr;

    png_ptr  = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    info_ptr = png_create_info_struct(png_ptr);

    png_init_io(png_ptr, fp);

    png_set_IHDR(png_ptr, info_ptr, 
                 m_width, m_height, 8 /* bitdepth */,
                 PNG_COLOR_TYPE_RGB,
                 PNG_INTERLACE_NONE, 
                 PNG_COMPRESSION_TYPE_BASE, 
                 PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);

    png_uint_32 height = m_height;

    png_byte image[height * row_bytes];
    png_bytep row_pointers[height];
   
    // fill the image with data
    for (unsigned int i = 0; i < m_image.size (); ++i)
      image[i] = m_image[i];
    
    // generate row pointers
    for (unsigned int k = 0; k < height; k++)
      row_pointers[k] = image + (k * row_bytes);

    png_write_image(png_ptr, row_pointers);

    png_write_end(png_ptr, info_ptr);
  }

  void add_overlay(Image& mask, Image& image)
  {
    for (int y = 0; y < m_height; ++y)
      for (int x = 0; x < row_bytes; ++x)
        {
          int i = (y * row_bytes) + x;
          float alpha = (mask.m_image[i]/255.0);
          int new_color = int((m_image[i] * (1.0f - alpha)) + (image.m_image[i] * alpha));
          m_image[i] = new_color > 255 ? 255 : new_color;
        }
  }

  void rotate_90()
  {
    Image image(*this);
    
    for (int y = 0; y < m_height; ++y)
      for (int x = 0; x < m_width; ++x)
        {
          m_image[(y * row_bytes) + 3*x + 0] = image.m_image[((m_height - x - 1) * row_bytes) + 3*y + 0];
          m_image[(y * row_bytes) + 3*x + 1] = image.m_image[((m_height - x - 1) * row_bytes) + 3*y + 1];
          m_image[(y * row_bytes) + 3*x + 2] = image.m_image[((m_height - x - 1) * row_bytes) + 3*y + 2];
        }
  }

  void flip()
  {
    Image image(*this);
    
    for (int y = 0; y < m_height; ++y)
      for (int x = 0; x < m_width; ++x)
        {
          m_image[(y * row_bytes) + 3*x + 0] = image.m_image[((m_height - y - 1) * row_bytes) + 3*x + 0];
          m_image[(y * row_bytes) + 3*x + 1] = image.m_image[((m_height - y - 1) * row_bytes) + 3*x + 1];
          m_image[(y * row_bytes) + 3*x + 2] = image.m_image[((m_height - y - 1) * row_bytes) + 3*x + 2];
        }
  }
};

int main (int argc, char* argv[])
{
  struct arguments args;

  args.flip   = false;
  args.rotate = arguments::ROT0;
  args.mask_file = 0;
  args.layer1_file = 0;
  args.layer2_file = 0;
  args.output_file = 0;

  argp_parse (&argp, argc, argv, 0, 0, &args);

  std::cout << "Loading..." << std::endl;
  Image mask  (args.mask_file);
  Image layer1(args.layer1_file);
  Image layer2(args.layer2_file);
  std::cout << "Loading... done" << std::endl;
  std::cout << "writing png" << std::endl;

  if (args.flip)
    mask.flip();

  switch (args.rotate)
    {
    case arguments::ROT0:
      break;

    case arguments::ROT90:
      mask.rotate_90();
      break;

    case arguments::ROT180:
      mask.rotate_90();
      mask.rotate_90();
      break;
      
    case arguments::ROT270:
      mask.rotate_90();
      mask.rotate_90();
      mask.rotate_90();
      break;
    }

  layer1.add_overlay(mask, layer2);

  if (args.output_file)
    layer1.write_png_file(args.output_file);
  else
    layer1.write_png(stdout);
}


// EOF //
