#include <DogFood.hpp>

#include "unittest.hpp"

//
// Unit Test
//
// Validate Metric
//
void UnitTest::Setup() {

    //
    // Metric Name
    //

    // Name length
    AddTest("Metric Name", "Name Length", [](void) {
        {
            const std::string too_short = "";
            AssertFalse(DogFood::ValidateMetricName(too_short), "Empty name should not be valid");
        }

        for (int i = 1; i < 201; i++)
        {
            std::string just_right(i, 'x');
            AssertTrue(DogFood::ValidateMetricName(just_right), "Name of length " + std::to_string(i) + " should be valid");
        }

        {
            const std::string too_long(201, 'x');
            AssertFalse(DogFood::ValidateMetricName(too_long), "Name longer than 201 characters should not be valid");
        }

    });

    // Invalid name characters
    AddTest("Metric Name", "Invalid characters", [](void) {
        std::string test_name = "Metric Name";
        for (char c = 0; c < CHAR_MAX; c++) {
            test_name[6] = c;
            if (std::isalnum(c) || c == '_' || c == '.') {
                std::string message = "Name containing ASCII '" + std::to_string(c) + "' should be valid";
                AssertTrue(DogFood::ValidateMetricName(test_name), message);
            } else {
                std::string message = "Name containing ASCII '" + std::to_string(c) + "' should not be valid: ";
                AssertFalse(DogFood::ValidateMetricName(test_name), message);
            }
        }
    });

    // Invalid starting character
    AddTest("Metric Name", "Invalid characters", [](void) {
        std::string test_name = "MetricName";
        for (char c = 0; c < CHAR_MAX; c++) {
            test_name[0] = c;
            if (std::isalpha(c)) {
                std::string message = "Name beginning with ASCII '" + std::to_string(c) + "' should be valid";
                AssertTrue(DogFood::ValidateMetricName(test_name), message);
            } else {
                std::string message = "Name beginning with ASCII '" + std::to_string(c) + "' should not be valid: ";
                AssertFalse(DogFood::ValidateMetricName(test_name), message);
            }
        }
    });

    //
    // Sample Rate
    //
    AddTest("Sample Rate", "Sample Rate", [](void) {
        AssertFalse(DogFood::ValidateSampleRate(-1.0), "Negative sample rate should not be valid");
        AssertTrue(DogFood::ValidateSampleRate(0.0), "Sample rate equal to 0 should be valid");
        AssertTrue(DogFood::ValidateSampleRate(0.5), "Positive sample rate between 0 and 1 should be valid");
        AssertTrue(DogFood::ValidateSampleRate(1.0), "Sample rate equal to 1 should be valid");
        AssertFalse(DogFood::ValidateSampleRate(2.0), "Positive sample rate greater than 1 should not be valid");
    });

    //
    // Payload Size
    //
    AddTest("Payload Size", "Payload Size", [](void) {
        const std::string max_payload(65507, 'x');
        AssertTrue(DogFood::ValidatePayloadSize(max_payload), "Payload should not be longer than 65507 bytes");
    });
}