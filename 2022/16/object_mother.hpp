/*
 ObjectMother creates objects for tests in a way object properties that are important.
 Copyright (C) 2023  Fredrik Bülow

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
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 USA

 Code is maintained here:
 https://github.com/fbulow/object_mother/
*/

#pragma once
#include <tuple>

template<class AA, class RET, class ... ARG>
struct ObjectMother
{
  using Arguments = std::tuple<ARG...>;
  Arguments arg;

  [[nodiscard]] RET get() const
  {
    return std::make_from_tuple<RET>(arg);
  }

  [[nodiscard]] AA clone() const
  {
    return {arg};
  }
  
  template<class TO_SET>
  [[nodiscard]] AA w(TO_SET const & newValue) const
  {
    auto ret = clone();
    std::get<TO_SET>(ret.arg) = newValue;
    return ret;
  }

  template<int INDEX, class TO_SET>
  [[nodiscard]] AA w(TO_SET const & newValue) const
  {
    auto ret = clone();
    std::get<INDEX>(ret.arg) = newValue;
    return ret;
  }

  [[nodiscard]] operator RET () const
  {return get();}

  template<class ... X>
  [[nodiscard]] static AA defaultValues(X...a)
  {
    return {Arguments{a...}};
  }
};
