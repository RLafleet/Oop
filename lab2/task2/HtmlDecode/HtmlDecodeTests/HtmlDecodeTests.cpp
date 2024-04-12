#define CATCH_CONFIG_MAIN
#include "../../../../Catch2/catch.hpp"
#include "Decode.h" 

SCENARIO("HtmlDecode function tests", "[ResponceVector]") {
    GIVEN("An empty str") {
        std::string str = "";

        WHEN("Calling ResponceVector function") {
            str = DecodeHtmlStr(str);

            THEN("Vector size should remain unchanged") {
                REQUIRE(str.empty() == true);
            }
        }
    }

    GIVEN("An decode str") {
        std::string str = "&amp quot;";

        WHEN("Calling ResponceVector function") {
            str = DecodeHtmlStr(str);

            THEN("Vector size should remain unchanged") {
                REQUIRE(str == "&amp quot;");
            }
        }
    }

    IVEN("An decode str") {
        std::string str = "&h&amp;lt;";

        WHEN("Calling ResponceVector function") {
            str = DecodeHtmlStr(str);

            THEN("Vector size should remain unchanged") {
                REQUIRE(str == "&h&lt;");
            }
        }
    }

    GIVEN("An decode str") {
        std::string str = "Cat &lt;says&gt; &quot;Meow&quot;.M&amp;M&apos;s";

        WHEN("Calling ResponceVector function") {
            str = DecodeHtmlStr(str);

            THEN("Vector size should remain unchanged") {
                REQUIRE(str == "Cat <says> \"Meow\".M&M\`s");
            }
        }
    }

    GIVEN("An decode str") {
        std::string str = "&&&quot;;;; &apos; &lt; &gt; &amp;";

        WHEN("Calling ResponceVector function") {
            str = DecodeHtmlStr(str);

            THEN("Vector size should remain unchanged") {
                REQUIRE(str == "&&\";;; ` < > &");
            }
        }
    }

}