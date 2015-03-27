#pragma once
//    wire/fwd.hpp - list of type names for network packets
//
//    Copyright © 2014 Ben Longbons <b.r.longbons@gmail.com>
//
//    This file is part of The Mana World (Athena server)
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "../sanity.hpp"

#include "../ints/fwd.hpp" // rank 1
#include "../compat/fwd.hpp" // rank 2
#include "../io/fwd.hpp" // rank 4
#include "../net/fwd.hpp" // rank 5
#include "../proto2/fwd.hpp" // rank 8
// wire/fwd.hpp is rank 9

namespace tmwa
{
enum class RecvResult;
// meh, add more when I feel like it
} // namespace tmwa
