
#include "rzboom-bu.h"
#include "rzboom-td.h"

#include "nlohmann/json.hpp"
#include "gtest/gtest.h"

#include <string>

using json = nlohmann::json;

TEST(rzboom, build_as_specified)
{
    std::vector<std::tuple<int, std::string, Kleur>> content = {
            std::make_tuple(10, std::to_string(10), Kleur::ZWART),
            std::make_tuple(3, std::to_string(3), Kleur::ZWART),
            std::make_tuple(15, std::to_string(15), Kleur::ROOD),
            std::make_tuple(2, std::to_string(2), Kleur::ZWART),
            std::make_tuple(6, std::to_string(6), Kleur::ZWART),
            std::make_tuple(12, std::to_string(12), Kleur::ZWART),
            std::make_tuple(18, std::to_string(18), Kleur::ZWART),
            std::make_tuple(4, std::to_string(4), Kleur::ROOD),
            std::make_tuple(8, std::to_string(8), Kleur::ROOD),
            std::make_tuple(11, std::to_string(11), Kleur::ZWART),
            std::make_tuple(13, std::to_string(13), Kleur::ZWART),
            std::make_tuple(16, std::to_string(16), Kleur::ZWART),
            std::make_tuple(20, std::to_string(20), Kleur::ZWART),
    };

    RZBoomBottomUp<int, std::string> rzb{content};

    auto controle_json = json::parse(R"(
        {
            "key": 10,
            "color": "black",
            "left": {
                "key": 3,
                "color": "black",
                "left": {
                    "key": 2,
                    "color": "black",
                    "left": {},
                    "right": {}
                },
                "right": {
                    "key": 6,
                    "color": "black",
                    "left": {
                        "key": 4,
                        "color": "red",
                        "left": {},
                        "right": {}
                    },
                    "right": {
                        "key": 8,
                        "color": "red",
                        "left": {},
                        "right": {}
                    }
                }
            },
            "right": {
                "key": 15,
                "color": "red",
                "left": {
                    "key": 12,
                    "color": "black",
                    "left": {
                        "key": 11,
                        "color": "black",
                        "left": {},
                        "right": {}
                    },
                    "right": {
                        "key": 13,
                        "color": "black",
                        "left": {},
                        "right": {}
                    }
                },
                "right": {
                    "key": 18,
                    "color": "black",
                    "left": {
                        "key": 16,
                        "color": "black",
                        "left": {},
                        "right": {}
                    },
                    "right": {
                        "key": 20,
                        "color": "black",
                        "left": {},
                        "right": {}
                    }
                }
            }
        }
    )");

    ASSERT_EQ(json::parse(rzb.to_json()), controle_json);
}

TEST(rzboom, add_bottom_up)
{
    RZBoomBottomUp<int, std::string> rzb;
    int keys[] = {13, 3, 4, 12, 14, 10, 5, 1, 8, 2, 7, 9, 11, 6, 18};

    for (int key : keys)
    {
        rzb.voeg_toe(key, std::to_string(key));
    }

    auto controle_json = json::parse(R"(
        {
            "key": 10,
            "color": "black",
            "left": {
                "key": 4,
                "color": "black",
                "left": {
                    "key": 2,
                    "color": "black",
                    "left": {
                        "key": 1,
                        "color": "red",
                        "left": {},
                        "right": {}
                    },
                    "right": {
                        "key": 3,
                        "color": "red",
                        "left": {},
                        "right": {}
                    }
                },
                "right": {
                    "key": 7,
                    "color": "red",
                    "left": {
                        "key": 5,
                        "color": "black",
                        "left": {},
                        "right": {
                            "key": 6,
                            "color": "red",
                            "left": {},
                            "right": {}
                        }
                    },
                    "right": {
                        "key": 8,
                        "color": "black",
                        "left": {},
                        "right": {
                            "key": 9,
                            "color": "red",
                            "left": {},
                            "right": {}
                        }
                    }
                }
            },
            "right": {
                "key": 13,
                "color": "black",
                "left": {
                    "key": 12,
                    "color": "black",
                    "left": {
                        "key": 11,
                        "color": "red",
                        "left": {},
                        "right": {}
                    },
                    "right": {}
                },
                "right": {
                    "key": 14,
                    "color": "black",
                    "left": {},
                    "right": {
                        "key": 18,
                        "color": "red",
                        "left": {},
                        "right": {}
                    }
                }
            }
        }
    )");

    ASSERT_EQ(json::parse(rzb.to_json()), controle_json);
    ASSERT_TRUE(rzb.is_rep_ok());
}

// https://www.coursehero.com/file/22593733/red-black-examples/
TEST(rzboom, add_top_down)
{
    RZBoomTopDown<int, std::string> rzb;
    int keys[] = {4, 7, 10, 2, 5, 6, 3, 8, 0, 9, 1};

    for (int key : keys)
    {
        rzb.voeg_toe(key, std::to_string(key));
    }

    auto controle_json = json::parse(R"(
        {
            "key": 4,
            "color": "black",
            "left": {
                "key": 2,
                "color": "red",
                "left": {
                    "key": 0,
                    "color": "black",
                    "left": {},
                    "right": {
                        "key": 1,
                        "color": "red",
                        "left": {},
                        "right": {}
                    }
                },
                "right": {
                    "key": 3,
                    "color": "black",
                    "left": {},
                    "right": {}
                }
            },
            "right": {
                "key": 7,
                "color": "red",
                "left": {
                    "key": 5,
                    "color": "black",
                    "left": {},
                    "right": {
                        "key": 6,
                        "color": "red",
                        "left": {},
                        "right": {}
                    }
                },
                "right": {
                    "key": 9,
                    "color": "black",
                    "left": {
                        "key": 8,
                        "color": "red",
                        "left": {},
                        "right": {}
                    },
                    "right": {
                        "key": 10,
                        "color": "red",
                        "left": {},
                        "right": {}
                    }
                }
            }
        }
    )");

    ASSERT_EQ(json::parse(rzb.to_json()), controle_json);
    ASSERT_TRUE(rzb.is_rep_ok());
}
