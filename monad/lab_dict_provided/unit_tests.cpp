#include "proxy.h"
#include "anagram_dict.h"
#include "fib.h"
#include "cartalk_puzzle.h"
#include "pronounce_dict.h"
#include "game.h"

#include <sstream>
#include <algorithm>
#include <utility>
#include <string>
#include <set>

using namespace std;
using namespace game_ret;

static vector< unsigned int > fib_results = 
{ 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584,
  4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811 };
                               

static vector< string > words = 
{ "dog", "god", "good", "super", "cow", "powers", "skin", "kins" };

static map< string, vector< string > > pronunciations = 
                            { { "SCENT", { "DUMMY" } }, 
                              { "CENT", { "DUMMY" } },
                              { "SENT", { "DUMMY" } },
                              { "DOG", { "DOGE" } }
                            };

#if MONAD_SPLIT
UNIT_TEST(test_get_anagrams, 15, 15, 5000)
{
    AnagramDict d(words);
    const vector< string > canon = { "dog", "god" };
    vector< string > result = d.get_anagrams("dog");
    ASSERT(canon == result);
    ASSERT(d.get_anagrams("z").empty());
}
#endif

#if MONAD_SPLIT
UNIT_TEST(test_get_all_anagrams, 15, 15, 5000)
{
    AnagramDict d(words);
    set< set< string > > canon = { { "dog", "god" }, { "skin", "kins" } };
    vector< vector< string > > result = d.get_all_anagrams();
    /* We want to be agnostic to all orderings. */
    set< set< string > > result_set;
    for(auto& anagram_vec : result)
    {
        /* Has to be insert because GCC 4.7 didn't implemet emplace for set. */
        set< string > s(anagram_vec.begin(), anagram_vec.end());
        result_set.insert(s);
    }
    ASSERT(canon == result_set);
}
#endif

#if MONAD_SPLIT
UNIT_TEST(test_fib, 5, 5, 1000)
{
    for(size_t i = 0; i < 6; i ++)
    {
        ASSERT(fib(i) == fib_results[i]);
    }
}
#endif

#if MONAD_SPLIT
UNIT_TEST(test_memoized_fib, 10, 10, 100)
{
    for(int i = 0; i < 10; i ++)
    {
        ASSERT(memoized_fib(28) == fib_results[28]);
    }
}
#endif 

#if MONAD_SPLIT
UNIT_TEST(test_homophones, 10, 10, 1000)
{
    PronounceDict d(pronunciations);
    ASSERT(d.homophones("scent", "CeNt"));
    ASSERT((! d.homophones("scent", "DOG")));
    ASSERT((! d.homophones("garbage", "Tim")));
}
#endif

#if MONAD_SPLIT
UNIT_TEST(test_cartalk_puzzle, 10, 10, 1000)
{
    PronounceDict d(pronunciations);
    vector< string > canon = {"scent", "cent", "sent"};
    auto result = cartalk_puzzle(d, "cartalk_words.txt");
    ASSERT(result.size() == 1);
    vector< string > result_vec = { get<0>(result[0]),
                                    get<1>(result[0]),
                                    get<2>(result[0]) };
    ASSERT(is_permutation(canon.begin(), canon.end(), result_vec.begin()));
}
#endif

#if MONAD_SPLIT
UNIT_TEST(test_delete_users, 5, 5, 1000)
{
    Game g;
    g.add_user("lls");
    g.add_user("skyenet");
    ASSERT(INVALID_USERNAME == g.delete_user("m"));
    /* The following usernames are not mispelled. */
    ASSERT(SUCCESS == g.delete_user("skyenet"));
    ASSERT(SUCCESS == g.delete_user("lls"));
    ASSERT(INVALID_USERNAME == g.delete_user("lls"));
}
#endif

#if MONAD_SPLIT
UNIT_TEST(test_login_logout_users, 5, 5, 1000)
{
    Game g;
    g.add_user("lls");
    g.add_user("skyenet");
    g.login_user("lls");
    ASSERT(INVALID_USERNAME == g.logout_user("m"));
    ASSERT(SUCCESS == g.logout_user("skyenet"));
    ASSERT(SUCCESS == g.logout_user("lls"));
}
#endif

#if MONAD_SPLIT
UNIT_TEST(test_make_party, 5, 5, 1000)
{
    Game g;
    vector< string > team = { "lls", "skyenet" };
    ASSERT("" == g.make_party(team));
    for(string& un : team)
    {
        g.add_user(un);
        g.login_user(un);
    }
    ASSERT("" != g.make_party(team));    
    team.push_back("mjoras");
    g.add_user("mjoras");
    g.login_user("mjoras");
    ASSERT("" == g.make_party(team));
}
#endif

#if MONAD_SPLIT
UNIT_TEST(test_make_match, 5, 5, 1000)
{
    Game g;
    ASSERT(NULL_MATCH_ID == g.make_match("garbage"));    
    vector< string > team = { "lls", "skyenet" };
    for(string& un : team)
    {
        g.add_user(un);
        g.login_user(un);
    }
    string party_id = g.make_party(team);
   
    unsigned long match_id1 = g.make_match(party_id);
    ASSERT(NULL_MATCH_ID != match_id1);
    ASSERT(NULL_MATCH_ID == g.make_match(party_id));
}
#endif

#if MONAD_SPLIT
UNIT_TEST(test_get_user_stats, 5, 5, 1000)
{
    Game g;
    Game::UserStats def;
    Game::UserStats us;
    ASSERT(INVALID_USERNAME == g.get_user_stats("mjoras", us));
    g.add_user("lls");
    ASSERT(SUCCESS == g.get_user_stats("lls", us));
    ASSERT(def == us);
}
#endif

#if MONAD_SPLIT
UNIT_TEST(test_find_match, 10, 10, 1000)
{
    Game g;
    vector< string > team1 = { "lls", "skyenet", "tim", "csouth" };
    vector< string > team2 = { "dejong", "pushl%car", "alex", "wiss" };
    for(string& un : team1)
    {
        g.add_user(un);
        g.login_user(un);
    }
    for(string& un : team2)
    {
        g.add_user(un);
        g.login_user(un);
    }
    string party1 = g.make_party(team1);
    string party2 = g.make_party(team2);
    ASSERT(party1 != "" && party2 != "");

    unsigned long match_id = g.make_match(party1);
    unsigned long found_match = g.find_match(party2, 10);
    ASSERT(match_id == found_match);
    ASSERT(SUCCESS == g.add_party_to_match(party2, match_id));
    ASSERT(SUCCESS == g.start_match(match_id));
    ASSERT(SUCCESS == g.end_match(match_id, 1000, 0, 10));
    Game::UserStats us;
    g.get_user_stats("lls", us);
    ASSERT(us.experience == 1000);
    g.get_user_stats("dejong", us);
    ASSERT(us.experience == 0);
    
    match_id = g.make_match(party1);
    ASSERT(match_id != NULL_MATCH_ID);
    found_match = g.find_match(party2, 10);
    ASSERT(found_match == NULL_MATCH_ID);
    found_match = g.find_match(party2, 1000);
    ASSERT(found_match != NULL_MATCH_ID);    
    found_match = g.find_match(party2, 2000);
    ASSERT(found_match != NULL_MATCH_ID);

}
#endif
