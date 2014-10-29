#pragma once
//    ast/item.hpp - Structure of tmwa itemdb
//
//    Copyright © 2014 Ben Longbons <b.r.longbons@gmail.com>
//
//    This file is part of The Mana World (Athena server)
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Affero General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "fwd.hpp"

#include <memory>

#include "../compat/result.hpp"

#include "../io/span.hpp"

#include "../mmo/clif.t.hpp"
#include "../mmo/ids.hpp"
#include "../mmo/strs.hpp"

#include "script.hpp"


namespace tmwa
{
namespace ast
{
namespace item
{
    using io::Spanned;

    struct ItemOrComment
    {
        io::LineSpan span;

        virtual ~ItemOrComment();
    };
    struct Comment : ItemOrComment
    {
        RString comment;
    };
    struct Item : ItemOrComment
    {
        Spanned<ItemNameId> id;
        Spanned<ItemName> name;
        Spanned<ItemName> jname;
        Spanned<ItemType> type;
        Spanned<int> buy_price;
        Spanned<int> sell_price;
        Spanned<int> weight;
        Spanned<int> atk;
        Spanned<int> def;
        Spanned<int> range;
        Spanned<int> magic_bonus;
        Spanned<RString> slot_unused;
        Spanned<SEX> gender;
        Spanned<EPOS> loc;
        Spanned<int> wlv;
        Spanned<int> elv;
        Spanned<ItemLook> view;
        ast::script::ScriptBody use_script;
        ast::script::ScriptBody equip_script;
    };

    Result<std::unique_ptr<ItemOrComment>> parse_item(io::LineCharReader& lr);
} // namespace item
} // namespace ast
} // namespace tmwa
