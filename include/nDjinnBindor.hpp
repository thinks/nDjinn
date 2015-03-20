//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_BINDOR_HPP_INCLUDED
#define NDJINN_BINDOR_HPP_INCLUDED

#include "nDjinnGL.hpp"
#include "nDjinnNamespace.hpp"
#include "nDjinnSampler.hpp"

NDJINN_BEGIN_NAMESPACE

//! Resource must not be destroyed during the life-time of a Bindor instance.
template <class R>
class Bindor {
public:
  typedef R Resource;

  explicit Bindor(R const& resource)
      : _resource(resource) {
    _resource.bind();
  }

  ~Bindor() {
    _resource.release();
  }

private: // Member variables.
  R const& _resource;
};

//! Specialization for Sampler.
template <>
class Bindor<Sampler> {
public:
  explicit Bindor(Sampler const& sampler, GLuint const unit = 0)
      : _sampler(sampler)
      , _unit(unit) {
    _sampler.bind(_unit);
  }

  ~Bindor() {
    _sampler.release(_unit);
  }

private: // Member variables.
  Sampler const& _sampler;
  GLuint const _unit;
};

//------------------------------------------------------------------------------

NDJINN_END_NAMESPACE

#endif // NDJINN_BINDOR_HPP_INCLUDED
