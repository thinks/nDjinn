//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_CAMERA_HPP_INCLUDED
#define NDJINN_CAMERA_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnException.hpp"
#include "nDjinnError.hpp"
#include <gl/glew.h>
//#include "ndj_utils.hpp"
#include <algorithm>
#include <cmath>

// -----------------------------------------------------------------------------

BEGIN_NDJINN_NAMESPACE

//! Camera class.
template<typename T>
class Camera
{
public:    

    typedef T value_type;

public:

    //! CTOR.
    explicit
    Camera(const T focal_length        = 35,
           const T horizontal_aperture = 1.417,
           const T vertical_aperture   = 0.945,
           const T near_clip           = 1, 
           const T far_clip            = 100,
           const T aspect              = 1)
        : _focal_length(focal_length)
        , _horizontal_aperture(horizontal_aperture)
        , _vertical_aperture(vertical_aperture)
        , _near_clip(near_clip)
        , _far_clip(far_clip)
        , _aspect(aspect)
    {
        _translate[0] = 0;
        _translate[1] = 0;
        _translate[2] = 0;
        _rotate_deg[0] = 0;
        _rotate_deg[1] = 0;
        _rotate_deg[2] = 0;
        _scale[0] = 0;
        _scale[1] = 0;
        _scale[2] = 0;
        _orbit_radius = 1;

        _set_view();
        _set_perspective_projection();
    }


    //! CTOR.
    explicit
    camera(const T translate[3], 
           const T rotate[3],
           const T scale[3],
           const T focal_length        = 35,
           const T horizontal_aperture = 1.417,
           const T vertical_aperture   = 0.945,
           const T near_clip           = 1, 
           const T far_clip            = 100
           const T aspect              = 1)
        : _focal_length(focal_length)
        , _horizontal_aperture(horizontal_aperture)
        , _vertical_aperture(vertical_aperture)
        , _near_clip(near_clip)
        , _far_clip(far_clip)
        , _aspect(aspect)
    {
        copy_vec3(translate, _translate);
        copy_vec3(rotate,    _rotate);
        copy_vec3(scale,     _scale);

        cam_view(_translate, _rotate, _scale, _view);
        _set_perspective_projection(
            _aperture_aspect(_horizontal_aperture, _vertical_aperture));
    }

    //! Copy CTOR.
    camera(const camera<T> &rhs) 
        : _orbit_radius(rhs._orbit_radius)
        , _focal_length(rhs._focal_length)
        , _horizontal_aperture(rhs._horizontal_aperture)
        , _vertical_aperture(rhs._vertical_aperture)
        , _near_clip(rhs._near_clip)
        , _far_clip(rhs._far_clip)
        , _aspect(rhs.aspect)
    {
        copy_mat44(rhs._view, _view);
        copy_mat44(rhs._proj, _proj);
        copy_vec3(rhs._translate, _translate);
        copy_vec3(rhs._rotate,    _rotate);
        copy_vec3(rhs._scale,     _scale);
    }

    //! DTOR. NB: Not virtual!
    ~camera()
    {}

    //! Assign.
    camera<T>&
    operator=(const camera<T> &rhs)
    {
        copy_mat44(rhs._view, _view);
        copy_mat44(rhs._proj, _proj);
        copy_vec3(rhs._translate, _translate);
        copy_vec3(rhs._rotate, _rotate);
        copy_vec3(rhs._scale, _scale);
        _orbit_radius = rhs._orbit_radius;
        _focal_length = rhs._focal_length;
        _horizontal_aperture = rhs._horizontal_aperture;
        _vertical_aperture = rhs._vertical_aperture;
        _near_clip = rhs._near_clip;
        _far_clip = rhs._far_clip;
        _aspect = rhs._aspect;
        return *this;
    }

    //! Return view matrix, in column-major array.
    const T*
    view() const
    { return _view; }

    //! Return projection matrix, in column-major array.
    const T*
    projection() const
    { return _proj; }

public:     // View.

    //! World space position.
    const T*
    translate() const
    { return _translate; }

    //! Return camera rotation in degrees.
    const T*
    rotate() const
    { return _rotate; }

    //! Return camera scale.
    const T*
    scale() const
    { return _scale; }

    //! Return orbit radius, which is the distance to the pivot.
    T
    orbit_radius() const
    { return _orbit_radius; }

    //! Set camera world space position.
    void
    set_translate(const T t[3])
    {
        copy_vec<T,3>(t, _translate);
        cam_view(_translate, _rotate, _scale, _view);
    }

    //! Set rotation part of view transformation.
    void
    set_rotate(const T r[3])
    {
        copy_vec<T,3>(r, _rotate);
        cam_view(_translate, _rotate, _scale, _view);
    }

    //! Set scale part of view transformation.
    void
    set_scale(const T s[3])
    {
        copy_vec<T,3>(s, _scale);
        cam_view(_translate, _rotate, _scale, _view);
    }

    //! Set view parameters with a single call, updating the view matrix only
    //! once.
    void
    set_view(const T t[3], const T r_deg[3], const T s[3])
    {
        copy_vec<T,3>(t, _translate);
        copy_vec<T,3>(r_deg, _rotate_deg);
        copy_vec<T,3>(s, _scale);
        cam_view(_translate, _rotate_deg, _scale, _view);
    }

    //! Moves pivot, not camera. Use dolly() to move camera.
    void
    set_orbit_radius(const T r)
    { _orbit_radius = std::max<T>(2*_near_clip, r); }

public:     // Projection.

    //! Return focal length in [mm].
    T 
    focal_length() const
    { return _focal_length; }

    //! Return horizontal aperture in [inch].
    T
    horizontal_aperture() const
    { return _horizontal_aperture; }

    //! Return vertical aperture in [inch].
    T 
    vertical_aperture() const
    { return _vertical_aperture; }

    //! Return near clipping distance.
    T 
    near_clip() const 
    { return _near_clip; }

    //! Return far clipping distance.
    T 
    far_clip() const
    { return _far_clip; }

    //! Set focal length in [mm].
    //! TODO: Check negative?
    //! aspect: viewport height/width.
    void
    set_focal_length(const T focal_length, const T aspect)
    {
        _focal_length = focal_length;
        _set_perspective_projection();
    }

    //! Set aperture dimensions.
    //! [in]      h: horizontal aperture [inch]
    //! [in]      v: vertical aperture [inch]
    void
    set_apertures(const T ha, const T va)
    {
        _horizontal_aperture = ha;
        _vertical_aperture = va;
        _set_perspective_projection(aspect);
    }

    //! Set clipping distances.
    //! [in]      n: near clipping distance.
    //! [in]      f: far clipping distance.
    void
    set_clip(const T n, const T f)
    {
        _near_clip = std::min<T>(n, f);
        _far_clip = std::max<T>(n, f);
        _set_perspective_projection();
    }

    //! Set projection aspect.
    //! [in] aspect: viewport height/width.
    void
    set_aspect(const T aspect)
    { 
        _aspect = aspect;
        _set_perspective_projection(); 
    }

public:

    //! Move camera in local xy-plane.
    //! [in] dr: distance to move in right direction.
    //! [in] du: distance to move in up direction.
    void
    track(const T dr, const T du)
    {
        T right[3];
        view_right(_view, right);
        T up[3];
        view_up(_view, up);
        _translate[0] += dr*right[0] + du*up[0];
        _translate[1] += dr*right[1] + du*up[1];
        _translate[2] += dr*right[2] + du*up[2];
        cam_view(_translate, _rotate_deg, _scale, _view);
    }

    //! Move camera along fwd/back direction without changing pivot position.
    //! [in]  dr: amount to change orbit radius. 
    void
    dolly(const T dr) 
    {
        T back[3];
        view_back(_view, back);
        T piv[3];
        _pivot(_translate, back, _orbit_radius, piv);
        set_orbit_radius(_orbit_radius + dr);
        _translate[0] = piv[0] + _orbit_radius*back[0];
        _translate[1] = piv[1] + _orbit_radius*back[1];
        _translate[2] = piv[2] + _orbit_radius*back[2];
        cam_view(_translate, _rotate, _scale, _view);
    }


    //! Adjust orbit angles by given amounts.
    void
    orbit(const T dtheta_deg, const T dphi_deg)
    {
        //const NtVec3f wsx0(worldPos());
        //const NtVec3f bdir(back());
        //const float orb(orbitRadius(ctb));

        //const NtVec3f piv(pivot(wsx0, bdir, orb));
        T piv[3];
        _pivot(piv);

        // Compute spherical angles of camera position with respect to pivot.
        T theta_rad0;
        T phi_rad0;
        _spherical_angles(_translate, piv, _orbit_radius, theta_rad0, phi_rad0);
        phi_rad0 = 0.5*pi<T>() - phi_rad0;
#if 1
        {
        std::cerr << "\n";
        std::cerr << "Spherical Theta: " << rad_to_deg(theta_rad0) << "\n";
        std::cerr << "Spherical Phi: " << rad_to_deg(phi_rad0) << "\n";
        std::cerr << "\n";
        }
#endif

        const T theta_rad1 = theta_rad0 + deg_to_rad(dtheta_deg);
        const T phi_rad1 = phi_rad0 + deg_to_rad(dphi_deg);

        T wsx[3];
        T right[3];
        T up[3];
        T back[3];
        _spherical_coordinates(
            piv, 
            _orbit_radius,
            theta_rad1, 
            phi_rad1,
            _translate,
            right,
            up,
            back);
        cam_view(right, up, back, _translate, _view);
        //const T global_up[] = { 0, 1, 0 };
        //cam_view_lookat(_translate, piv, global_up, _view);

        T ea_rad[3];
        euler_angles_xyz(_view, ea_rad);
        _rotate_deg[0] = rad_to_deg(-ea_rad[0]);
        _rotate_deg[1] = rad_to_deg(-ea_rad[1]);
        _rotate_deg[2] = rad_to_deg(-ea_rad[2]);

        //_set_view();

#if 1
        {
        std::cerr << "\n";
        std::cerr << "translate: [" 
            << _translate[0] << ", " 
            << _translate[1] << ", " 
            << _translate[2] << "]\n";
        std::cerr << "rotate: [" 
            << _rotate_deg[0] << ", " 
            << _rotate_deg[1] << ", " 
            << _rotate_deg[2] << "]\n";
        T fwd[3];
        view_fwd(_view, fwd);
        std::cerr << "fwd: ["
            << fwd[0] << ", " 
            << fwd[1] << ", " 
            << fwd[2] << "]\n"; 
        std::cerr << "\n";
        }
#endif

        //const NtVec3f sphDeg1(
        //    sphDeg0[0] + mouseSpeed*ndy,
        //    sphDeg0[1] + mouseSpeed*ndx,
        //    sphDeg0[2]);

        //const NtVec3f wsx1(
        //    sphericalPosition(
        //        em::clamp(sphDeg1[0], -89.f, 89.f), // Phi.
        //        sphDeg1[1],  // theta
        //        orb,
        //        piv));

        // Look at the pivot from the new camera position and extract
        // resulting Euler angles.

        //const em::glmat44f mv(
        //    em::make_cam_view_lookat(wsx1, piv));

        //const NtVec3f ea(em::euler_angles_xyz(mv));

        // Update camera world position and rotation.

        //setParam3f("Rotate", -ea[0], -ea[1], -ea[2]);
        //setParam3f("Translate", wsx1[0], wsx1[1], wsx1[2]);
        //updateModelview();
    }




    void
    track(const int mx0, const int my0,
          const int mx1, const int my1,
          const T ms,
          const GLint vp[4],
          const GLdouble n = 0,
          const GLdouble f = 1)
    {
        T pv[16];
        mult_mat44(_proj, _view, pv);
        T inv_pv[16];
        invert_mat44(pv, inv_pv);   // May throw.
        T ori0[3];
        T dir0[3];
        pixel_ray(mx0, my0, vp, inv_pv, ori0, dir0, n, f);  // May throw.
        T ori1[3];
        T dir1[3];
        pixel_ray(mx1, my1, vp, inv_pv, ori1, dir1, n, f);  // May throw.
        T back[3];
        view_back(_view, back);
        T piv[3];
        _pivot(_translate, back, _orbit_radius, piv);
        T isect0[3];
        ray_plane_intersect(ori0, dir0, piv, back, isect0); // May throw.
        T isect1[3];
        ray_plane_intersect(ori1, dir1, piv, back, isect1); // May throw.
        track(ms*(isect1[0] - isect0[0]), ms*(isect1[1] - isect0[1]));
    }


    void
    orbit(const int mx0, const int my0,
          const int mx1, const int my1,
          const GLint vp[4],
          const T ms = 1)
    {
        const T ndx = (ms*(mx1 - mx0))/vp[2];
        const T ndy = (ms*(my1 - my0))/vp[3];
        const T dtheta_deg = 180*ndx;
        const T dphi_deg = 180*ndy;
        orbit(dtheta_deg, 0/*dphi_deg*/);
    }






    //void
    //dolly(const GLfloat dr)
    //{
    //    _dolly(dr);
    //    //const NtVec3f piv = pivot(wsx0, bdir, rad);
    //    //const float dim = 
    //    //    std::max<float>(bbox.dimX(), 
    //    //        std::max<float>(bbox.dimY(), bbox.dimZ()));
    //    //const float dist = mouseSensitivity(ctb)*(1.f + dim);
    //    //const float dm = (ndx - ndy); // Mouse drag.
    //    //const float orb1 = std::max<float>(2.f*near, rad + dm*dist); // New radius.
    //    //const NtVec3f wsx1 = piv + orb1*bdir;     // New world space position.
    //}



    void
    frame(const T wsx_min[3], const T wsx_max[3])
    {
        // Check valid bounds.
        if (wsx_min[0] < wsx_max[0] &&
            wsx_min[1] < wsx_max[1] &&
            wsx_min[2] < wsx_max[2]) {
            T wsx_dim[3];
            diff_vec<T,3>(wsx_max, wsx_min, wsx_dim);
            const T wsx_rad = 
                static_cast<T>(
                    sqrt(0.25*wsx_dim[0]*wsx_dim[0] + 
                         0.25*wsx_dim[1]*wsx_dim[1] + 
                         0.25*wsx_dim[2]*wsx_dim[2]));
            _orbit_radius = 2*wsx_rad;
            T back[3];
            view_back(_view, back);
            _translate[0] = 
                static_cast<T>(
                    0.5*(wsx_min[0] + wsx_max[0]) + _orbit_radius*back[0]);
            _translate[1] = 
                static_cast<T>(
                    0.5*(wsx_min[1] + wsx_max[1]) + _orbit_radius*back[1]);
            _translate[2] = 
                static_cast<T>(
                    0.5*(wsx_min[2] + wsx_max[2]) + _orbit_radius*back[2]);
            _set_view();
        }
    }

private:


    void
    _orbit()
    {
        //const float mouseSpeed(std::min(180.f, 180.f*mouseSensitivity(ctb)));

        //const NtVec3f wsx0(worldPos());
        //const NtVec3f bdir(back());
        //const float orb(orbitRadius(ctb));

        //const NtVec3f piv(pivot(wsx0, bdir, orb));

        //// Get spherical angles of camera position with respect to pivot.
        //const NtVec3f sphDeg0(sphericalAngles(wsx0, piv));

        //const NtVec3f sphDeg1(
        //    sphDeg0[0] + mouseSpeed*ndy,
        //    sphDeg0[1] + mouseSpeed*ndx,
        //    sphDeg0[2]);

        //const NtVec3f wsx1(
        //    sphericalPosition(
        //        em::clamp(sphDeg1[0], -89.f, 89.f), // Phi.
        //        sphDeg1[1],  // theta
        //        orb,
        //        piv));

        //// Look at the pivot from the new camera position and extract
        //// resulting Euler angles.

        //const em::glmat44f mv(
        //    em::make_cam_view_lookat(wsx1, piv));

        //const NtVec3f ea(em::euler_angles_xyz(mv));

        //// Update camera world position and rotation.

        //setParam3f("Rotate", -ea[0], -ea[1], -ea[2]);
        //setParam3f("Translate", wsx1[0], wsx1[1], wsx1[2]);

        //updateModelview();
    }

private:

    //! Compute pivot position using current camera state. 
    //! [out] piv: pivot position.
    void
    _pivot(T piv[3])
    {
        T back[3];
        view_back(_view, back);
        _pivot(_translate, back, _orbit_radius, piv);
    }

    //! Set camera view matrix from internal state.
    void
    _set_view()
    {
        cam_view(_translate, _rotate_deg, _scale, _view);
    }

private:

    //! Set camera projection matrix from internal state.
    void
    _set_perspective_projection()
    {
        perspective_projection( 
            _pixel_focal_length(
                _angle_of_view(
                    _inch_to_mm(_horizontal_aperture), _focal_length)), 
            _aspect, 
            _near_clip, 
            _far_clip, 
            _proj);
    }

private:    // Utility functions for computing view matrix.

    //! Get pivot position in world space.
    //! [in]  translate: camera position in world space.
    //! [in]       back: camera back direction.
    //! [in]     radius: orbit radius.
    //! [out]       piv: pivot position.
    static void
    _pivot(const T translate[3], const T back[3], const T radius, T piv[3])
    {
        piv[0] = translate[0] - radius*back[0];
        piv[1] = translate[1] - radius*back[1];
        piv[2] = translate[2] - radius*back[2];
    }

    //! Compute Cartesian coordinates based on spherical coordinates.
    //! [in]          c: sphere center.
    //! [in]          r: sphere radius.
    //! [in]  theta_rad: azimuth angle in xz-plane (longitude) in [radians].
    //! [in]    phi_rad: zenith angle (latitude) in [radians].
    //! [out]         p: Cartesian coordinates.
    static void
    _spherical_coordinates(const T ctr[3], 
                           const T radius,
                           const T theta_rad, 
                           const T phi_rad, 
                           T       p[3],
                           T       r[3],
                           T       u[3],
                           T       b[3])
    {
        const T cos_theta = cos(theta_rad);
        const T sin_theta = sin(theta_rad);
        const T cos_phi = cos(phi_rad);
        const T sin_phi = sin(phi_rad);
        p[0] = ctr[0] + radius*sin_theta*sin_phi;
        p[1] = ctr[1] + radius*cos_phi;
        p[2] = ctr[2] + radius*cos_theta*sin_phi;
        r[0] = cos_theta;
        r[1] = 0;
        r[2] = -sin_theta;
        u[0] = -sin_theta*cos_phi;
        u[1] = sin_phi;
        u[2] = -cos_theta*cos_phi;
        b[0] = sin_theta*sin_phi;
        b[1] = cos_phi;
        b[2] = cos_theta*sin_phi;
    }

    //! Return spherical angles in radians. Make sure the distance between
    //! p and c is non-zero.
    //! [in]          p: position in Cartesian coordinates.
    //! [in]          c: sphere center.
    //! [out]         r: radius.
    //! [out] theta_rad: azimuth angle in xz-plane (longitude) in [radians].
    //! [out]   phi_rad: zenith angle (latitude) in [radians].
    static void
    _spherical_angles(const T  p[3], 
                      const T  c[3], 
                      T       &r, 
                      T       &theta_rad, 
                      T       &phi_rad)
    {
        T dpc[3];
        diff_vec<T,3>(p, c, dpc);
        r = sqrt(dpc[0]*dpc[0] + dpc[1]*dpc[1] + dpc[2]*dpc[2]);
        theta_rad = atan2(dpc[0], dpc[2]);
        phi_rad = acos(dpc[1]/r);
    }

private:    // Utility functions for computing projection matrix.

    //! Convert inches to millimeters.
    //! [in] inch: value in [inch].
    static T
    _inch_to_mm(const T inch)
    { return static_cast<T>(25.4*inch); }

    //! Return aperture aspect ratio (vertical/horizontal).
    //! [in] ha: horizontal aperture.
    //! [in] va: vertical aperture.
    static T
    _aperture_aspect(const T ha, const T va)
    { return va/ha; }

    //! Returns angle of view in radians.
    //! Clamp to [1..179] (degrees).
    //! NB: aperture and focal_length: in same length unit, probably [mm].
    //! [in] ap: aperture, probably in [mm]
    //! [in] fl: focal length, probably in [mm]
    static T
    _angle_of_view(const T ap, const T fl)
    {
        static const T min_aov_rad = deg_to_rad<T>(1);
        static const T max_aov_rad = deg_to_rad<T>(179);
        return clamp(min_aov_rad, max_aov_rad, 2*atan(ap/(2*fl)));
    }

    //! Focal length in some sort of pixel-related units(?).
    //! NB: argument should be in radians.
    //! [in] aov_rad: angle of view in radians.
    static T
    _pixel_focal_length(const T aov_rad)
    { return static_cast<T>(1/tan(0.5*aov_rad)); }

private:    // Member variables.

    T _view[16];                //!< View matrix.
    T _proj[16];                //!< Projection matrix.

    T _translate[3];            //!< World space position.    
    T _rotate_deg[3];                
    T _scale[3];
    T _orbit_radius;            //!< Distance to pivot.
    T _anchor[3];

    T _focal_length;            //!< [mm]
    T _horizontal_aperture;     //!< [inch]
    T _vertical_aperture;       //!< [inch]
    T _near_clip;
    T _far_clip;
    T _aspect;
};

END_NDJINN_NAMESPACE

// -----------------------------------------------------------------------------

#endif  // NDJINN_CAMERA_HPP_INCLUDED
