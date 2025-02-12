#include <gtest/gtest.h>

#include <tools.h>

static auto rules = std::make_shared<std::map<std::string, std::string>>(
    std::map({
        std::pair<std::string, std::string> {"werewolf", "robber"},
        std::pair<std::string, std::string> {"robber", "bear"},
        std::pair<std::string, std::string> {"bear", "werewolf"}
    })
);

TEST(correct_npc_type, test)
{
    auto type = "werewolf";
    auto no_type = "Mihail";

    auto good = correct_npc_type(type, rules);
    auto bad = correct_npc_type(no_type, rules);

    ASSERT_TRUE(good);
    ASSERT_FALSE(bad);
}

TEST(can_kill, test)
{
    auto first_type = "werewolf";
    auto second_type = "bear";

    auto good = can_kill(second_type, first_type, rules);
    auto bad = can_kill(first_type, second_type, rules);

    ASSERT_TRUE(good);
    ASSERT_FALSE(bad);
}

TEST(distance, test)
{
    auto first = Pair{4, 3};
    auto second = Pair{0, 0};
    auto expected = 5.;

    auto result = distance(first, second);

    ASSERT_EQ(expected, result);
}

TEST(make_npcs, test)
{
    auto array_size = 50;
    auto size = 100;
    auto npcs = make_npcs(rules, nullptr, size);

    ASSERT_EQ(npcs->size, array_size);

    for (int i = 0; i < npcs->size; ++i) {
        ASSERT_TRUE((*npcs)[i]->status == ALIVE);
        auto crds = (*npcs)[i]->get_crds();
        ASSERT_TRUE(crds.x <= size);
        ASSERT_TRUE(crds.y <= size);
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}