/*#include "gmock/gmock.h"

int main()
{
	testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
*/

#include <stdio.h>
#include <string>
#include <stdlib.h>

#define CLEAR_SCREEN "\033[H\033[2J"

void selectCarType(int car_type, int *stack);
void selectEngine(int engine, int *stack);
void selectbrakeSystem(int brake_system, int *stack);
void selectSteeringSystem(int steer_system, int *stack);
void runProducedCar(const int * const stack);
void delay(int ms);

using namespace std;

/* strategy interface */
class Engine {
    virtual std::string getName() const = 0;
    virtual ~Engine() = default;
};

class BrakeSystem {
public:
    virtual std::string getBrand() const = 0;
    virtual ~BrakeSystem() = default;
};
class SteeringSystem
{
public:
    virtual std::string getType() const = 0;
    virtual ~SteeringSystem() = default;
};








enum QuestionType
{   
    QuestionType_MIN = -1,
    CarType_Q = 0,
    Engine_Q,
    brakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
    QuestionType_MAX
};

enum CarType
{
    CarType_MIN = 0,
    SEDAN = 1,
    SUV,
    TRUCK,
    CarType_MAX
};

enum Engine
{
    Engine_MIN = -1,
    GM = 1,
    TOYOTA,
    WIA,
    BROKEN,
    Engine_MAX
};

enum BrakeSystem
{
    BrakeSystem_MIN = -1,
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B,
    BrakeSystem_MAX
};

enum SteeringSystem
{
    SteeringSystem_MIN = -1,
    BOSCH_S = 1,
    MOBIS,
    SteeringSystem_MAX
};

enum RunTest
{
    RunTest_MIN = -1,
    RUN = 1,
    TEST = 2,
    RunTest_MAX
};
void delay(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}

void print_car_option()
{
    printf(CLEAR_SCREEN);
    printf("        ______________\n");
    printf("       /|            | \n");
    printf("  ____/_|_____________|____\n");
    printf(" |                      O  |\n");
    printf(" '-(@)----------------(@)--'\n");
    printf("===============================\n");
    printf("어떤 차량 타입을 선택할까요?\n");
    printf("1. Sedan\n");
    printf("2. SUV\n");
    printf("3. Truck\n");
    printf("===============================\n");
}

void print_brake_system_option()
{
    printf(CLEAR_SCREEN);
    printf("어떤 제동장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. MANDO\n");
    printf("2. CONTINENTAL\n");
    printf("3. BOSCH\n");
    printf("===============================\n");
}

void print_engine_option()
{
    printf(CLEAR_SCREEN);
    printf("어떤 엔진을 탑재할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. GM\n");
    printf("2. TOYOTA\n");
    printf("3. WIA\n");
    printf("4. 고장난 엔진\n");
    printf("===============================\n");
}

void print_steer_system_option()
{
    printf(CLEAR_SCREEN);
    printf("어떤 조향장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. BOSCH\n");
    printf("2. MOBIS\n");
    printf("===============================\n");
}

void print_run_test()
{
    printf(CLEAR_SCREEN);
    printf("멋진 차량이 완성되었습니다.\n");
    printf("어떤 동작을 할까요?\n");
    printf("0. 처음 화면으로 돌아가기\n");
    printf("1. RUN\n");
    printf("2. Test\n");
    printf("===============================\n");
}

#define EXIT_PROGRAM    (0xdeaddead)
#define INVALID_INPUT   (0xdeadbeef)
int get_parsed_input()
{
    char buf[100];
    int step = CarType_Q;
    printf("INPUT > ");
    fgets(buf, sizeof(buf), stdin);

    // 엔터 개행문자 제거
    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);

    if (!strcmp(buf, "exit"))
    {
        printf("바이바이\n");
        return EXIT_PROGRAM;
    }

    // 숫자로 된 대답인지 확인
    char* checkNumber;
    int parsed_input = strtol(buf, &checkNumber, 10); // 문자열을 10진수로 변환
    if (*checkNumber != '\0')
    {
        printf("ERROR :: 숫자만 입력 가능\n");
        delay(800);
        return INVALID_INPUT;
    }

    return parsed_input;
}

int is_car_type_valid(int car_type)
{
    if (car_type >= CarType_MAX || car_type <= CarType_MIN)
        return INVALID_INPUT;

    return 0;
}

int is_engine_valid(int engine)
{
    if (engine >= Engine_MAX || engine <= Engine_MIN)
        return INVALID_INPUT;

    return 0;
}

int is_steer_system_valid(int steer_system)
{
    if (steer_system >= SteeringSystem_MAX || steer_system <= SteeringSystem_MIN)
        return INVALID_INPUT;

    return 0;
}

int is_brake_system_valid(int brake_system)
{
    if (brake_system >= BrakeSystem_MAX || brake_system <= BrakeSystem_MIN)
        return INVALID_INPUT;

    return 0;
}

int is_run_test_valid(int run_test)
{
    if (run_test >= RunTest_MAX || run_test <= RunTest_MIN)
        return INVALID_INPUT;

    return 0;
}

int validate_input(int input, const int * const step)
{
    if (*step == CarType_Q && is_car_type_valid(input))
    {
        printf("ERROR :: 차량 타입은 %d ~ %d 범위만 선택 가능\n", CarType_MIN + 1, CarType_MAX - 1);
        delay(800);
        return INVALID_INPUT;
    }
    else if (*step == Engine_Q && is_engine_valid(input))
    {
        printf("ERROR :: 엔진은 %d ~ %d 범위만 선택 가능\n", Engine_MIN + 2, Engine_MAX - 1);
        delay(800);
        return INVALID_INPUT;
    }

    if (*step == brakeSystem_Q && is_brake_system_valid(input))
    {
        printf("ERROR :: 제동장치는 %d ~ %d 범위만 선택 가능\n", BrakeSystem_MIN + 2, BrakeSystem_MAX - 1);
        delay(800);
        return INVALID_INPUT;
    }

    if (*step == SteeringSystem_Q && is_steer_system_valid(input))
    {
        printf("ERROR :: 조향장치는 %d ~ %d 범위만 선택 가능\n", SteeringSystem_MIN + 2, SteeringSystem_MAX - 1);
        delay(800);
        return INVALID_INPUT;
    }

    if (*step == Run_Test && is_run_test_valid(input))
    {
        printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
        delay(800);
        return INVALID_INPUT;
    }

    return 0;
}

#define SUCCESS (1)
#define FAIL    (0)
int go_back_to_first(int input, int *step)
{
    if (input == CarType_Q && *step == Run_Test)
    {
        *step = CarType_Q;
        return SUCCESS;
    }
    return 0;
}

int go_back_to_previous(int input, int* step)
{
    if (input == CarType_Q && *step >= Engine_Q)
    {
        *step -= 1;
        return SUCCESS;
    }
    return FAIL;
}

void selectCarType(int car_type, int *stack)
{
    stack[CarType_Q] = car_type;
    if (car_type == SEDAN)
        printf("차량 타입으로 Sedan을 선택하셨습니다.\n");
    if (car_type == SUV)
        printf("차량 타입으로 SUV을 선택하셨습니다.\n");
    if (car_type == TRUCK)
        printf("차량 타입으로 Truck을 선택하셨습니다.\n");
}

void selectEngine(int engine, int *stack)
{
    stack[Engine_Q] = engine;
    if (engine == GM)
        printf("GM 엔진을 선택하셨습니다.\n");
    else if (engine == TOYOTA)
        printf("TOYOTA 엔진을 선택하셨습니다.\n");
    else if (engine == WIA)
        printf("WIA 엔진을 선택하셨습니다.\n");
    else if (engine == BROKEN)
        printf("고장난 엔진을 선택하셨습니다.\n");
}

void selectbrakeSystem(int brake_system, int *stack)
{
    stack[brakeSystem_Q] = brake_system;
    if (brake_system == MANDO)
        printf("MANDO 제동장치를 선택하셨습니다.\n");
    if (brake_system == CONTINENTAL)
        printf("CONTINENTAL 제동장치를 선택하셨습니다.\n");
    if (brake_system == BOSCH_B)
        printf("BOSCH 제동장치를 선택하셨습니다.\n");
}

void selectSteeringSystem(int steer_system, int *stack)
{
    stack[SteeringSystem_Q] = steer_system;
    if (steer_system == BOSCH_S)
        printf("BOSCH 조향장치를 선택하셨습니다.\n");
    if (steer_system == MOBIS)
        printf("MOBIS 조향장치를 선택하셨습니다.\n");
}

#define ENABLE_LOG  (1)
#define DISABLE_LOG (0)
int isValidCheck(int enable_log, const int * const stack)
{
    if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
    {
        if (enable_log) {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("Sedan에는 Continental제동장치 사용 불가\n");
        }
        return false;
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        if (enable_log) {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("SUV에는 TOYOTA엔진 사용 불가\n");
        }
        return false;
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        if (enable_log) {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("Truck에는 WIA엔진 사용 불가\n");
        }
        return false;
    }
    else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
    {
        if (enable_log) {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("Truck에는 Mando제동장치 사용 불가\n");
        }
        return false;
    }
    else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        if (enable_log) {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            if (stack[SteeringSystem_Q] == MOBIS)
            {
                printf("Bosch엔진에는 Mobis제동장치 사용 불가\n");
            }
        }
        return false;
    }
    else
    {
        if (enable_log) {
            printf("자동차 부품 조합 테스트 결과 : PASS\n");
        }
        return true;
    }
    return true;
}

void runProducedCar(const int * const stack)
{
    if (isValidCheck(DISABLE_LOG, stack) == false)
    {
        printf("자동차가 동작되지 않습니다\n");
    }
    else
    {
        if (stack[Engine_Q] == BROKEN)
        {
            printf("엔진이 고장나있습니다.\n");
            printf("자동차가 움직이지 않습니다.\n");
        }
        else
        {
            if (stack[CarType_Q] == SEDAN)
                printf("Car Type : Sedan\n");
            if (stack[CarType_Q] == SUV)
                printf("Car Type : SUV\n");
            if (stack[CarType_Q] == TRUCK)
                printf("Car Type : Truck\n");
            if (stack[Engine_Q] == GM)
                printf("Engine : GM\n");
            if (stack[Engine_Q] == TOYOTA)
                printf("Engine : TOYOTA\n");
            if (stack[Engine_Q] == WIA)
                printf("Engine : WIA\n");
            if (stack[brakeSystem_Q] == MANDO)
                printf("Brake System : Mando");
            if (stack[brakeSystem_Q] == CONTINENTAL)
                printf("Brake System : Continental\n");
            if (stack[brakeSystem_Q] == BOSCH_B)
                printf("Brake System : Bosch\n");
            if (stack[SteeringSystem_Q] == BOSCH_S)
                printf("SteeringSystem : Bosch\n");
            if (stack[SteeringSystem_Q] == MOBIS)
                printf("SteeringSystem : Mobis\n");

            printf("자동차가 동작됩니다.\n");
        }
    }
}

int main()
{
    int stack[10];
    int step = CarType_Q;

    while (1)
    {
        if (step == CarType_Q)
            print_car_option();
        else if (step == Engine_Q)
            print_engine_option();
        else if (step == brakeSystem_Q)
            print_brake_system_option();
        else if (step == SteeringSystem_Q)
            print_steer_system_option();
        else if (step == Run_Test)
            print_run_test();

        int input_from_user = get_parsed_input();

        if (input_from_user == EXIT_PROGRAM)
            break;
        else if (input_from_user == INVALID_INPUT)
            continue;

        if (validate_input(input_from_user, &step) == INVALID_INPUT)
            continue;

        if (go_back_to_first(input_from_user, &step) == SUCCESS)
            continue;

        if (go_back_to_previous(input_from_user, &step) == SUCCESS)
            continue;

        if (step == CarType_Q)
        {
            selectCarType(input_from_user, stack);
            delay(800);
            step = Engine_Q;
        }
        else if (step == Engine_Q)
        {
            selectEngine(input_from_user, stack);
            delay(800);
            step = brakeSystem_Q;
        }
        else if (step == brakeSystem_Q)
        {
            selectbrakeSystem(input_from_user, stack);
            delay(800);
            step = SteeringSystem_Q;
        }
        else if (step == SteeringSystem_Q)
        {
            selectSteeringSystem(input_from_user, stack);
            delay(800);
            step = Run_Test;
        }
        else if (step == Run_Test)
        {
            if (input_from_user == RUN) {
                runProducedCar(stack);
                delay(2000);
            }
            else if (input_from_user == TEST) {
                printf("Test...\n");
                delay(1500);
                isValidCheck(ENABLE_LOG, stack);
                delay(2000);
            }
        }
    }
}