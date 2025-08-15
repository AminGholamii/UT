#ifndef WAVE_CONFIGS_HPP_INCLUDE
#define WAVE_CONFIGS_HPP_INCLUDE

#include <vector>
#include <map>
#include <string>

struct AttackWave {
    // تعداد بادکنک‌های مهاجم بر اساس نوعشان
    std::map<std::string, int> enemiesCount;

    // فاصله زمانی بین ورود بادکنک‌ها (به صورت بازه تصادفی بر حسب میلی‌ثانیه)
    std::pair<int, int> enemyLaunchGapMs;
};

// برنامه موج‌های حمله
const std::vector<AttackWave> ATTACKING_PLAN = {
    { { {"Normal", 5} }, {500, 700} },
    { { {"Normal", 10}, {"Pregnant", 5} }, {400, 600} },
    { { {"Normal", 15}, {"Pregnant", 10} }, {200, 400} }
};

// زمان بین پایان یک موج و شروع موج بعدی (بر حسب ثانیه)
const int WAVE_LAUNCH_GAP_SECS = 10;

#endif