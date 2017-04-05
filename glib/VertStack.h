#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
template <typename T>
struct VertStackCell
{
     double a = 0.0;
     T v = T();
};
template <typename T, size_t S = 9>
struct VertStack
{
private:
     int top = S;
     VertStackCell<T> cells[S];
     double getTa(double dy, double dx)
     {
          return dy / dx;
     }
public:
     int size() const
     {
          return S-top;
     }
     VertStackCell<T>& get(int i)
     {
          if (i >= size() || i < 0)
               throw("fatal Error:", __FUNCSIG__);
          return cells[top+i];
     }
     void push(const T& v, const double& a)
     {
          int i = --top;
          cells[i].a = a;
          cells[i].v = v;
     }
     void pop()
     {
          top++;
     }
     void swap(int f, int s)
     {
          if (f == s)
               return;
          std::swap(get(f).a, get(s).a);
          std::swap(get(f).v, get(s).v);
     }
     void sort()
     {
          int first = 0;
          for (int i = 1; i < size(); i++)
          {
               if (get(first).v.x_ > get(i).v.x_)
                    first = i;
               else if ((get(first).v.x_ == get(i).v.x_)&& (get(first).v.y_ > get(i).v.y_))
                    first = i;
          }
          swap(0, first);
          for (int i = 1; i < size(); i++)
          {
               get(i).a = getTa(static_cast<double>(get(i).v.y_ - get(0).v.y_), static_cast<double>(get(i).v.x_ - get(0).v.x_));
          }
          for (int i = 1; i < size(); i++)
          {
               int loc_max = i;
               for (int j = i+1; j < size(); j++)
               {
                    if (get(j).a > get(loc_max).a)
                         loc_max = j;
               }
               swap(i, loc_max);
          }
     }
};
