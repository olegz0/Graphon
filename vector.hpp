#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

#include "matrix.hpp"

//class Vector3f;

typedef struct {unsigned char b, g, r, a;} color_t;
const color_t col_red    = {0,   0,   255, 0};
const color_t col_green  = {0,   255, 0,   0};
const color_t col_blue   = {255, 0,   0,   0};

const color_t col_white  = {255, 255, 255, 0};
const color_t col_black  = {0,   0,   0,   0};

const color_t col_yellow = {0,   255, 255, 0};

/*
class Color
{
    color_t col_;
public:
    Color(color_t col)
    : col_(col)
    { }
    
    color_t getColor(void) const {
        return col_;
    }
    
    void operator*=(const Vector3f &v) {
        
    }
    
    void operator*=(float k) {
        col_.r *= k;
        col_.g *= k;
        col_.b *= k;
    }
};
*/

class Vector3f
{
    float x_, y_, z_;
    color_t col_;
public:
    Vector3f()
    : x_(0)
    , y_(0)
    , z_(0)
    { }
    
    Vector3f(float x, float y, float z, color_t col = col_white)
    : x_(x)
    , y_(y)
    , z_(z)
    , col_(col)
    { }
    
    Vector3f(float arr[3])
    {
        for(int i = 0; i < 3; i++)
            (*this)[i] = arr[i];
    }
    
    float getX() const { return x_; }
    float getY() const { return y_; }
    float getZ() const { return z_; }
    color_t getColor() const { return col_; }
    
    void Init(float arr[3]) {
        for(int i = 0; i < 3; i++)
            (*this)[i] = arr[i];
    }
    
    void Init(float x, float y, float z) { x_ = x; y_ = y; z_ = z; }
    
    void setColor(color_t col) { col_ = col; }
    
    void Move(float x, float y, float z) { x_ += x; y_ += y; z_ += z; }
    
    float len() {
        return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
    }
    
    float &operator[](int i) {
        switch (i) {
        case 0:  return x_;
        case 1:  return y_;
        case 2:  return z_;
        default: break;
        }
        throw("index out of range");
    }
    
    float operator[](int i) const {
        switch (i) {
        case 0:  return x_;
        case 1:  return y_;
        case 2:  return z_;
        default: break;
        }
        throw("index out of range");
    }
    
    float     len       (void)              const { return           sqrt( x_ * x_ + y_ * y_ + z_ * z_);  }
    float     scal      (const Vector3f &v) const { return                 x_*v.x_ + y_*v.y_ + z_*v.z_;   }
    Vector3f &operator +(const Vector3f &v) const { return *(new Vector3f( x_+v.x_,  y_+v.y_,  z_+v.z_)); }
    Vector3f &operator -(const Vector3f &v) const { return *(new Vector3f( x_-v.x_,  y_-v.y_,  z_-v.z_)); }
    Vector3f &operator -(void)              const { return *(new Vector3f(-x_,      -y_,      -z_     )); }
    Vector3f &operator /(float k)           const { return *(new Vector3f( x_/k,     y_/k,     z_/k   )); }
    Vector3f &operator *(float k)           const { return *(new Vector3f( x_*k,     y_*k,     z_*k   )); }
    void      operator+=(const Vector3f &v)       { x_ += v.x_; y_ += v.y_; z_ += v.z_; }
    void      operator-=(const Vector3f &v)       { x_ -= v.x_; y_ -= v.y_; z_ -= v.z_; }
    void      operator/=(float k)                 { x_ /= k;    y_ /= k;    z_ /= k;    }
    
    Vector3f &operator*(const Matrix3f &m) const {
        Vector3f *res = new Vector3f(*this);
        (*res) *= m;
        return *res;
    }
    
    void operator*=(const Matrix3f &m) {
        float tmp[3] = {x_, y_, z_};
        this->Init(0, 0, 0);
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                (*this)[i] += m[i][j] * tmp[j];
    }
    
    Vector3f &operator*(const Vector3f &v) {
        Vector3f *res = new Vector3f(0, 0, 0);
        for (int i = 0; i < 3; i++)
            (*res)[i] = (*this)[(i + 1) % 3] * v[(i + 2) % 3] - (*this)[(i + 2) % 3] * v[(i + 1) % 3];
        return *res;
    }
};

#endif // VECTOR_H_INCLUDED
