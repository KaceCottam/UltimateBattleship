#pragma once
/*
 * Since this is a very simple data type, we can declare it as a struct, which is
 * inherently public.
 * This can be initialized by using what is called "uniform initialization", example:
 * Coordinate coord { 10, 10 };
 * Notice the braces!
 */

struct Coordinate {
  int x, y;
};