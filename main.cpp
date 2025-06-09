/*#include "gmock/gmock.h"

int main()
{
	testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CLEAR_SCREEN "\033[H\033[2J"

int stack[10];

void selectCarType(int car_type);
void selectEngine(int engine);
void selectbrakeSystem(int brake_system);
void selectSteeringSystem(int steer_system);
void runProducedCar();
void testProducedCar();
void delay(int ms);

enum QuesionType
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
    printf("� ���� Ÿ���� �����ұ��?\n");
    printf("1. Sedan\n");
    printf("2. SUV\n");
    printf("3. Truck\n");
    printf("===============================\n");
}

void print_brake_system_option()
{
    printf(CLEAR_SCREEN);
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. MANDO\n");
    printf("2. CONTINENTAL\n");
    printf("3. BOSCH\n");
    printf("===============================\n");
}

void print_engine_option()
{
    printf(CLEAR_SCREEN);
    printf("� ������ ž���ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. GM\n");
    printf("2. TOYOTA\n");
    printf("3. WIA\n");
    printf("4. ���峭 ����\n");
    printf("===============================\n");
}

void print_steer_system_option()
{
    printf(CLEAR_SCREEN);
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. BOSCH\n");
    printf("2. MOBIS\n");
    printf("===============================\n");
}

void print_run_test()
{
    printf(CLEAR_SCREEN);
    printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
    printf("� ������ �ұ��?\n");
    printf("0. ó�� ȭ������ ���ư���\n");
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

    // ���� ���๮�� ����
    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);

    if (!strcmp(buf, "exit"))
    {
        printf("���̹���\n");
        return EXIT_PROGRAM;
    }

    // ���ڷ� �� ������� Ȯ��
    char* checkNumber;
    int answer = strtol(buf, &checkNumber, 10); // ���ڿ��� 10������ ��ȯ
    if (*checkNumber != '\0')
    {
        printf("ERROR :: ���ڸ� �Է� ����\n");
        delay(800);
        return INVALID_INPUT;
    }

    return answer;
}

int is_car_type_valid(int answer)
{
    if (answer >= CarType_MAX || answer <= CarType_MIN)
        return INVALID_INPUT;

    return 0;
}

int is_engine_valid(int answer)
{
    if (answer >= Engine_MAX || answer <= Engine_MIN)
        return INVALID_INPUT;

    return 0;
}

int is_steer_system_valid(int answer)
{
    if (answer >= SteeringSystem_MAX || answer <= SteeringSystem_MIN)
        return INVALID_INPUT;

    return 0;
}

int is_brake_system_valid(int answer)
{
    if (answer >= BrakeSystem_MAX || answer <= BrakeSystem_MIN)
        return INVALID_INPUT;

    return 0;
}

int is_run_test_valid(int answer)
{
    if (answer >= RunTest_MAX || answer <= RunTest_MIN)
        return INVALID_INPUT;

    return 0;
}

int check_valid_answer(int step, int answer)
{
    if (step == CarType_Q && is_car_type_valid(answer))
    {
        printf("ERROR :: ���� Ÿ���� %d ~ %d ������ ���� ����\n", CarType_MIN + 1, CarType_MAX - 1);
        delay(800);
        return INVALID_INPUT;
    }
    else if (step == Engine_Q && is_engine_valid(answer))
    {
        printf("ERROR :: ������ %d ~ %d ������ ���� ����\n", Engine_MIN + 2, Engine_MAX - 1);
        delay(800);
        return INVALID_INPUT;
    }

    if (step == brakeSystem_Q && is_brake_system_valid(answer))
    {
        printf("ERROR :: ������ġ�� %d ~ %d ������ ���� ����\n", BrakeSystem_MIN + 2, BrakeSystem_MAX - 1);
        delay(800);
        return INVALID_INPUT;
    }

    if (step == SteeringSystem_Q && is_steer_system_valid(answer))
    {
        printf("ERROR :: ������ġ�� %d ~ %d ������ ���� ����\n", SteeringSystem_MIN + 2, SteeringSystem_MAX - 1);
        delay(800);
        return INVALID_INPUT;
    }

    if (step == Run_Test && is_run_test_valid(answer))
    {
        printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
        delay(800);
        return INVALID_INPUT;
    }

    return 0;
}

int main()
{
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

        int answer = get_parsed_input();

        if (answer == EXIT_PROGRAM)
            break;
        else if (answer == INVALID_INPUT)
            continue;

        if (check_valid_answer(step, answer) == INVALID_INPUT)
            continue;

        // ó������ ���ư���
        if (answer == 0 && step == Run_Test)
        {
            step = CarType_Q;
            continue;
        }

        // �������� ���ư���
        if (answer == 0 && step >= 1)
        {
            step -= 1;
            continue;
        }

        if (step == CarType_Q)
        {
            selectCarType(answer);
            delay(800);
            step = Engine_Q;
        }
        else if (step == Engine_Q)
        {
            selectEngine(answer);
            delay(800);
            step = brakeSystem_Q;
        }
        else if (step == brakeSystem_Q)
        {
            selectbrakeSystem(answer);
            delay(800);
            step = SteeringSystem_Q;
        }
        else if (step == SteeringSystem_Q)
        {
            selectSteeringSystem(answer);
            delay(800);
            step = Run_Test;
        }
        else if (step == Run_Test)
        {
            if (answer == RUN) {
                runProducedCar();
                delay(2000);
            }
            else if (answer == TEST) {
                printf("Test...\n");
                delay(1500);
                testProducedCar();
                delay(2000);
            }
        }
    }
}

void selectCarType(int car_type)
{
    stack[CarType_Q] = car_type;
    if (car_type == SEDAN)
        printf("���� Ÿ������ Sedan�� �����ϼ̽��ϴ�.\n");
    if (car_type == SUV)
        printf("���� Ÿ������ SUV�� �����ϼ̽��ϴ�.\n");
    if (car_type == TRUCK)
        printf("���� Ÿ������ Truck�� �����ϼ̽��ϴ�.\n");
}

void selectEngine(int engine)
{
    stack[Engine_Q] = engine;
    if (engine == GM)
        printf("GM ������ �����ϼ̽��ϴ�.\n");
    else if (engine == TOYOTA)
        printf("TOYOTA ������ �����ϼ̽��ϴ�.\n");
    else if (engine == WIA)
        printf("WIA ������ �����ϼ̽��ϴ�.\n");
    else if (engine == BROKEN)
        printf("���峭 ������ �����ϼ̽��ϴ�.\n");
}

void selectbrakeSystem(int brake_system)
{
    stack[brakeSystem_Q] = brake_system;
    if (brake_system == MANDO)
        printf("MANDO ������ġ�� �����ϼ̽��ϴ�.\n");
    if (brake_system == CONTINENTAL)
        printf("CONTINENTAL ������ġ�� �����ϼ̽��ϴ�.\n");
    if (brake_system == BOSCH_B)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
}

void selectSteeringSystem(int steer_system)
{
    stack[SteeringSystem_Q] = steer_system;
    if (steer_system == BOSCH_S)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
    if (steer_system == MOBIS)
        printf("MOBIS ������ġ�� �����ϼ̽��ϴ�.\n");
}

int isValidCheck()
{
    if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
    {
        return false;
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        return false;
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        return false;
    }
    else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
    {
        return false;
    }
    else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        return false;
    }
    else if (stack[brakeSystem_Q] != BOSCH_B && stack[SteeringSystem_Q] == BOSCH_S)
    {
        return false;
    }
    else
    {
        return true;
    }
    return true;
}

void runProducedCar()
{
    if (isValidCheck() == false)
    {
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
    }
    else
    {
        if (stack[Engine_Q] == BROKEN)
        {
            printf("������ ���峪�ֽ��ϴ�.\n");
            printf("�ڵ����� �������� �ʽ��ϴ�.\n");
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

            printf("�ڵ����� ���۵˴ϴ�.\n");
        }
    }
}

void testProducedCar()
{
    if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Sedan���� Continental������ġ ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("SUV���� TOYOTA���� ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� WIA���� ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� Mando������ġ ��� �Ұ�\n");
    }
    else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        if (stack[SteeringSystem_Q] == MOBIS)
        {
            printf("Bosch�������� Mobis������ġ ��� �Ұ�\n");
        }
    }
    else
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
    }
}