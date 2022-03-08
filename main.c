#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_LIMIT_STUFF_ID_REAR    5
#define INIT_LIMIT_STUFF_NAME_REAR  21
#define INIT_LIMIT_STUFF            5


const int UNIT_STUFF_PRICE_16000 = 16000;
const int UNIT_STUFF_PRICE_24000 = 24000;
const int UNIT_PERMISSION_ADMIN  = 1028;



const int  UNIT_STUFF_PRICE []                                              = { 16000, 24000 };
const char UNIT_STUFF_ID    [INIT_LIMIT_STUFF][INIT_LIMIT_STUFF_ID_REAR]    = {"RC01", "RC02", "SD20", "SD21", "SD22"};
const char UNIT_STUFF_NAME  [INIT_LIMIT_STUFF] [INIT_LIMIT_STUFF_NAME_REAR] = {"더 레어리티 컬렉션 1",
                                                                                "더 레어리티 컬렉션 2",
                                                                                "사황제의 능묘",
                                                                                "데빌의 게이트",
                                                                                "드래고닉 군단"};


struct CustomerState {

    int customerBalance;                    // 얼마나 꽁처두고 있느냐???

}; typedef struct CustomerState Customer;



/*******************************************************************

* stuffIdentity 물건의 고유 식별코드
* stuffName     물건의 교유 이름
* stuffPrice    물건의 교유 가격
* stuffQuantity 물건의 수량 ( 재고 )


* 여기서 stuffIdentity, stuffName,
  stuffPrice 는 초기화 돼고 나서는 불변. 값을 수정해서는 안됀다!
  initStuff(...) 이후에 값은 바꾸면 안됀다!

* stuffQuantity 는 해당 물건의 재고를 의미... 가변 / 유동적이다.

********************************************************************/



struct StuffState {

    char stuffIdentity [INIT_LIMIT_STUFF_ID_REAR];
    char stuffName   [INIT_LIMIT_STUFF_NAME_REAR];
    int stuffPrice;
    int stuffQuantity;

}; typedef struct StuffState Stuff;




int getInt(char* informationString);
int getIntRange(char* informationString, int frontLimit, int rearLimit);




void initStuff(Stuff* stuff);
void initCustomer(Customer* customer);

int paymentCustomerVender(Stuff*stuff, Customer* customer, int index);
void provideStuffVender(Stuff* stuff, int index);
void showPackageBox(Stuff* stuff, int index);

void showVenderUI(Stuff* stuff, Customer* customer);


void toAdminArea(Stuff* stuff, Customer* customer, int isPermission, int totalSales);
void showTotalSalesVender(int totalSalse, int isPermission);
void setStuffStockVender(Stuff* stuff, int index, int isPermission);





int main() {

    int isLoop = 0;
    int action = 0;
    int totalSales = 0;

    Stuff stuff [INIT_LIMIT_STUFF] = {
    { "", "", 0, 0 }, {}};
    Customer customer = {0 };



    initStuff(stuff);
    initCustomer(&customer);

    while(!isLoop){

        showVenderUI(stuff, &customer);
        action = getInt("원, 구매할 상품 번호를 입력하세요! 종료는 0");

        system("cls");
        switch(action) {
            case 0: isLoop =1; break;
            case 1028: toAdminArea(stuff, &customer, action, totalSales); break;

            case 1: totalSales += paymentCustomerVender(stuff, &customer, action); break;
            case 2: totalSales += paymentCustomerVender(stuff, &customer, action); break;
            case 3: totalSales += paymentCustomerVender(stuff, &customer, action); break;
            case 4: totalSales += paymentCustomerVender(stuff, &customer, action); break;
            case 5: totalSales += paymentCustomerVender(stuff, &customer, action); break;
        }
    }
    return 0;
}



/************** 현재 자판기 상황 ******************/

void showVenderUI(Stuff* stuff, Customer* customer){

    int i = 0;

    printf("\n================= 자판기 =====================\n");
    printf("번호       이름                 가격      재고\n");
    for(i = 0; i < INIT_LIMIT_STUFF; i++) {
        printf("%2d  %20s    %8d    %5d\n", (i + 1),
                                            stuff[i].stuffName,
                                            stuff[i].stuffPrice,
                                            stuff[i].stuffQuantity);
    }
    printf("==============================================\n");
    printf("잔고 : %d", customer[0].customerBalance );

    return;
}




/******************* 물건값 지불 *********************/

int paymentCustomerVender(Stuff* stuff, Customer* customer, int index){

    int returnValue  = 0;

    if( stuff[index -1].stuffQuantity < 1 ){

        puts("\n    ==== 상품이 모두 동났어요! ====\n");
        returnValue = 0;


    } else if ( customer->customerBalance >= stuff[index -1].stuffPrice ){

        customer->customerBalance = customer->customerBalance - stuff[index - 1].stuffPrice;
        provideStuffVender(stuff, index);

        returnValue = stuff[index - 1].stuffPrice;;

    } else {

        puts("\n    ====카드에 충분한 돈이 없네요!====\n");
        returnValue = 0;
    }

    return returnValue;
}



/******************************************

*               물건 수령 func.

*   int paymentCustomerVender(...) 내부에서 사용!

******************************************/

void provideStuffVender(Stuff* stuff, int index){
//
//    puts("      ===========");
//    printf("      =  %5s  =\n", (stuff[index -1].stuffIdentity));
//    puts("      ===========");
//    printf("%s 입니다!\n\n", stuff[index - 1].stuffName);

    showPackageBox(stuff, index);
    stuff[index - 1].stuffQuantity--;

    return;

}


/*********** Just ASCII Art *************/

void showPackageBox(Stuff* stuff, int index){

    puts(" =============================");
    puts("/__________________________ /|");
    puts("|                          | |");
    puts("|                          | |");
  printf("|    %20s  | |\n", stuff[index - 1].stuffName);
    puts("|                          | |");
    puts("|                          |/");
    puts("============================");

    return;
}





/*************** 관리자 영역 **************************

*   setStuffStockVender(...)
*   showTotalSalesVender(...)

*   해당 매세드는 toAdminArea(...) 내부 전용 메서드.

******************************************************/

void toAdminArea(Stuff* stuff, Customer* customer, int isPermission, int totalSales){

    int isLoop = 0;
    int action = 0;

    if(isPermission != UNIT_PERMISSION_ADMIN)
        return;

    while(!isLoop){


        showVenderUI(stuff, customer);
        action = getInt("\n1. 재고 관리\n2. 수익 확인\n0. 나가기");
        system("cls");

        switch(action){
            case 0: isLoop = 1; break;
            case 1: setStuffStockVender(stuff, getInt(" 관리할 인덱스"), isPermission) ; break;
            case 2: showTotalSalesVender(totalSales, isPermission);
        }
    }
    return;
}


void setStuffStockVender(Stuff* stuff, int index, int isPermission){

    int changeStuffStock = 0;


    if (isPermission != UNIT_PERMISSION_ADMIN)
            return;

    changeStuffStock = getIntRange("재고를 입력하세요 ", 0, INIT_LIMIT_STUFF);
    stuff[index - 1].stuffQuantity = changeStuffStock;

    return;
}


void showTotalSalesVender(int totalSales, int isPermission){


    if (isPermission != UNIT_PERMISSION_ADMIN )
        return;


    printf("\n현재 %d원 받았음!!\n", totalSales);
    return;
}






/*************** 어레이 초기화 ****************/

void initCustomer(Customer* customer){

    puts("====카드에 있는 금액을 입력하세요!====");
    scanf("%d", &customer[0].customerBalance);

    return;
}


void initStuff(Stuff* stuff) {

    int i= 0;

    for(i =0; i < INIT_LIMIT_STUFF; i++){

        strcpy(stuff[i].stuffIdentity, UNIT_STUFF_ID[i]);
        strcpy(stuff[i].stuffName,  UNIT_STUFF_NAME[i]);

        if(i < 2){

            stuff[i].stuffPrice = UNIT_STUFF_PRICE_24000;

        } else {

            stuff[i].stuffPrice = UNIT_STUFF_PRICE_16000;
        }
        stuff[i].stuffQuantity = INIT_LIMIT_STUFF;
    }
    return;
}
