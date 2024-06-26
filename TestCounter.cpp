//314638669, Barak10101998@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
using namespace doctest;

const int MIN_TESTS = 20;

int return_code = -1;

struct ReporterCounter : public ConsoleReporter
{
    ReporterCounter(const ContextOptions &input_options)
        : ConsoleReporter(input_options) {}

    void test_run_end(const TestRunStats &run_stats) override
    {
        if (run_stats.numAsserts >= MIN_TESTS)
        {
            std::cout << "You wrote " << run_stats.numAsserts << " tests! " << std::endl;
            return_code = 0;
        }
        else
        {
            std::cout << "Please write at least " << MIN_TESTS << " tests! " << std::endl;
            return_code = 1;
        }
    }
};

REGISTER_REPORTER("counter", 1, ReporterCounter);

int main(int argc, char **argv)
{
    Context context;
    context.addFilter("reporters", "counter");
//    clock_t begin = clock();
    context.run();
//    clock_t end = clock();
//    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
//    printf("%f",time_spent);
    return return_code;
}