/*
  CLAW - a C++ Library Absolutely Wonderful

  CLAW is a free library without any particular aim but being useful to 
  anyone.

  Copyright (C) 2005-2011 Julien Jorge

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  contact: julien.jorge@gamned.org
*/
/**
 * \file claw/code/tween/tweener.cpp
 * \brief Implementation of the claw::tween::tweener class.
 * \author Julien Jorge
 */

#include "tweener.hpp"
#include "base_tweener.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Default constructor.
 */
claw::tween::tweener::tweener()
: m_impl(nullptr) {

} // tweener::tweener()

/*----------------------------------------------------------------------------*/
/**
 * \brief Copy constructor.
 * \param that The instance to copy from.
 */
claw::tween::tweener::tweener(const tweener& that)
: m_impl(that.m_impl == nullptr ? nullptr : that.m_impl->clone()) {

} // tweener::tweener()

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor from a base_tweener.
 * \param that The instance to use for the implementation.
 */
claw::tween::tweener::tweener(const base_tweener& that)
: m_impl(that.clone()) {

} // tweener::tweener()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
claw::tween::tweener::~tweener() {
  delete m_impl;
} // tweener::~tweener()

/*----------------------------------------------------------------------------*/
/**
 * \brief Assignment operator.
 * \param that The instance to copy from.
 */
claw::tween::tweener& claw::tween::tweener::operator = (const tweener& that) {
  tweener tmp(that);
  swap(tmp);
  return *this;
} // tweener::operator=()

/*----------------------------------------------------------------------------*/
/**
 * \brief Swap this instance with a given instance.
 * \param that The instance to swap with.
 */
void claw::tween::tweener::swap(tweener& that) throw() {
  std::swap(m_impl, that.m_impl);
} // tweener::swap()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the tweener has reached his total duration.
 */
bool claw::tween::tweener::is_finished() const {
  if (m_impl == nullptr) {
    return true;
  } else {
    return m_impl->is_finished();
  }
} // tweener::is_finished()

/*----------------------------------------------------------------------------*/
/**
 * \brief Update the tweener of a given amount of time.
 * \param dt The duration of the update in time units since the last call.
 */
double claw::tween::tweener::update(double dt) {
  if (m_impl == nullptr) {
    return dt;
  } else {
    return m_impl->update(dt);
  }
} // tweener::update()

/*----------------------------------------------------------------------------*/
/**
 * \brief Execute the callbacks notifying about the finish of the tweener.
 */
void claw::tween::tweener::on_finished(finish_callback f) {
  if (m_impl != nullptr) {
    m_impl->on_finished(f);
  }
} // tweener::on_finished()

/*----------------------------------------------------------------------------*/
/**
 * \brief Swap two tweeners.
 * \param a The first tweener.
 * \param b The second tweener.
 */
template<>
void std::swap(claw::tween::tweener& a, claw::tween::tweener& b) {
  a.swap(b);
} // std::swap()
