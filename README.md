# Yu-Gi-Oh Vending-Machine

#### 옜날에 즐겨했던 유희왕카드. 최근에 용산 아이파크몰에 있던 
#### 유희왕 카드 밴딩머신을 첨고하여 기획함.

## 개요!
#### - 먼저, 카드에 금액을 확인하고( 잔고 확인 )
#### - 상품 번호를 입력하여 상품을 수령한다.

#### - 그리고 상품 번호를 "1028"로 입력하면 "관리자 모드"애 진입하게 돼고
#### - "관리자 모드"에서는 제품 재고 조정, 밴딩머신 수입을 확인 할 수 있다.

## 상수
```
#define INIT_LIMIT_STUFF_ID_REAR    5
#define INIT_LIMIT_STUFF_NAME_REAR  21
#define INIT_LIMIT_STUFF            5

const int UNIT_STUFF_PRICE_16000 = 16000;
const int UNIT_STUFF_PRICE_24000 = 24000;
const int UNIT_PERMISSION_ADMIN  = 1028;

```

#### INIT_LIMIT_STUFF_ID_REAR    5 
#### -  상품코드의 이름 길이다.  NULL을 위해 4자리만 사용.

#### INIT_LIMIT_STUFF_NAME_REAR  21
#### -  상품 이름의 길이다. NULL을 위해 20 자리만 사용.

#### INIT_LIMIT_STUFF            5
#### -  기본 재고 갯수이다.

#### UNIT_STUFF_PRICE_16000 = 16000
#### -  상품의 가격 "16000"원이다.

#### UNIT_STUFF_PRICE_24000 = 24000
#### -  상춤의 가격 "24000"원 이다.

#### UNIT_PERMISSION_ADMIN  = 1028
#### 관리자모드 진입용. 상품명 1028 입력시 관리자 모드 진입.



## 물건 정보 상수

```
const int  UNIT_STUFF_PRICE []  = { UNIT_STUFF_PRICE_16000, UNIT_STUFF_PRICE_24000 };
const char UNIT_STUFF_ID    [INIT_LIMIT_STUFF][INIT_LIMIT_STUFF_ID_REAR]    = {"RC01", "RC02", "SD20", "SD21", "SD22"};
const char UNIT_STUFF_NAME  [INIT_LIMIT_STUFF] [INIT_LIMIT_STUFF_NAME_REAR] = {...};

```
#### UNIT_STUFF_PRICE [2]
#### -  물건의 금액 16000원, 24000원을 기억한다. 

#### UNIT_STUFF_ID [5][....]
#### -  각 물건의 ID값을 기억한다.

#### UNIT_STUFF_NAME[5][....]
#### -  각 물건의 이름을 기억한다.



## 구매자 정보
```

struct CustomerState {

    int customerBalance;

}; typedef struct CustomerState Customer;

```

#### customerBalance;
#### -  구매자 카드의 금액이다.

## 판매자 정보
```

struct StuffState {

    char stuffIdentity [INIT_LIMIT_STUFF_ID_REAR];
    char stuffName   [INIT_LIMIT_STUFF_NAME_REAR];
    int stuffPrice;
    int stuffQuantity;

}; typedef struct StuffState Stuff;

```

#### stuffIdentity [INIT_LIMIT_STUFF_ID_REAR]
#### -  물품의 상품코드. "initStuff(...)" 가 실행됀 후에는 변경해서는 안됀다!


#### stuffName   [INIT_LIMIT_STUFF_NAME_REAR]
#### -  물품의 이름. "initStuff(...)" 가 실행됀 후에는 변경해서는 안됀다!

#### stuffPrice
#### -  물품의 가격. "initStuff(...)" 가 실행됀 후에는 변경해서는 안됀다!

#### stuffQuantity
#### -  물품의 재고. 가변이다.



## 함수 기능
```
void initStuff(Stuff* stuff);
void initCustomer(Customer* customer);

int paymentCustomerVender(Stuff*stuff, Customer* customer, int index);
void provideStuffVender(Stuff* stuff, int index);
void showPackageBox(Stuff* stuff, int index);

void showVenderUI(Stuff* stuff, Customer* customer);


void toAdminArea(Stuff* stuff, Customer* customer, int isPermission, int totalSales);
void showTotalSalesVender(int totalSalse, int isPermission);
void setStuffStockVender(Stuff* stuff, int index, int isPermission);
```


void initStuff(Stuff* stuff)
```
  - Stuff 구조체를 초기화 한다.
  - Stuff의 "stuffQuantity" 이외의 값은 변경해서는 안됀다!
```


#### void initCustomer(Customer* customer)
```
  - Customer 구조체를 초기화 한다.
```


#### int paymentCustomerVender(Stuff* stuff, Customer* customer, int index)
```  
  -  Stuff : 물건 구조체, Customer : 구매자 구조체, index : 구매할 물품 번호
  -  물품을 선택하면 실행하는 함수이다.
```


#### void provideStuffVender(Stuff* stuff, int index);
```
  -  Stuff : 물건정보 구조체, index : 구매할 물건 번호.
  -  여기서 구매한 물품의 재고를 -1 한다
  -  paymentCustomerVender() 내부에서 사용하는 함수이다.
```

#### void showPackageBox(Stuff* stuff, int index)
```
  -  Stuff : 물건정보 구조체, index : 구매할 물건 번호.
  -  구매한 물품을 화면으로 보여준다.
```


#### void showVenderUI(Stuff* stuff, Customer* customer)
```
  -  현재 판매물품과 구매자 상태롤 보여준다.
```


## 함수 기능 : 관리자 영역

#### void toAdminArea(Stuff* stuff, Customer* customer, int isPermission, int totalSales)
```
  - Stuff : 싱품정보, Customer : 구매자 정보, isPermission : 입력한 번호, totalSalses :  현재 판매 금액
  - 상품번호로 1028 입력 시 분기. 관리자 모드로 분기한다!
  - isPermission 이 1028인지 검사한다.
```

#### void showTotalSalesVender(int totalSalse, int isPermission)
```
  - totalSales : 판매 금액, isPermission : 입력한 번호
  - 현재 판매 현황을 표시한다.
  - isPermission 이 1028인지 검사한다.
```

#### void setStuffStockVender(Stuff* stuff, int index, int isPermission)
```
  - Stuff 판매할 물품들, index 관리할 상품 번호, isPermission : 입력한 번호
  - index의 해당하는 물건의 재고를 설정한다 (0 ~ 5)
  - isPermission 이 1028인지 검사한다.
```


