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
 * \file claw/tween/easing/symmetric_easing.hpp
 * \brief Easing functions for the tweener.
 * \author Julien Jorge
 */
#ifndef __CLAW_TWEEN_SYMMETRIC_EASING_HPP__
#define __CLAW_TWEEN_SYMMETRIC_EASING_HPP__

namespace claw {
  namespace tween {
    /**
     * \brief Easing functions for the tweener.
     * \author Julien Jorge
     */
    template<double (*Function)(double)>
    class symmetric_easing {
    public:
      static double ease_in(double t);
      static double ease_out(double t);
      static double ease_in_out(double t);

    }; // class symmetric_easing

  } // namespace tween
} // namespace claw

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the easing at the beginning of the tweener.
 * \param t The ratio of the date, in (0, 1), representing the total progression
 *        of the tweener.
 */
template<double (*Function)(double)>
double claw::tween::symmetric_easing<Function>::ease_in(double t) {
  return Function(t);
} // symmetric_easing::ease_in()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the easing at the end of the tweener.
 * \param t The ratio of the date, in (0, 1), representing the total progression
 *        of the tweener.
 */
template<double (*Function)(double)>
double claw::tween::symmetric_easing<Function>::ease_out(double t) {
  return 1 - ease_in(1 - t);
} // symmetric_easing::ease_out()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the easing at the beginning and the end of the tweener.
 * \param t The ratio of the date, in (0, 1), representing the total progression
 *        of the tweener.
 */
template<double (*Function)(double)>
double claw::tween::symmetric_easing<Function>::ease_in_out(double t) {
  if (t < 0.5) {
    return ease_in(2 * t) / 2;
  } else {
    return 0.5 + ease_out(2 * t - 1) / 2;
  }
} // symmetric_easing::ease_in_out()

#endif // __CLAW_TWEEN_SYMMETRIC_EASING_HPP__
