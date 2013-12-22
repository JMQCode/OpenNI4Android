/*
* Color Mapping methods.
* Author: felhr (felhr85@gmail.com)
* 
* Some functions to perform different types of "color mapping" of the 16bit grayscale depth signal to 8bit RGB
* Maximum and minimum depth values of Asus Xtion Pro and Kinect(1): 800mm - 4000mm
* 
*/

#ifndef _Included_color_mapping
#define _Included_color_mapping

extern unsigned int depth_min;
extern unsigned int depth_max;

/*
* The simplest mapping, It was default when I started to dig into this.
* output = (depth*255)/4000
*/
float simple_mapping(unsigned int* depth_value);

/*
* Normalized mapping allows mapping in the whole 8bit range
* output = (d - depthMin)/(depthMax - depthMin) * 255
*/
float normalized_mapping(unsigned int* depth_value);

/*
* Two section mapping can apply a more accurate mapping to a subset of depthValues
* depth1 is fixed to 800.
* Return NULL if wrong
*/
float two_section_mapping(unsigned int* depth_value, unsigned int depth2, unsigned int precision);

/*
* Log mapping with base 10
* output = 255 * log10(0.00281d - 1.25)
*/
float log_mapping_base10(unsigned int* depth_value);

#endif
