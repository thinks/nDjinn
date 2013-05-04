//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_QUERY_HPP_INCLUDED
#define NDJINN_QUERY_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnException.hpp"
#include "nDjinnError.hpp"
#include <gl/glew.h>

//------------------------------------------------------------------------------

NDJINN_BEGIN_NAMESPACE

namespace detail {

//! glGenQueries wrapper. May throw.
inline void
genQueries(GLsizei const n, GLuint* queries) {
  glGenQueries(n, queries);
  checkError("glGenQueries");
}

//! glDeleteQueries wrapper. May throw.
inline void
deleteQueries(GLsizei const n, GLuint const* queries) {
  glDeleteQueries(n, queries);
  checkError("glDeleteQueries");
}

//! glIsQuery wrapper. May throw.
inline GLboolean
isQuery(GLuint const query) {
  GLboolean const result = glIsQuery(query);
  checkError("glIsQuery");
  return result;
}

//! glQueryCounter wrapper. May throw.
inline void 
queryCounter(GLuint const id) {
  glQueryCounter(id, GL_TIMESTAMP);
  checkError("glQueryCounter");
}

//! glBeginQuery wrapper. May throw.
inline void 
beginQuery(GLenum const target, GLuint const id) {
  glBeginQuery(target, id);
  checkError("glBeginQuery");
}

//! glBeginQueryIndexed wrapper. May throw.
inline void
beginQueryIndexed(GLenum const target, GLuint const index, GLuint const id) {
  glBeginQueryIndexed(target, index, id);
  checkError("glBeginQueryIndexed");
}

//! glEndQuery wrapper. May throw.
inline void
endQuery(GLenum const target) {
  glEndQuery(target);
  checkError("glEndQuery");
}

//! glEndQueryIndexed wrapper. May throw.
inline void
endQueryIndexed(GLenum const target, GLuint const index) {
  glEndQueryIndexed(target, index);
  checkError("glEndQueryIndexed");
}

//! glGetQueryiv wrapper. May throw.
inline void 
getQueryiv(GLenum const target, GLenum const pname, GLint* params) {
  glGetQueryiv(target, pname, params);
  checkError("glGetQueryiv");
}

//! glGetQueryIndexediv wrapper. May throw.
inline void
getQueryIndexediv(GLenum const target, 
                  GLuint const index, 
                  GLenum const pname, 
                  GLint* params) {
  glGetQueryIndexediv(target, index, pname, params);
  checkError("glGetQueryIndexediv");
}

//! glGetQueryObjectiv wrapper. May throw.
inline void 
getQueryObjectiv(GLuint const id, GLenum const pname, GLint* params) {
  glGetQueryObjectiv(id, pname, params);
  checkError("glGetQueryObjectiv");
}

//! glGetQueryObjectuiv wrapper. May throw.
inline void 
getQueryObjectuiv(GLuint const id, GLenum const pname, GLuint* params) {
  glGetQueryObjectuiv(id, pname, params);
  checkError("glGetQueryObjectuiv");
}

//! glGetQueryObjecti64v wrapper. May throw.
inline void 
getQueryObjecti64v(GLuint const id, GLenum const pname, GLint64* params) {
  glGetQueryObjecti64v(id, pname, params);
  checkError("glGetQueryObjecti64v");
}

//! glGetQueryObjectui64v wrapper. May throw.
inline void 
getQueryObjectui64v(GLuint const id, GLenum const pname, GLuint64* params) {
  glGetQueryObjectui64v(id, pname, params);
  checkError("glGetQueryObjectui64v");
}


template <typename T> void 
getQueryObjectv(GLuint id, GLenum pname, T* params);

template <> inline void
getQueryObjectv<GLint>(GLuint const id, GLenum const pname, GLint* params) {
  getQueryObjectiv(id, pname, params);
}

template <> inline void
getQueryObjectv<GLuint>(GLuint const id, GLenum const pname, GLuint* params) {
  getQueryObjectuiv(id, pname, params);
}

template <> inline void
getQueryObjectv<GLint64>(GLuint const id, 
                         GLenum const pname, 
                         GLint64* params) {
  getQueryObjecti64v(id, pname, params);
}

template <> inline void
getQueryObjectv<GLuint64>(GLuint const id, 
                          GLenum const pname, 
                          GLuint64* params) {
  getQueryObjectui64v(id, pname, params);
}


//! Convenience.
inline GLuint
genQuery() {
  GLuint query = 0;
  genQueries(1, &query);
  return query;
}

//! Convenience.
inline void
deleteQuery(GLuint const& query) {
  deleteQueries(1, &query);
}

} // namespace detail

//------------------------------------------------------------------------------

//! DOCS
class Query {
public:
  Query(GLenum target);
  ~Query();

  void
  begin();

  void 
  end();

  template <typename T>
  void result(T* r) const;

  bool 
  resultAvailable() const;

  void
  wait() const;

private: // Member variables.
  GLuint const _handle;
  GLenum const _target;
};

//! DOCS
class IndexedQuery {
public:
  IndexedQuery(GLenum target, GLuint index);
  ~IndexedQuery();

  void
  begin();

  void 
  end();

  template <typename T>
  void result(T* r) const;

  bool 
  resultAvailable() const;

private: // Member variables.
  GLuint const _handle;
  GLenum const _target;
  GLuint const _index;
};

//------------------------------------------------------------------------------

inline
Query::Query(GLenum const target)
  : _handle(detail::genQuery())
  , _target(target) {
}

inline
Query::~Query() {
  detail::deleteQuery(_handle);
}

void
Query::begin() {
  detail::beginQuery(_target, _handle);
}

void 
Query::end() {
  detail::endQuery(_target);
}

template <typename T>
inline void
Query::result(T* r) const {
  detail::getQueryObjectv<T>(_handle, GL_QUERY_RESULT, r);
}

inline bool 
Query::resultAvailable() const {
  GLint p = 0;
  detail::getQueryObjectiv(_handle, GL_QUERY_RESULT_AVAILABLE, &p);
  return p == GL_TRUE;
}

void
Query::wait() const {
  while (!resultAvailable()) {  
  }
}


//------------------------------------------------------------------------------

inline
IndexedQuery::IndexedQuery(GLenum const target, GLuint const index)
  : _handle(detail::genQuery())
  , _target(target)
  , _index(index) {
}

inline
IndexedQuery::~IndexedQuery() {
  detail::deleteQuery(_handle);
}

void
IndexedQuery::begin() {
  detail::beginQueryIndexed(_target, _index, _handle);
}

void 
IndexedQuery::end() {
  detail::endQueryIndexed(_target, _index);
}

template <typename T>
inline void
IndexedQuery::result(T* r) const {
  detail::getQueryObjectv<T>(_handle, GL_QUERY_RESULT, r);
}

inline bool 
IndexedQuery::resultAvailable() const {
  GLint p = 0;
  detail::getQueryObjectiv(_handle, GL_QUERY_RESULT_AVAILABLE, &p);
  return p == GL_TRUE;
}

NDJINN_END_NAMESPACE

#endif // NDJINN_QUERY_HPP_INCLUDED
