//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJ_UTILS_HPP_INCLUDED
#define NDJ_UTILS_HPP_INCLUDED

#include "ndj_exception.hpp"
#include <algorithm>
#include <iostream>

//------------------------------------------------------------------------------

namespace ndj {

//! Pi, you know what this number is already!
//! NB: Use floating point type!
template<typename T>
T
pi() 
{ return static_cast<T>(3.141592); }

//! Convert argument in degrees to radians. 
//! NB: Use floating point type!
template<typename T>
T
deg_to_rad(const T deg)
{ return deg*(pi<T>()/180); }

//! Convert argument in radians to degrees. 
//! NB: Use floating point type!
template<typename T>
T
rad_to_deg(const T rad)
{ return rad*(180/pi<T>()); }

//! Return value clamped to range [lower, upper].
//! [in] lower: lower bound.
//! [in] upper: upper bound.
//! [in]   val: value.
template<typename T>
T
clamp(const T lower, const T upper, const T val)
{ return (val < lower ? lower : (val > upper ? upper : val)); }

//------------------------------------------------------------------------------

//! Simple memcpy wrapper.
template<typename T, int N>
void
copy_vec(const T src[N], T dst[N])
{ std::copy(src, src + N, dst); }

//! Simple memcpy wrapper.
template<typename T>
void
copy_mat44(const T src[16], T dst[16])
{ std::copy(src, src + 16, dst); }

//! Dot product.
template<typename T, int N>
T
dot_vec(const T u[N], const T v[N])
{
    T sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += u[i]*v[i];
    }
    return sum; 
}

//! 3D cross product.
template<typename T> 
void
cross_vec3(const T u[3], const T v[3], T w[3])
{ 
    w[0] = u[1]*v[2] - u[2]*v[1];
    w[1] = u[2]*v[0] - u[0]*v[2];
    w[2] = u[0]*v[1] - u[1]*v[0];
}

//! Component-wise difference.
template<typename T, int N>
void
diff_vec(const T u[N], const T v[N], T w[N])
{
    for (int i = 0; i < N; ++i) {
        w[i] = u[i] - v[i];
    }
}

//! Distance between vectors.
template<typename T, int N>
T
dist_vec(const T u[N], const T v[N])
{
    T d[N];
    diff_vec<T,N>(u, v, d);
    return sqrt(d[0]*d[0] + d[1]*d[1] + d[2]*d[2]); // No checking!
}

//! Normalize.
template<typename T, int N>
void
norm_vec(const T u[N], T v[N])
{
    T mag2 = 0;
    for (int i = 0; i < N; ++i) {
        mag2 += u[i]*u[i];
    }
    const T inv_mag = 1/sqrt(mag2); // NB: No checking.
    for (int i = 0; i < N; ++i) {
        v[i] = inv_mag*u[i];
    }
}

//! Primitive low-level array matrix multiplication. Assumes matrices are 
//! stored in column major order (as OpenGL wants).
//! a: LHS.
//! b: RHS.
//! c: product.
template<typename T>
void
mult_mat44(const T a[16], const T b[16], T c[16])
{
    c[0]  = a[0]*b[0]  + a[4]*b[1]  + a[8]*b[2]   + a[12]*b[3];
    c[4]  = a[0]*b[4]  + a[4]*b[5]  + a[8]*b[6]   + a[12]*b[7];    
    c[8]  = a[0]*b[8]  + a[4]*b[9]  + a[8]*b[10]  + a[12]*b[11];
    c[12] = a[0]*b[12] + a[4]*b[13] + a[8]*b[14]  + a[12]*b[15];
    c[1]  = a[1]*b[0]  + a[5]*b[1]  + a[9]*b[2]   + a[13]*b[3];
    c[5]  = a[1]*b[4]  + a[5]*b[5]  + a[9]*b[6]   + a[13]*b[7];
    c[9]  = a[1]*b[8]  + a[5]*b[9]  + a[9]*b[10]  + a[13]*b[11];
    c[13] = a[1]*b[12] + a[5]*b[13] + a[9]*b[14]  + a[13]*b[15];
    c[2]  = a[2]*b[0]  + a[6]*b[1]  + a[10]*b[2]  + a[14]*b[3];
    c[6]  = a[2]*b[4]  + a[6]*b[5]  + a[10]*b[6]  + a[14]*b[7];
    c[10] = a[2]*b[8]  + a[6]*b[9]  + a[10]*b[10] + a[14]*b[11];
    c[14] = a[2]*b[12] + a[6]*b[13] + a[10]*b[14] + a[14]*b[15];
    c[3]  = a[3]*b[0]  + a[7]*b[1]  + a[11]*b[2]  + a[15]*b[3];
    c[7]  = a[3]*b[4]  + a[7]*b[5]  + a[11]*b[6]  + a[15]*b[7];
    c[11] = a[3]*b[8]  + a[7]*b[9]  + a[11]*b[10] + a[15]*b[11];
    c[15] = a[3]*b[12] + a[7]*b[13] + a[11]*b[14] + a[15]*b[15];
#if 0
    int j = 0;
    for (int i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j) {
            c[i*4+j] =
                a[i*4]*b[j]+a[i*4+1]*b[4+j]+a[i*4+2]*b[8+j]+a[i*4+3]*b[12+j];
        }
    }
#endif
}

//! Matrix / column vector multiplication. Assumes matrix is 
//! stored in column major order (as OpenGL wants).
//! v = A*u.
template<typename T>
void
mult_mat44_vec4(const T a[16], const T u[4], T v[4])
{
    v[0] = a[0]*u[0] + a[4]*u[1] + a[8]*u[2]  + a[12]*u[3];
    v[1] = a[1]*u[0] + a[5]*u[1] + a[9]*u[2]  + a[13]*u[3];
    v[2] = a[2]*u[0] + a[6]*u[1] + a[10]*u[2] + a[14]*u[3];
    v[3] = a[3]*u[0] + a[7]*u[1] + a[11]*u[2] + a[15]*u[3];

#if 0
    for (int i = 0; i < 4; ++i) {
        v[i] = a[i]*u[0] + a[4+i]*u[1] + a[8+i]*u[2] + a[12+i]*u[3];
    }
#endif
}

//! Invert 4x4 matrix. Throws if matrix is singular.
//! b = inv(a)
template<typename T>
void
invert_mat44(const T a[16], T b[16])
{
    b[0]  = a[5]*a[10]*a[15]  - a[5]*a[11]*a[14] - a[9]*a[6]*a[15] + 
            a[9]*a[7]*a[14]   + a[13]*a[6]*a[11] - a[13]*a[7]*a[10];
    b[4]  = -a[4]*a[10]*a[15] + a[4]*a[11]*a[14] + a[8]*a[6]*a[15] - 
            a[8]*a[7]*a[14]   - a[12]*a[6]*a[11] + a[12]*a[7]*a[10];
    b[8]  = a[4]*a[9]*a[15]   - a[4]*a[11]*a[13] - a[8]*a[5]*a[15] + 
            a[8]*a[7]*a[13]   + a[12]*a[5]*a[11] - a[12]*a[7]*a[9];
    b[12] = -a[4]*a[9]*a[14]  + a[4]*a[10]*a[13] + a[8]*a[5]*a[14] - 
            a[8]*a[6]*a[13]   - a[12]*a[5]*a[10] + a[12]*a[6]*a[9];
    b[1]  = -a[1]*a[10]*a[15] + a[1]*a[11]*a[14] + a[9]*a[2]*a[15] - 
            a[9]*a[3]*a[14]   - a[13]*a[2]*a[11] + a[13]*a[3]*a[10];
    b[5]  = a[0]*a[10]*a[15]  - a[0]*a[11]*a[14] - a[8]*a[2]*a[15] + 
            a[8]*a[3]*a[14]   + a[12]*a[2]*a[11] - a[12]*a[3]*a[10];
    b[9]  = -a[0]*a[9]*a[15]  + a[0]*a[11]*a[13] + a[8]*a[1]*a[15] - 
            a[8]*a[3]*a[13]   - a[12]*a[1]*a[11] + a[12]*a[3]*a[9];
    b[13] = a[0]*a[9]*a[14]   - a[0]*a[10]*a[13] - a[8]*a[1]*a[14] + 
            a[8]*a[2]*a[13]   + a[12]*a[1]*a[10] - a[12]*a[2]*a[9];
    b[2]  = a[1]*a[6]*a[15]   - a[1]*a[7]*a[14]  - a[5]*a[2]*a[15] + 
            a[5]*a[3]*a[14]   + a[13]*a[2]*a[7]  - a[13]*a[3]*a[6];
    b[6]  = -a[0]*a[6]*a[15]  + a[0]*a[7]*a[14]  + a[4]*a[2]*a[15] - 
            a[4]*a[3]*a[14]   - a[12]*a[2]*a[7]  + a[12]*a[3]*a[6];
    b[10] = a[0]*a[5]*a[15]   - a[0]*a[7]*a[13]  - a[4]*a[1]*a[15] + 
            a[4]*a[3]*a[13]   + a[12]*a[1]*a[7]  - a[12]*a[3]*a[5];
    b[14] = -a[0]*a[5]*a[14]  + a[0]*a[6]*a[13]  + a[4]*a[1]*a[14] - 
            a[4]*a[2]*a[13]   - a[12]*a[1]*a[6]  + a[12]*a[2]*a[5];
    b[3]  = -a[1]*a[6]*a[11]  + a[1]*a[7]*a[10]  + a[5]*a[2]*a[11] - 
            a[5]*a[3]*a[10]   - a[9]*a[2]*a[7]   + a[9]*a[3]*a[6];
    b[7]  = a[0]*a[6]*a[11]   - a[0]*a[7]*a[10]  - a[4]*a[2]*a[11] + 
            a[4]*a[3]*a[10]   + a[8]*a[2]*a[7]   - a[8]*a[3]*a[6];
    b[11] = -a[0]*a[5]*a[11]  + a[0]*a[7]*a[9]   + a[4]*a[1]*a[11] - 
            a[4]*a[3]*a[9]    - a[8]*a[1]*a[7]   + a[8]*a[3]*a[5];
    b[15] = a[0]*a[5]*a[10]   - a[0]*a[6]*a[9]   - a[4]*a[1]*a[10] + 
            a[4]*a[2]*a[9]    + a[8]*a[1]*a[6]   - a[8]*a[2]*a[5];
    const T det = a[0]*b[0] + a[1]*b[4] + a[2]*b[8] + a[3]*b[12];
    if (0 == det) {
        NDJINN_THROW("invert_mat44: cannot invert singular matrix");
    }
    const T inv_det = 1/det;
    for (int i = 0; i < 16; ++i) {
        b[i] *= inv_det;
    }
}

//------------------------------------------------------------------------------

//! Make a translation matrix.
template<typename T>
void
translate_mat44(const T t0, const T t1, const T t2, T m[16])
{
    m[0] = 1; m[4] = 0; m[8]  = 0; m[12] = t0;
    m[1] = 0; m[5] = 1; m[9]  = 0; m[13] = t1;
    m[2] = 0; m[6] = 0; m[10] = 1; m[14] = t2;
    m[3] = 0; m[7] = 0; m[11] = 0; m[15] = 1;
}

//! Make a x-rotation matrix.
template<typename T>
void
rotate_x_mat44(const T r0_deg)
{
    const T r0_rad = deg_to_rad(r0_deg);
    const T s0 = sin(r0_rad);
    const T c0 = cos(r0_rad);
    m[0] = 1; m[4] = 0;  m[8]  =  0;  m[12] = 0;
    m[1] = 0; m[5] = c0; m[9]  = -s0; m[13] = 0;
    m[2] = 0; m[6] = s0; m[10] =  c0; m[14] = 0;
    m[3] = 0; m[7] = 0;  m[11] =  0;  m[15] = 1;
}

//! Make a y-rotation matrix.
template<typename T>
void
rotate_y_mat44(const T r1_deg)
{
    const T r1_rad = deg_to_rad(r1_deg);
    const T s1 = sin(r1_rad);
    const T c1 = cos(r1_rad);
    m[0] =  c1; m[4] = 0; m[8]  = s1; m[12] = 0;
    m[1] =  0;  m[5] = 1; m[9]  = 0;  m[13] = 0;
    m[2] = -s1; m[6] = 0; m[10] = c1; m[14] = 0;
    m[3] =  0;  m[7] = 0; m[11] = 0;  m[15] = 1;
}

//! Make a z-rotation matrix.
template<typename T>
void
rotate_z_mat44(const T r2_deg)
{
    const T r2_rad = deg_to_rad(r2_deg);
    const T s2 = sin(r2_rad);
    const T c2 = cos(r2_rad);
    m[0] = c2; m[4] = -s2; m[8]  = 0; m[12] = 0;
    m[1] = s2; m[5] =  c2; m[9]  = 0; m[13] = 0;
    m[2] = 0;  m[6] =  0;  m[10] = 1; m[14] = 0;
    m[3] = 0;  m[7] =  0;  m[11] = 0; m[15] = 1;
}

//! Make a rotation matrix. Order xyz is hard-coded.
//! [in]  r0_rad: x rotation.
//! [in]  r1_rad; y rotation.
//! [in]  r2_rad: z rotation.
//! [out]      m: xyz rotation matrix.
template<typename T>
void
rotate_xyz_mat44(const T r0_rad, const T r1_rad, const T r2_rad, T m[16])
{
    const T s0 = sin(r0_rad);
    const T s1 = sin(r1_rad);
    const T s2 = sin(r2_rad);
    const T c0 = cos(r0_rad);
    const T c1 = cos(r1_rad);
    const T c2 = cos(r2_rad);
    m[0] = c1*c2;          m[4] = -c1*s2;          m[8]  =  s1;    m[12] = 0;
    m[1] = s0*s1*c2+c0*s2; m[5] =  c0*c2-s0*s1*s2; m[9]  = -s0*c1; m[13] = 0;
    m[2] = s0*s2-c0*s1*c2; m[6] =  c0*s1*s2+s0*c2; m[10] =  c0*c1; m[14] = 0;
    m[3] = 0;              m[7] =  0;              m[11] =  0;     m[15] = 1;
}

//! Make a scale matrix.
template<typename T>
void
scale_mat44(const T s0, const T s1, const T s2, T m[16])
{
    m[0] = s0; m[4] = 0;  m[8]  = 0;  m[12] = 0;
    m[1] = 0;  m[5] = s1; m[9]  = 0;  m[13] = 0;
    m[2] = 0;  m[6] = 0;  m[10] = s2; m[14] = 0;
    m[3] = 0;  m[7] = 0;  m[11] = 0;  m[15] = 1;
}

//------------------------------------------------------------------------------

//! Make a camera view matrix.
//! [in]      t: world space position.
//! [in]  r_deg: rotation in [degrees].
//! [in]      s: scale.
//! [out]  view: camera view matrix.
template<typename T>
void
cam_view(const T t[3], const T r_deg[3], const T s[3], T view[16])
{
    T sxf[16];
    scale_mat44(s[0], s[1], s[2], sxf);
    T rxf[16];
    rotate_xyz_mat44(
        -deg_to_rad(r_deg[0]), 
        -deg_to_rad(r_deg[1]), 
        -deg_to_rad(r_deg[2]), 
        rxf);
    T txf[16];
    translate_mat44(-t[0], -t[1], -t[2], txf);
    T tmp[16];
    mult_mat44(sxf, rxf, tmp);
    mult_mat44(tmp, txf, view);
}

//! Create camera view matrix from right, up, back, and world space position.
//! [in]     r: right direction.
//! [in]     u: up direction.
//! [in]     b: back direction.
//! [in]     t: world space position.
//! [out] view: camera view matrix.
template <typename T>
void
cam_view(const T r[3], const T u[3], const T b[3], const T t[3], T v[16])
{
    v[0] = r[0]; v[4] = r[1]; v[8]  = r[2]; v[12] = -dot_vec<T,3>(t, r);
    v[1] = u[0]; v[5] = u[1]; v[9]  = u[2]; v[13] = -dot_vec<T,3>(t, u);
    v[2] = b[0]; v[6] = b[1]; v[10] = b[2]; v[14] = -dot_vec<T,3>(t, b);
    v[3] = 0;    v[7] = 0;    v[11] = 0;    v[15] = 1;
}

//! Construct camera view from arguments similar to those used in gluLookAt.
//! [in]     t: world space position.
//! [in]     c: point to look at.
//! [in]     u: world up vector, typically [0 1 0].
//! [out] view: camera view matrix.
template <typename T>
void
cam_view_lookat(const T t[3], const T c[3], const T u[3], T view[16])
{
    T diff[3];
    diff_vec<T,3>(t, c, diff);
    T back[3];
    norm_vec<T,3>(diff, back);
    T rx[3];
    cross_vec3<T>(u, back, rx);
    T right[3];
    norm_vec<T,3>(rx, right);
    T up[3];
    cross_vec3<T>(back, right, up);
    cam_view(right, up, back, t, view);
}

//! Camera local +X axis. First row of view rotation. Points right
//! with respect to forward direction.
//! [in]   view: camera view matrix.
//! [out] right: camera local right vector.
template<typename T>
void
view_right(const T view[16], T right[3])
{
    right[0] = view[0];
    right[1] = view[4];
    right[2] = view[8];
}

//! Camera local +Y axis. Second row of modelview rotation.
//! [in]  view: camera view matrix.
//! [out]   up: camera local up vector.
template<typename T>
static void
view_up(const T view[16], T up[3])
{
    up[0] = view[1];
    up[1] = view[5];
    up[2] = view[9];
}

//! Camera local +Z axis. Note that this is not the view direction.
//! In fact, the view direction is exactly opposite this vector (i.e.
//! all components sign-flipped). Third row of modelview rotation.
//! [in]  view: camera view matrix.
//! [out] back: camera local back vector.
template<typename T>
void
view_back(const T view[16], T back[3])
{
    back[0] = view[2];
    back[1] = view[6];
    back[2] = view[10];
}

//! Camera local -Z axis. Corresponds to view direction.
//! view: camera view matrix.
//! [in]  view: camera view matrix.
//! [out]  fwd: camera local forward vector.
template<typename T>
void
view_fwd(const T view[16], T fwd[3])
{ 
    fwd[0] = -view[2];
    fwd[1] = -view[6];
    fwd[2] = -view[10];
}        

//! Extract camera local coordinate system.
//! [in] view: camera view matrix.
//! [out] r: camera local right vector.
//! [out] u: camera local up vector.
//! [out] b: camera local back vector.
template<typename T>
void
view_axes(const T view[16], T r[3], T u[3], T b[3])
{
    r[0] = view[0]; r[1] = view[4]; r[2] = view[8];
    u[0] = view[1]; u[1] = view[5]; u[2] = view[9];
    b[0] = view[2]; b[1] = view[6]; b[2] = view[10];
}

//! Compute normal matrix from view matrix.
//! [in]  view: camera view matrix.
//! [out]   nm: normal matrix.
template<typename T>
void
normal_matrix(const T view[16], T nm[9])
{
}

//------------------------------------------------------------------------------

//! Make a perspective projection matrix. Taken from Eric Lengyel's 
//! excellent GDC 2007 presentation entitled "Projection Matrix Tricks".
//!
//! NB: T should be a floating point type.
//! TODO: Check input validity, n < f, a != 0, e > 0,  etc.
//! [in]  e: focal length. [unit?]
//! [in]  a: viewport aspect. (height/width)
//! [in]  n: near clip plane distance.
//! [in]  f: far clip plane distance.
//! [out] p: projection matrix.
template<typename T>
static void
perspective_projection(const T e, const T a, const T n, const T f, T p[16])
{
    const T inv_fmn = 1/(f-n);
    p[0] = e; p[4] = 0;   p[8]  = 0;              p[12] = 0;
    p[1] = 0; p[5] = e/a; p[9]  = 0;              p[13] = 0;
    p[2] = 0; p[6] = 0;   p[10] = -(f+n)*inv_fmn; p[14] = -(2*f*n)*inv_fmn;
    p[3] = 0; p[7] = 0;   p[11] = -1;             p[15] = 0;
}

//! Make a perspective projection matrix, see documentation for glFrustum.
//! NB: T should be a floating point type.
//! TODO: Check input validity, left < right, bottom < top, etc.
template<typename T>
static void
perspective_projection(const T left,    
                       const T right,
                       const T bottom, 
                       const T top,
                       const T near_val,
                       const T far_val,
                       T       p[16])
{
    const T inv_rml = 1/(right - left);
    const T inv_tmb = 1/(top - bottom);
    const T inv_fmn = 1/(far_val - near_val);
    const T a =  (right + left)*inv_rml;
    const T b =  (top + bottom)*inv_tmb;
    const T c = -(far_val + near_val)*inv_fmn;
    const T d = -(2*far_val*near_val)*inv_fmn;
    p[0] = 2*near_val*inv_rml; p[4] = 0;                  p[8]  =  a; p[12] = 0;
    p[1] = 0;                  p[5] = 2*near_val*inv_tmb; p[9]  =  b; p[13] = 0;
    p[2] = 0;                  p[6] = 0;                  p[10] =  c; p[14] = d;
    p[3] = 0;                  p[7] = 0;                  p[11] = -1; p[15] = 0;
}

//! Make an orthographics projection matrix, see documentation for glOrtho.
//! NB: T should be a floating point type.
//! TODO: Check input validity, left < right, bottom < top, etc.
template<typename T>
static void
orthographic_projection(const T left,
                        const T right,
                        const T bottom,
                        const T top,
                        const T near_val,
                        const T far_val,
                        T       p[16])
{
    const T inv_rml = 1/(right - left);
    const T inv_tmb = 1/(top - bottom);
    const T inv_fmn = 1/(far_val - near_val);
    const T tx = -(right + left)*inv_rml;
    const T ty = -(top + bottom)*inv_tmb;
    const T tz = -(far_val + near_val)*inv_fmn;
    p[0] = 2*inv_rml; p[4] = 0;         p[8]  = 0;           p[12] = tx;
    p[1] = 0;         p[5] = 2*inv_tmb; p[9]  = 0;           p[13] = ty;
    p[2] = 0;         p[6] = 0;         p[10] = -2*inv_fmn;  p[14] = tz;
    p[3] = 0;         p[7] = 0;         p[11] = 0;           p[15] = 1;
}

//------------------------------------------------------------------------------

//! Project an object space vector into window space. May throw.
//! [in]   obj: vector in object space.
//! [in] model: model matrix.
//! [in]  view: view matrix.
//! [in]  proj: projection matrix.
//! [in]    vp: viewport dimension. [as from glGetIntegerv(GL_VIEWPORT)]
//! [out]  win: vector in window coordinates.
//! [in]     n: near depth range. [as from glGetDoublev(GL_DEPTH_RANGE)]
//! [in]     f: far depth range. [as from glGetDoublev(GL_DEPTH_RANGE)]
template<typename T>
void
project(const T     obj[3], 
        const T     model[16],
        const T     view[16],
        const T     proj[16],
        const GLint vp[4],
        T           win[3],
        const T     n = 0,
        const T     f = 1)
{
    const T objw[] = { obj[0], obj[1], obj[2], 1 };
    T wsx[4];    // World-space.
    mult_mat44_vec4(model, objw, wsx);
    T esx[4];    // Eye-space.
    mult_mat44_vec4(view, wsx, esx);
    T csx[4];    // Clip-space.
    mult_mat44_vec4(proj, esx, csx);
    T ndc[3];
    ndc_coordinates(csx, ndc);  // May throw.
    window_coordinates(vp, ndc, win, n, f);
}

//! Project an object space vector into window space. May throw.
//! [in]  obj: vector in object space.
//! [in]  pvm: projection*view*model matrix.
//! [in]   vp: viewport dimensions. [as from glGetIntegerv(GL_VIEWPORT)]
//! [out] win: vector in window coordinates.
//! [in]    n: near depth range. [as from glGetDoublev(GL_DEPTH_RANGE)]
//! [in]    f: far depth range. [as from glGetDoublev(GL_DEPTH_RANGE)]
template<typename T>
void
project(const T     obj[3],
        const T     pvm[16],
        const GLint vp[4],
        T           win[3],
        const T     n = 0,
        const T     f = 1)
{
    const T objw[] = { obj[0], obj[1], obj[2], 1 };
    T csx[4];
    mult_mat44_vec4(pvm, objw, csx);    // Straight to clip space!
    T ndc[3];
    ndc_coordinates(csx, ndc);          // May throw.
    window_coordinates(vp, ndc, win, n, f);
}

//! Compute an object space vector from window coordinates. May throw.
//! [in]    win: window space vector.
//! [in]     vp: viewport dimensions. [as from glGetIntegerv(GL_VIEWPORT)]
//! [in]   proj: projection matrix.
//! [in]   view: view matrix.
//! [in]  model: view matrix.
//! [out]   obj: object space vector.
//! [in]      n: near depth range. [as from glGetDoublev(GL_DEPTH_RANGE)]
//! [in]      f: far depth range. [as from glGetDoublev(GL_DEPTH_RANGE)]
template<typename T>
void
unproject(const T        win[3],
          const GLint    vp[4],
          const T        proj[16],
          const T        view[16],
          const T        model[16],
          T              obj[3],
          const GLdouble n = 0,
          const GLdouble f = 1)
{
    T pv[16];
    mult_mat44(proj, view, pv);
    T pvm[16];
    mult_mat44(pv, model, pvm);
    T inv_pvm[16];
    invert_mat44(pvm, inv_pvm);              // May throw.
    unproject(win, vp, inv_pvm, obj, n, f);  // May throw.

}

//! Compute a world space vector from window coordinates. May throw.
//! [in]   win: window space vector.
//! [in]    vp: viewport dimensions. [as from glGetIntegerv(GL_VIEWPORT)]
//! [in]  proj: projection matrix.
//! [in]  view: view matrix.
//! [out]  wsx: world space vector.
//! [in]     n: near depth range. [as from glGetDoublev(GL_DEPTH_RANGE)]
//! [in]     f: far depth range. [as from glGetDoublev(GL_DEPTH_RANGE)]
template<typename T>
void
unproject(const T        win[3],
          const GLint    vp[4],
          const T        proj[16],
          const T        view[16],
          T              wsx[3],
          const GLdouble n = 0,
          const GLdouble f = 1)
{
    T pv[16];
    mult_mat44(proj, view, pv);
    T inv_pv[16];
    invert_mat44(pv, inv_pv);               // May throw.
    unproject(win, vp, inv_pv, wsx, n, f);  // May throw.
}

//! Compute a world space or object space vector from window coordinates, 
//! depending on the provided inv_ndc matrix. May throw.
//! inv_ndc = inverse(projection*view) --> world space.
//! inv_ndc = inverse(projection*view*model) --> object space.
//! [in]      win: window space vector.
//! [in]       vp: viewport dimensions. [as from glGetIntegerv(GL_VIEWPORT)]
//! [in]  inv_ndc: inverse transformation from NDC.
//! [out]       v: world space or object space vector.
//! [in]        n: near depth range. [as from glGetDoublev(GL_DEPTH_RANGE)]
//! [in]        f: far depth range. [as from glGetDoublev(GL_DEPTH_RANGE)]
template<typename T>
void
unproject(const T        win[3],
          const GLint    vp[4],
          const T        inv_ndc[16],
          T              v[3],
          const GLdouble n = 0,
          const GLdouble f = 1)
{
    const T ndc4[] = {
        static_cast<T>(((win[0] - vp[0])/vp[2])*2 - 1),
        static_cast<T>(((win[1] - vp[1])/vp[3])*2 - 1),
        static_cast<T>((2*win[2] - (f + n))/(f - n)),
        static_cast<T>(1)
    };
    T wsx4[4];
    mult_mat44_vec4(inv_ndc, ndc4, wsx4);
    if (0.f == wsx4[3]) {
        NDJINN_THROW("unproject: divide-by-zero");
    }
    const T inv_w = 1/wsx4[3];
    v[0] = wsx4[0]*inv_w;
    v[1] = wsx4[1]*inv_w;
    v[2] = wsx4[2]*inv_w;
}

//! Compute a world space ray from camera and viewport info. May throw.
//! [in]    px: pixel x-coordinate.
//! [in]    py: pixel y-coordinate.
//! [in]    vp: viewport [as from glGetIntegerv(GL_VIEWPORT)]
//! [in]  proj: projection matrix.
//! [in]  view: view matrix.
//! [out]  ori: ray origin.
//! [out]  dir: ray direction (normalized).
//! [in]     n: near depth range. [as from glGetDoublev(GL_DEPTH_RANGE)]
//! [in]     f: far depth range. [as from glGetDoublev(GL_DEPTH_RANGE)]
template<typename T>
void
pixel_ray(const int      px,
          const int      py,
          const GLint    vp[4], 
          const T        proj[16],
          const T        view[16],
          T              ori[3], 
          T              dir[3],
          const GLdouble n = 0,
          const GLdouble f = 1)
{
    T pv[16];
    mult_mat44(proj, view, pv);
    T inv_pv[16];
    invert_mat44(pv, inv_pv);                       // May throw.
    pixel_ray(px, py, vp, inv_pv, ori, dir, n, f);  // May throw.
}

//! Compute a world space ray from camera and viewport info. May throw.
//! [in]      px: pixel x-coordinate.
//! [in]      py: pixel y-coordinate.
//! [in]      vp: viewport. [as from glGetIntegerv(GL_VIEWPORT)]
//! [in]  inv_pv: inverse(projection*view) matrix.
//! [out]    ori: ray origin.
//! [out]    dir: ray direction (normalized).
//! [in]       n: near depth range. [as from glGetDoublev(GL_DEPTH_RANGE)]
//! [in]       f: far depth range. [as from glGetDoublev(GL_DEPTH_RANGE)]
template<typename T>
void
pixel_ray(const int      px,
          const int      py,
          const GLint    vp[4], 
          const T        inv_pv[16],
          T              ori[3], 
          T              dir[3],
          const GLdouble n = 0,
          const GLdouble f = 1)
{
    const T win_near[] = { 
        static_cast<T>(px), 
        static_cast<T>(py), 
        static_cast<T>(n) 
    };
    const T win_far[] = { 
        static_cast<T>(px), 
        static_cast<T>(py), 
        static_cast<T>(f) 
    };
    T wsx_near[3];
    T wsx_far[3];
    unproject(win_near, vp, inv_pv, wsx_near, n, f); // May throw.
    unproject(win_far, vp, inv_pv, wsx_far, n, f);  // May throw.
    copy_vec<T,3>(wsx_near, ori);
    T wsx_diff[3];
    diff_vec<T,3>(wsx_far, wsx_near, wsx_diff);
    norm_vec<T,3>(wsx_diff, dir);
}

//! Compute NDC coordinates from clip space coordinates. May throw.
//! [in]  csx: clip space vector.
//! [out] ndc: NDC vector.
template<typename T>
void
ndc_coordinates(const T csx[4], T ndc[3])
{
    if (csx[3] == 0) {
        NDJINN_THROW("ndc_coordinates: perspective divide-by-zero");
    }
    const T inv_w = 1/csx[3];
    ndc[0] = csx[0]*inv_w;
    ndc[1] = csx[1]*inv_w;
    ndc[2] = csx[2]*inv_w;
}

//! Compute window coordinates given NDC coordinates and viewport info.
//! [in]   vp: viewport parameters. [as from glGetIntegerv(GL_VIEWPORT)]
//! [in]  ndc: normalized device coordinates.
//! [out] win: window coordinates.
//! [in]    n: near depth range. [as from glGetDoublev(GL_DEPTH_RANGE)]
//! [in]    f: far depth range. [as from glGetDoublev(GL_DEPTH_RANGE)]
template<typename T>
void
window_coordinates(const GLint    vp[4], 
                   const T        ndc[3],
                   T              win[3],
                   const GLdouble n = 0, 
                   const GLdouble f = 1) throw()
{
    win[0] = (0.5*ndc[0] + 0.5)*vp[2] + vp[0];
    win[1] = (0.5*ndc[1] + 0.5)*vp[3] + vp[1];
    win[2] = 0.5*(f - n)*ndc[2] + 0.5*(f + n);
}

//------------------------------------------------------------------------------

template<typename T>
void
ray_plane_intersect(const T ray_ori[3],
                    const T ray_dir[3],
                    const T plane_ori[3],
                    const T plane_nml[3],
                    T       isect[3])
{
    const T denom = dot_vec<T,3>(plane_nml, ray_dir);
    if (denom == 0) {
        NDJINN_THROW("ray_plane_intersect: tangent ray");
    }
    const T d = 
        -plane_nml[0]*plane_ori[0]
        -plane_nml[1]*plane_ori[1]
        -plane_nml[2]*plane_ori[2];
    const T num = dot_vec<T,3>(plane_nml, ray_ori) + d;
    const T ratio = num/denom;
    isect[0] = ray_ori[0] - ratio*ray_dir[0];
    isect[1] = ray_ori[1] - ratio*ray_dir[1];
    isect[2] = ray_ori[2] - ratio*ray_dir[2];

#if 1
    std::cerr << "isect: [" 
        << isect[0] << ", " << isect[1] << ", " << isect[2] << "]\n";
#endif
}

//------------------------------------------------------------------------------

//! Compute Euler angles from a rotation matrix, assumes
//! XYZ rotation order. Angles are given in radians.
//! [in]  xfr: rotation matrix (xyz order)
//! [out]   r: Euler angles in [radians].
template <typename T>
void
euler_angles_xyz(const T xfr[16], T r[3])
{
    r[0] = atan2(-xfr[9], xfr[10]);
    r[1] = asin(xfr[8]);
    r[2] = atan2(-xfr[4], xfr[0]);
}

//------------------------------------------------------------------------------

}   // Namespace: ndj.

//------------------------------------------------------------------------------

#endif  // NDJ_UTILS_HPP_INCLUDED
