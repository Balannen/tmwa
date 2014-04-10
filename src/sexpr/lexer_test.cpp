#include "lexer.hpp"
//    lexer_test.cpp - Testsuite for sexpr tokenizer.
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

#include <gtest/gtest.h>

#include "../poison.hpp"

static
io::FD string_pipe(ZString sz)
{
    io::FD rfd, wfd;
    if (-1 == io::FD::pipe(rfd, wfd))
        return io::FD();
    if (sz.size() != wfd.write(sz.c_str(), sz.size()))
    {
        rfd.close();
        wfd.close();
        return io::FD();
    }
    wfd.close();
    return rfd;
}

TEST(sexpr, escape)
{
    EXPECT_EQ(sexpr::escape('\0'), "\\x00");
    EXPECT_EQ(sexpr::escape('\x1f'), "\\x1f");
    EXPECT_EQ(sexpr::escape('\x20'), " ");
    EXPECT_EQ(sexpr::escape('\x7e'), "~");
    EXPECT_EQ(sexpr::escape('\x7f'), "\\x7f");
    EXPECT_EQ(sexpr::escape('\x80'), "\\x80");
    EXPECT_EQ(sexpr::escape('\xff'), "\\xff");
    EXPECT_EQ(sexpr::escape('\a'), "\\a");
    EXPECT_EQ(sexpr::escape('\b'), "\\b");
    EXPECT_EQ(sexpr::escape('\e'), "\\e");
    EXPECT_EQ(sexpr::escape('\f'), "\\f");
    //EXPECT_EQ(sexpr::escape('\n'), "\\n");
    EXPECT_EQ(sexpr::escape('\n'), "\n");
    EXPECT_EQ(sexpr::escape('\r'), "\\r");
    EXPECT_EQ(sexpr::escape('\t'), "\\t");
    EXPECT_EQ(sexpr::escape('\v'), "\\v");
    EXPECT_EQ(sexpr::escape('\\'), "\\\\");
    EXPECT_EQ(sexpr::escape('\"'), "\\\"");

    EXPECT_EQ(sexpr::escape("\x1f\x20\x7e\x7f\x80\xff\a\b\e\f\r\t\v\\\""),
            "\"\\x1f ~\\x7f\\x80\\xff\\a\\b\\e\\f\\r\\t\\v\\\\\\\"\"");
}

TEST(sexpr, lexer)
{
    io::LineSpan span;
    sexpr::Lexer lexer("<lexer-test1>", string_pipe(" foo( ) 123\"\" \n"));
    EXPECT_EQ(lexer.peek(), sexpr::TOK_TOKEN);
    EXPECT_EQ(lexer.val_string(), "foo");
    EXPECT_EQ(lexer.span().message_str("error", "test"),
            "<lexer-test1>:1:2: error: test\n"
            " foo( ) 123\"\" \n"
            " ^~~\n"
    );
    lexer.adv();
    EXPECT_EQ(lexer.peek(), sexpr::TOK_OPEN);
    EXPECT_EQ(lexer.span().message_str("error", "test"),
            "<lexer-test1>:1:5: error: test\n"
            " foo( ) 123\"\" \n"
            "    ^\n"
    );
    lexer.adv();
    EXPECT_EQ(lexer.peek(), sexpr::TOK_CLOSE);
    EXPECT_EQ(lexer.span().message_str("error", "test"),
            "<lexer-test1>:1:7: error: test\n"
            " foo( ) 123\"\" \n"
            "      ^\n"
    );
    lexer.adv();
    EXPECT_EQ(lexer.peek(), sexpr::TOK_TOKEN);
    EXPECT_EQ(lexer.val_string(), "123");
    EXPECT_EQ(lexer.span().message_str("error", "test"),
            "<lexer-test1>:1:9: error: test\n"
            " foo( ) 123\"\" \n"
            "        ^~~\n"
    );
    lexer.adv();
    EXPECT_EQ(lexer.peek(), sexpr::TOK_STRING);
    EXPECT_EQ(lexer.val_string(), "");
    EXPECT_EQ(lexer.span().message_str("error", "test"),
            "<lexer-test1>:1:12: error: test\n"
            " foo( ) 123\"\" \n"
            "           ^~\n"
    );
    lexer.adv();
    EXPECT_EQ(lexer.peek(), sexpr::TOK_EOF);
}

TEST(sexpr, lexbad)
{
    {
        io::LineSpan span;
        sexpr::Lexer lexer("<lexer-bad>", string_pipe("(\n"));
        EXPECT_EQ(lexer.peek(), sexpr::TOK_OPEN);
        lexer.adv();
        EXPECT_EQ(lexer.peek(), sexpr::TOK_ERROR);
    }
    for (ZString bad : {
            ZString(")\n"),
            ZString("\"\n"),
            ZString("'\n"),
            ZString("\\\n"),
            ZString("\"\\"),
            ZString("\"\\z\""),
    })
    {
        io::LineSpan span;
        sexpr::Lexer lexer("<lexer-bad>", string_pipe(bad));
        EXPECT_EQ(lexer.peek(), sexpr::TOK_ERROR);
    }
}
