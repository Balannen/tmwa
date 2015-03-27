#include "int_party_ai.hpp"

#include "../ints/udl.hpp"

#include "../strings/mstring.hpp"
#include "../strings/astring.hpp"
#include "../strings/xstring.hpp"

#include "../generic/db.hpp"

#include "../io/cxxstdio.hpp"
#include "../io/extract.hpp"
#include "../io/lock.hpp"
#include "../io/read.hpp"
#include "../io/write.hpp"

#include "../proto2/char-map.hpp"

#include "../mmo/ids.hpp"

#include "../high/extract_mmo.hpp"
#include "../high/mmo.hpp"

#include "../wire/packets.hpp"

//#include "char.hpp"
#include "globals.hpp"
//#include "inter.hpp"
#include "inter_conf.hpp"

#include "../poison.hpp"

void ispis2 ()
{
    printf("%s\n", "bananko Banana");
    //tmwa::char_::inter_party_save2();
}

namespace tmwa
{
namespace char_
{
// パーティデータの文字列への変換
static
AString inter_party_tostr2(PartyPair p)
{
    MString str;
    str += STRPRINTF(
            "%d\t"
            "%s\t"
            "%d,%d\t"_fmt,
            p.party_id,
            p->name,
            p->exp, p->item);
    for (int i = 0; i < MAX_PARTY; i++)
    {
        PartyMember *m = &p->member[i];
        if (!m->account_id)
            continue;
        str += STRPRINTF(
                "%d,%d\t"
                "%s\t"_fmt,
                m->account_id, m->leader,
                m->name);
    }

    return AString(str);
}

// パーティーデータのセーブ用
static
void inter_party_save_sub2(PartyPair data, io::WriteFile& fp)
{
    AString line = inter_party_tostr2(data);
    fp.put_line(line);
}

// パーティーデータのセーブ
int inter_party_save2(void)
{
    io::WriteLock fp(inter_conf.party_txt);
    if (!fp.is_open())
    {
        PRINTF("int_party: cant write [%s] !!! data is lost !!!\n"_fmt,
                inter_conf.party_txt);
        return 1;
    }
    for (auto& pair : party_db)
    {
        PartyPair tmp{pair.first, borrow(pair.second)};
        inter_party_save_sub2(tmp, fp);
    }

    return 0;
}
} // namespace char_
} // namespace tmwa