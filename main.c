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
const char UNIT_STUFF_NAME  [INIT_LIMIT_STUFF] [INIT_LIMIT_STUFF_NAME_REAR] = {"�� ���Ƽ �÷��� 1",
                                                                                "�� ���Ƽ �÷��� 2",
                                                                                "��Ȳ���� �ɹ�",
                                                                                "������ ����Ʈ",
                                                                                "�巡��� ����"};


struct CustomerState {

    int customerBalance;                    // �󸶳� ��ó�ΰ� �ִ���???

}; typedef struct CustomerState Customer;



/*******************************************************************

* stuffIdentity ������ ���� �ĺ��ڵ�
* stuffName     ������ ���� �̸�
* stuffPrice    ������ ���� ����
* stuffQuantity ������ ���� ( ��� )


* ���⼭ stuffIdentity, stuffName,
  stuffPrice �� �ʱ�ȭ �Ű� ������ �Һ�. ���� �����ؼ��� �ȉ´�!
  initStuff(...) ���Ŀ� ���� �ٲٸ� �ȉ´�!

* stuffQuantity �� �ش� ������ ��� �ǹ�... ���� / �������̴�.

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
        action = getInt("��, ������ ��ǰ ��ȣ�� �Է��ϼ���! ����� 0");

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



/************** ���� ���Ǳ� ��Ȳ ******************/

void showVenderUI(Stuff* stuff, Customer* customer){

    int i = 0;

    printf("\n================= ���Ǳ� =====================\n");
    printf("��ȣ       �̸�                 ����      ���\n");
    for(i = 0; i < INIT_LIMIT_STUFF; i++) {
        printf("%2d  %20s    %8d    %5d\n", (i + 1),
                                            stuff[i].stuffName,
                                            stuff[i].stuffPrice,
                                            stuff[i].stuffQuantity);
    }
    printf("==============================================\n");
    printf("�ܰ� : %d", customer[0].customerBalance );

    return;
}




/******************* ���ǰ� ���� *********************/

int paymentCustomerVender(Stuff* stuff, Customer* customer, int index){

    int returnValue  = 0;

    if( stuff[index -1].stuffQuantity < 1 ){

        puts("\n    ==== ��ǰ�� ��� �������! ====\n");
        returnValue = 0;


    } else if ( customer->customerBalance >= stuff[index -1].stuffPrice ){

        customer->customerBalance = customer->customerBalance - stuff[index - 1].stuffPrice;
        provideStuffVender(stuff, index);

        returnValue = stuff[index - 1].stuffPrice;;

    } else {

        puts("\n    ====ī�忡 ����� ���� ���׿�!====\n");
        returnValue = 0;
    }

    return returnValue;
}



/******************************************

*               ���� ���� func.

*   int paymentCustomerVender(...) ���ο��� ���!

******************************************/

void provideStuffVender(Stuff* stuff, int index){
//
//    puts("      ===========");
//    printf("      =  %5s  =\n", (stuff[index -1].stuffIdentity));
//    puts("      ===========");
//    printf("%s �Դϴ�!\n\n", stuff[index - 1].stuffName);

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





/*************** ������ ���� **************************

*   setStuffStockVender(...)
*   showTotalSalesVender(...)

*   �ش� �ż���� toAdminArea(...) ���� ���� �޼���.

******************************************************/

void toAdminArea(Stuff* stuff, Customer* customer, int isPermission, int totalSales){

    int isLoop = 0;
    int action = 0;

    if(isPermission != UNIT_PERMISSION_ADMIN)
        return;

    while(!isLoop){


        showVenderUI(stuff, customer);
        action = getInt("\n1. ��� ����\n2. ���� Ȯ��\n0. ������");
        system("cls");

        switch(action){
            case 0: isLoop = 1; break;
            case 1: setStuffStockVender(stuff, getInt(" ������ �ε���"), isPermission) ; break;
            case 2: showTotalSalesVender(totalSales, isPermission);
        }
    }
    return;
}


void setStuffStockVender(Stuff* stuff, int index, int isPermission){

    int changeStuffStock = 0;


    if (isPermission != UNIT_PERMISSION_ADMIN)
            return;

    changeStuffStock = getIntRange("��� �Է��ϼ��� ", 0, INIT_LIMIT_STUFF);
    stuff[index - 1].stuffQuantity = changeStuffStock;

    return;
}


void showTotalSalesVender(int totalSales, int isPermission){


    if (isPermission != UNIT_PERMISSION_ADMIN )
        return;


    printf("\n���� %d�� �޾���!!\n", totalSales);
    return;
}






/*************** ��� �ʱ�ȭ ****************/

void initCustomer(Customer* customer){

    puts("====ī�忡 �ִ� �ݾ��� �Է��ϼ���!====");
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
