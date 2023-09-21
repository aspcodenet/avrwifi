#include <gtest/gtest.h>
#include "fff.h"
DEFINE_FFF_GLOBALS;



extern "C" {
    #include "sensorFetchAndSend.c"
}


FAKE_VOID_FUNC(addData,char *, int);

FAKE_VOID_FUNC(pushData);

static int id = 0;

FAKE_VALUE_FUNC(unsigned int, supersensor_get);
FAKE_VOID_FUNC(supersensor_init);






class FetchAndSendTest : public testing::Test {
protected:
	void SetUp() override {
		//game_initialize();	/* Without this the Tests could break*/
	}
};


TEST_F(FetchAndSendTest,addDataShouldBeCalledTwice){
    //ARRANGE
    //ACT
    fetchAndSend();

    //ASSERT
    ASSERT_EQ(addData_fake.call_count, 2);
}

TEST_F(FetchAndSendTest,addDataShouldSendCorrectData){
    //ARRANGE
    supersensor_get_fake.return_val = 99;
    //ACT
    fetchAndSend();

    //ASSERT
    ASSERT_EQ(addData_fake.arg0_val, "field2");
    ASSERT_EQ(addData_fake.arg1_val, 99);
}




