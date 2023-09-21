#include <gtest/gtest.h>


extern "C" {
    #include "sensorFetchAndSend.c"
}

int called = 0;
void addData(char* name, int data){
    printf("%s\n", name );
    called++;
}

void pushData(void) {

}

static int id = 0;


unsigned int supersensor_get(){
    return id;
}
void supersensor_init(){
}







class FetchAndSendTest : public testing::Test {
protected:
	void SetUp() override {
		//game_initialize();	/* Without this the Tests could break*/
	}
};


TEST_F(FetchAndSendTest,addDataShouldBeCalledTwice){
    //ARRANGE
    called = 0;
    //ACT
    fetchAndSend();

    //ASSERT
    ASSERT_EQ(called, 2);
}


