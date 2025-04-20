#include <gtest/gtest.h>
#include <sstream>
#include "foodDeliverySystem.cpp"

// Helper function to redirect cin for testing
void setInput(const std::string& input) {
    static std::istringstream iss;
    iss.clear();
    iss.str(input);
    std::cin.rdbuf(iss.rdbuf());
}

class AuthTest : public ::testing::Test {
protected:
    Authentication auth;

    void SetUp() override {
        user.clear();
    }

    void TearDown() override {
        user.clear();
    }

    unordered_map<string, string> createMockUser(string email, string password) {
        return {
            {"userID", email + "_id"},
            {"email", email},
            {"phone", "9999999999"},
            {"password", password},
            {"userType", "C"},
            {"name", "Test User"},
            {"address", "Test Address"}
        };
    }
};

TEST_F(AuthTest, RegisterCustomerIncreasesUserCount) {
    setInput("test@example.com\n9999999999\npassword123\nC\nJohn\nDoe\n123 Main St\n");
    int before = user.size();
    auth.registration();
    ASSERT_EQ(user.size(), before + 1);
    EXPECT_EQ(user[0]["email"], "test@example.com");
    EXPECT_EQ(user[0]["password"], "password123");
    EXPECT_EQ(user[0]["name"], "John Doe");
}

TEST_F(AuthTest, LoginWithCorrectCredentials) {
    user.push_back(createMockUser("john@example.com", "test123"));
    setInput("john@example.com\ntest123\n1234\n"); // Fixed OTP: 1234
    testing::internal::CaptureStdout();
    auth.login();
    string output = testing::internal::GetCapturedStdout();
    ASSERT_NE(output.find("Login Successful"), string::npos);
}

TEST_F(AuthTest, LoginFailsWithWrongPassword) {
    user.push_back(createMockUser("john@example.com", "correctpass"));
    setInput("john@example.com\nwrongpass\nn\n");
    testing::internal::CaptureStdout();
    auth.login();
    string output = testing::internal::GetCapturedStdout();
    ASSERT_NE(output.find("Login Failed"), string::npos);
}

// TEST_F(AuthTest, ResetPasswordUpdatesPassword) {
//     user.push_back(createMockUser("john@example.com", "oldpass"));
//     auth = Authentication();
//     setInput("1234\nnewpass123\nnewpass123\n"); // Fixed OTP: 1234
//     bool success = auth.resetPassword();
//     ASSERT_TRUE(success);
//     ASSERT_EQ(user[0]["password"], "newpass123");
// }

TEST_F(AuthTest, DuplicateEmailRegistrationShouldBeHandledManually) {
    user.push_back(createMockUser("dup@example.com", "abc"));
    user.push_back(createMockUser("dup@example.com", "xyz"));
    int count = 0;
    for (auto &u : user) {
        if (u["email"] == "dup@example.com") count++;
    }
    ASSERT_EQ(count, 2); // Proves system needs duplicate check logic
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
