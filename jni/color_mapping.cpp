/*
* Color Mapping methods.
* Author: felhr (felhr85@gmail.com)
* 
* Some functions to perform different types of "color mapping" of the 16bit grayscale depth signal to 8bit RGB
* Maximum and minumum depth values of Asus Xtion Pro and Kinect(1): 800mm - 4000mm
* 
*/
#include <stddef.h>
#include <math.h>
#include "color_mapping.h"

unsigned int depth_min = 800;
unsigned int depth_max = 4000;

float simple_mapping(unsigned int* depth_value)
{
	float mapped_value = *depth_value * 255.0 / depth_max;
	return mapped_value;
}

float normalized_mapping(unsigned int* depth_value)
{

	float mapped_value = 255.0 *((*depth_value - depth_min)/(depth_max - depth_min));
	return mapped_value;

}

float two_section_mapping(unsigned int* depth_value, unsigned int depth2, unsigned int precision)
{
	if(depth2 <= depth_max)
	{
		if(precision != 0)
		{
			float max_color = (depth2 - depth_min) / precision;
			if(max_color >= 1 && max_color < 255.0)
			{
				if(*depth_value <= depth2)
				{
					float mapped_value = ((*depth_value - depth_min) * (max_color - 1)) / (depth2 - depth_min);
					return mapped_value;
				}else
				{
					float mapped_value = (((*depth_value - depth2 - 1 ) * (255.0 - max_color)) / (depth_max - depth2 - 1)) + max_color;
					return mapped_value;
				}
			}else
			{
				return NULL;
			}
		}else
		{
			return NULL;
		}
	}else
	{
		return NULL;
	}
}

float log_mapping_base10(unsigned int* depth_value)
{
	double b = 0.0028125;
	double c = -1.25;
	double rect = *depth_value * b + c;

	if(rect < 1.0)
	{
		rect = 1.0;
	}else if(rect > 10.0)
	{
		rect = 10.0;
	}

	return (float) 255.0 * log10(rect);
}
